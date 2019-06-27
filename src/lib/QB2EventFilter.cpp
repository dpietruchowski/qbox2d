#include "QB2EventFilter.h"

#include <QKeyEvent>

QB2EventFilter::QB2EventFilter()
{

}

void QB2EventFilter::Update()
{
    OnUpdate();
}

bool QB2EventFilter::eventFilter(QObject* obj, QEvent* event)
{
    switch(event->type()) {
        case QEvent::KeyPress: return KeyPressEvent(static_cast<QKeyEvent*>(event));
        case QEvent::KeyRelease: return KeyReleaseEvent(static_cast<QKeyEvent*>(event));
        default: return QObject::eventFilter(obj, event);
    }
}
