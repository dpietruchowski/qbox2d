#include "QB2Player.h"

#include <QTcpSocket>

#include "utils/serialize.h"

QB2Player::QB2Player(QTcpSocket& socket): socket_(socket)
{
    connect(&socket_, &QTcpSocket::readyRead, this, &QB2Player::OnReadyRead);
}

bool QB2Player::SendData(const QByteArray& data)
{
    if (socket_.state() == QAbstractSocket::ConnectedState) {
        socket_.write(data);
        return socket_.waitForBytesWritten();
    }
    return false;
}

void QB2Player::OnReadyRead()
{
    QByteArray data = socket_.readAll();
    QEvent* event = EventDeserialize(data);

    if (event)
        QB2EventFilter::eventFilter(nullptr, event);
}
