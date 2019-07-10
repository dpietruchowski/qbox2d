#include "QB2Client.h"

#include <QEvent>
#include <QMessageBox>
#include <QAbstractSocket>

#include <QtNetwork>

#include "QB2Body.h"
#include "QB2Server.h"

#include "utils/serialize.h"
#include "utils/session.h"

QB2Client::QB2Client()
{
    connect(&socket_, &QIODevice::readyRead, this, &QB2Client::OnReadyRead);
    connect(&socket_, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &QB2Client::OnError);
}

void QB2Client::SetPlayerFactory(const QB2Client::FactoryFunction& factory)
{
    bodiesFactory_ = factory;
}

void QB2Client::SetWorld(std::unique_ptr<QB2World> world)
{
    world_ = std::move(world);
    world_->InstallEventFilter(*this);
}

QB2World& QB2Client::GetWorld()
{
    return *world_;
}

void QB2Client::OpenSession()
{
    session_ = OpenNetworkSession(this);

    connect(session_, &QNetworkSession::opened, this, &QB2Client::OnSessionOpen);
}

void QB2Client::Connect(const QString& hostName, quint16 port)
{
    socket_.connectToHost(hostName, port);
}

bool QB2Client::Event(QEvent* event)
{
    auto IntToArray = [] (qint32 source) {
        QByteArray temp;
        QDataStream data(&temp, QIODevice::ReadWrite);
        data << source;
        return temp;
    };

    if (socket_.state() == QAbstractSocket::ConnectedState) {
        QByteArray data = EventSerialize(event);
        if (data.size() > 0) {
            //socket_.write(IntToArray(data.size()));
            socket_.write(data);
            return socket_.waitForBytesWritten();
        } else {
            return false;
        }
    } else {
        return false;
    }
}

void QB2Client::OnUpdate()
{

}

void QB2Client::OnSessionOpen()
{
}

void QB2Client::OnReadyRead()
{
    QByteArray data = socket_.readAll();
    QDataStream dataStream(data);
    dataStream.setVersion(QDataStream::Qt_4_0);

    if (data.size() <= 0)
        return;

    uint32_t message;
    dataStream >> message;
    switch(message) {
        case QB2Server::AddBodies: {
            while (!dataStream.atEnd()) {
                int32_t newPlayerId;
                dataStream >> newPlayerId;
                bodies_.emplace_back(bodiesFactory_(newPlayerId, *world_));
                bodies_.back()->SetActive(false);
            }
            break;
        }
        case QB2Server::UpdateBodies: {
            while (!dataStream.atEnd()) {
                int32_t id;
                QPointF pos;
                float angle;
                QVector2D linearVelocity;
                float angularVelocity;
                float linearDamping;
                float angularDamping;
                dataStream >> id;
                dataStream >> pos;
                dataStream >> angle;
                dataStream >> linearVelocity;
                dataStream >> angularVelocity;
                dataStream >> linearDamping;
                dataStream >> angularDamping;
                if (id != 100)
                    int h = 0;
                QB2Body* body = world_->GetBody(id);
                if (body) {
                    if (body->GetType() == b2_staticBody)
                        continue;
                    body->SetPos(pos);
                    body->SetAngle(angle);
                    body->SetLinearVelocity(linearVelocity);
                    body->SetAngularVelocity(angularVelocity);
                    body->SetLinearDamping(linearDamping);
                    body->SetAngularDamping(angularDamping);
                }
            }
            break;
        }
        default:
            break;
    }
}

void QB2Client::OnError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            qWarning("The host was not found. Please check the "
                     "host name and port settings.");
            break;
        case QAbstractSocket::ConnectionRefusedError:
            qWarning("The connection was refused by the peer. "
                        "Make sure the fortune server is running, "
                        "and check that the host name and port "
                        "settings are correct.");
            break;
        default:
            qDebug() << socket_.errorString();
        }
}
