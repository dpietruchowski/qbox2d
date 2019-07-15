#include "QB2Object.h"

#include <QEvent>
#include "QB2ContactEvent.h"

bool QB2Object::OnEvent(QEvent* event)
{
    int type = event->type();
    switch(type) {
        case QB2ContactEvent::BeginContact: {
            QB2ContactEvent* contactEvent = static_cast<QB2ContactEvent*>(event);
            OnBeginContact(contactEvent);
            return contactEvent->isAccepted();
        }
        case QB2ContactEvent::EndContact: {
            QB2ContactEvent* contactEvent = static_cast<QB2ContactEvent*>(event);
            OnEndContact(contactEvent);
            return contactEvent->isAccepted();
        }
        case QB2ContactEvent::PreSolveContact: {
            QB2ContactEvent* contactEvent = static_cast<QB2ContactEvent*>(event);
            OnPreSolveContact(contactEvent);
            return contactEvent->isAccepted();
        }
        case QB2ContactEvent::PostSolveContact: {
            QB2ContactEvent* contactEvent = static_cast<QB2ContactEvent*>(event);
            OnPostSolveContact(contactEvent);
            return contactEvent->isAccepted();
        }
        default: {
            break;
        }
    }

    return false;
}

void QB2Object::OnBeginContact(QB2ContactEvent*)
{
}

void QB2Object::OnEndContact(QB2ContactEvent*)
{
}

void QB2Object::OnPreSolveContact(QB2ContactEvent*)
{
}

void QB2Object::OnPostSolveContact(QB2ContactEvent*)
{
}

void QB2Object::OnUpdate()
{
}
