#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <QByteArray>

class QEvent;

QByteArray EventSerialize(QEvent* event);
QEvent* EventDeserialize(const QByteArray& event);

#endif // SERIALIZE_H
