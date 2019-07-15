#include "QB2EventFilter.h"

#include <QKeyEvent>

#include <QB2ContactEvent.h>

QB2EventFilter::QB2EventFilter(QObject* parent): QObject(parent)
{

}

void QB2EventFilter::Update()
{
    OnUpdate();
}

bool QB2EventFilter::eventFilter(QObject* obj, QEvent* event)
{
    if (Event(event)) return QObject::eventFilter(obj, event);

    int type = event->type();
    switch(type) {
        case QEvent::KeyPress:
            return KeyPressEvent(static_cast<QKeyEvent*>(event));
        case QEvent::KeyRelease:
            return KeyReleaseEvent(static_cast<QKeyEvent*>(event));
        case QB2ContactEvent::BeginContact:
            return BeginContact(static_cast<QB2ContactEvent*>(event));
        case QB2ContactEvent::EndContact:
            return EndContact(static_cast<QB2ContactEvent*>(event));
        case QB2ContactEvent::PreSolveContact:
            return PreSolveContact(static_cast<QB2ContactEvent*>(event));
        case QB2ContactEvent::PostSolveContact:
            return PostSolveContact(static_cast<QB2ContactEvent*>(event));
        default:
            return QObject::eventFilter(obj, event);
    }
}
