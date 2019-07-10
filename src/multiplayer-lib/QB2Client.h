#ifndef QB2CLIENT_H
#define QB2CLIENT_H

#include <memory>

#include <QNetworkSession>
#include <QTcpSocket>

#include "qbox2d_global.h"
#include "QB2EventFilter.h"
#include "QB2World.h"

class QBOX2DSHARED_EXPORT QB2Client : public QB2EventFilter
{
public:
    using FactoryFunction = std::function<std::unique_ptr<QB2Body>(int id, QB2World& world)>;
    QB2Client();

    void SetPlayerFactory(const FactoryFunction& factory);
    void SetWorld(std::unique_ptr<QB2World> world);
    QB2World& GetWorld();

    void OpenSession();
    void Connect(const QString &hostName, quint16 port);

protected:
    bool Event(QEvent* event) override;

private:
    void OnUpdate() override;

private:
    void OnSessionOpen();
    void OnReadyRead();
    void OnError(QAbstractSocket::SocketError socketError);

private:
    std::unique_ptr<QB2World> world_;
    std::vector<std::unique_ptr<QB2Body>> bodies_;
    FactoryFunction bodiesFactory_;
    QTcpSocket socket_;
    QNetworkSession* session_;
};

#endif // QB2CLIENT_H
