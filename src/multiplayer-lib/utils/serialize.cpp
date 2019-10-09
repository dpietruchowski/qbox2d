#include "serialize.h"

#include <QDataStream>
#include <QKeyEvent>
#include <QDebug>

int count = 0;
QByteArray EventSerialize(QEvent* event)
{
    QByteArray data;
    QDataStream dataStream(&data, QIODevice::WriteOnly);
    switch(event->type()) {
        case QEvent::KeyPress:
        case QEvent::KeyRelease:
            if (static_cast<QKeyEvent*>(event)->isAutoRepeat())
                break;
            dataStream << event->type();
            dataStream << static_cast<QKeyEvent*>(event)->key();
            dataStream << static_cast<QKeyEvent*>(event)->isAutoRepeat();
            qDebug() << "Client " << count++ << event->type();
            break;
        default:
            break;
    }
    return data;
}

QEvent* EventDeserialize(const QByteArray& event)
{
    QDataStream dataStream(event);
    int type;
    dataStream >> type;
    switch(type) {
        case QEvent::KeyPress:
        case QEvent::KeyRelease:
            int key;
            dataStream >> key;
            bool autoRepeat;
            dataStream >> autoRepeat;
            qDebug() << "Client " << count++ << static_cast<QEvent::Type>(type);
            return new QKeyEvent(static_cast<QEvent::Type>(type), key,
                                 Qt::NoModifier, {}, autoRepeat);
        default:
            break;
    }
    return nullptr;
}
