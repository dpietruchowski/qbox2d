#ifndef QB2PLAYER_H
#define QB2PLAYER_H

#include "qbox2d_global.h"
#include "QB2EventFilter.h"

class QKeyEvent;
class QTcpSocket;
class QB2Body;

class QBOX2DSHARED_EXPORT QB2Player: public QB2EventFilter
{
public:
    QB2Player(QTcpSocket& socket);
    virtual ~QB2Player() {}

    bool SendData(const QByteArray& data);

    //virtual std::vector<QB2Body*> GetBodies() = 0;

private:
    void OnReadyRead();

private:
    QTcpSocket& socket_;
};

#endif // QB2PLAYER_H
