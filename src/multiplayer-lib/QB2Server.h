#ifndef QB2SERVER_H
#define QB2SERVER_H

#include <functional>

#include <QTcpServer>

#include "qbox2d_global.h"
#include "QB2Player.h"
#include "QB2World.h"

class QNetworkSession;

class QBOX2DSHARED_EXPORT QB2Server: public QObject
{
public:
    using FactoryFunction = std::function<std::unique_ptr<QB2Player>(QTcpSocket& socket)>;

    enum Message {
        AddBodies,
        UpdateBodies
    };

    QB2Server();

    void SetPlayerFactory(const FactoryFunction& factory);
    void SetWorld(std::unique_ptr<QB2World> world);
    QB2World& GetWorld();

    quint16 GetPort() const;
    QString GetHost() const;

    void OpenSession();

    int NextId();

private:
    void OnSessionOpen();
    void OnNewConnection();
    void OnSocketDisconnect(int i);
    void OnWorldUpdate();
    void OnBodyUpdate(QB2Body* body);
    void OnBodyAdded(QB2Body* body);

private:
    std::unique_ptr<QB2World> world_;
    std::vector<std::unique_ptr<QB2Player>> players_;
    QByteArray bodiesData_;
    QDataStream bodiesStream_;
    QByteArray bodiesAddedData_;
    QDataStream bodiesAddedStream_;
    FactoryFunction playerFactory_;
    QTcpServer* server_ = nullptr;
    QNetworkSession* session_;
    int nextId_ = 100;
    QHostAddress address_;
};

#endif // QB2SERVER_H
