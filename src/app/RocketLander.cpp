#include "RocketLander.h"

#include <QKeyEvent>

RocketLander::RocketLander() : QB2World({0, -50}), platforms_{},
    ground_(QRectF({0, -200}, QSizeF(500, 2)), *this), rocket_(*this)
{
    rocket_.SetSleepingAllowed(false);
}

bool RocketLander::KeyPressEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat())
        return true;
    applyForce = true;
    switch(event->key()) {
        case Qt::Key_Up: {
            force += {0, -1};
            break;
        }
        case Qt::Key_Down: {
            force += {0, 1};
            break;
        }
        case Qt::Key_Left: {
            force += {-1, 0};
            break;
        }
        case Qt::Key_Right: {
            force += {1, 0};
            break;
        }
        case Qt::Key_Space: {
            break;
        }
        default: {
            break;
        }
    }
    return true;
}

bool RocketLander::KeyReleaseEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat())
        return true;
    force = {0, 0};
    applyForce = false;
    switch(event->key()) {
        case Qt::Key_Up: {
            break;
        }
        case Qt::Key_Down: {
            break;
        }
        case Qt::Key_Left: {
            break;
        }
        case Qt::Key_Right: {
            break;
        }
        case Qt::Key_Space: {
            rocket_.SetPos(position);
            rocket_.SetAwake(true);
            break;
        }
        default: {
            break;
        }
    }
    return true;
}

void RocketLander::OnUpdate()
{
    if (applyForce)
        rocket_.ApplyForceToCenter(force);
}
