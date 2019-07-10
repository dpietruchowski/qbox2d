#include "serialize.h"

#include <QDataStream>
#include <QKeyEvent>
#include <QDebug>

QByteArray EventSerialize(QEvent* event)
{
    QByteArray data;
    QDataStream dataStream(&data, QIODevice::WriteOnly);
    switch(event->type()) {
        case QEvent::KeyPress:
        case QEvent::KeyRelease:
            dataStream << event->type();
            dataStream << static_cast<QKeyEvent*>(event)->key();
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
            return new QKeyEvent(static_cast<QEvent::Type>(type), key, Qt::NoModifier);
        default:
            break;
    }
    return nullptr;
}
