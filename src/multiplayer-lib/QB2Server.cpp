#include "QB2Server.h"

#include <QtNetwork>
#include <QTcpServer>

#include "utils/session.h"
#include "QB2Body.h"

QB2Server::QB2Server(): bodiesStream_(&bodiesData_, QIODevice::WriteOnly), bodiesAddedStream_(&bodiesAddedData_, QIODevice::WriteOnly)
{
    bodiesStream_ << Message::UpdateBodies;
    bodiesStream_.setVersion(QDataStream::Qt_4_0);
    bodiesAddedStream_ << Message::AddBodies;
    bodiesStream_.setVersion(QDataStream::Qt_4_0);
}

void QB2Server::SetPlayerFactory(const QB2Server::FactoryFunction& factory)
{
    playerFactory_ = factory;
}

void QB2Server::SetWorld(std::unique_ptr<QB2World> world)
{
    world_ = std::move(world);
    connect(world_.get(), &QB2World::Updated, this, &QB2Server::OnWorldUpdate);
    connect(world_.get(), &QB2World::BodyUpdated, this, &QB2Server::OnBodyUpdate);
    connect(world_.get(), &QB2World::BodyAdded, this, &QB2Server::OnBodyAdded);
}

QB2World& QB2Server::GetWorld()
{
    return *world_;
}

quint16 QB2Server::GetPort() const
{
    if (server_)
        return server_->serverPort();
    return 0;
}

QString QB2Server::GetHost() const
{
    if (server_)
        return server_->serverAddress().toString();
    return "Not connected";
}

void QB2Server::OpenSession()
{
    session_ = OpenNetworkSession(this);
    if (session_) {
        connect(session_, &QNetworkSession::opened, this, &QB2Server::OnSessionOpen);
        session_->open();
    } else {
        OnSessionOpen();
    }

}

int QB2Server::NextId()
{
    int nextId = nextId_;
    ++nextId_;
    return nextId;
}

void QB2Server::OnSessionOpen()
{
    // Save the used configuration
    if (session_) {
        QNetworkConfiguration config = session_->configuration();
        QString id;
        if (config.type() == QNetworkConfiguration::UserChoice)
            id = session_->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        else
            id = config.identifier();

        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }

    server_ = new QTcpServer(this);
    connect(server_, &QTcpServer::newConnection, this, &QB2Server::OnNewConnection);
    if (!server_->listen()) {
        return;
    }

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
}

void QB2Server::OnNewConnection()
{
    QTcpSocket* socket = server_->nextPendingConnection();
    int i = players_.size();
    players_.emplace_back(playerFactory_(*socket));
    connect(socket, &QTcpSocket::disconnected, [this, i] { OnSocketDisconnect(i); });

    bodiesAddedStream_ << Message::AddBodies;
    for (auto& player: players_) {
        if (bodiesAddedData_.size() > 4) {
            player->SendData(bodiesAddedData_);
        }
    }
    bodiesAddedData_.clear();
    bodiesAddedStream_.device()->reset();
}

void QB2Server::OnSocketDisconnect(int i)
{
    auto it = players_.begin();
    std::advance(it, i);
    players_.erase(it);
}

void QB2Server::OnWorldUpdate()
{
    for (auto& player: players_) {
        player->Update();
    }
    for (auto& player: players_) {
        if (bodiesData_.size() > 4) {
            player->SendData(bodiesData_);
        }
    }
    bodiesData_.clear();
    bodiesStream_.device()->reset();
    bodiesStream_ << Message::UpdateBodies;
}

void QB2Server::OnBodyUpdate(QB2Body* body)
{
    if (body->GetType() == b2_staticBody)
        return;
    //TODO: Move this serialization to QB2Body class
    bodiesStream_ << body->GetId();
    bodiesStream_ << body->GetPos();
    bodiesStream_ << body->GetAngle();
    bodiesStream_ << body->GetLinearVelocity();
    bodiesStream_ << body->GetAngularVelocity();
    bodiesStream_ << body->GetLinearDamping();
    bodiesStream_ << body->GetAngularDamping();
    qDebug() << "BODY: " << body->GetId() << body->GetPos() << body->GetAngle();
}

void QB2Server::OnBodyAdded(QB2Body* body)
{
    if (body->GetType() == b2_staticBody)
        return;

    bodiesAddedStream_ << body->GetId();
    qDebug() << "Added: " << body->GetId();
}
