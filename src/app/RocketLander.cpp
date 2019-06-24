#include "RocketLander.h"

#include <QLineF>
#include <QVector2D>

#include <QKeyEvent>
#include <QDebug>

RocketLander::RocketLander() : QB2World({0, -60}), platforms_{},
    ground_(QRectF({-20, -160}, QSizeF(500, 2)), *this), rocket_(*this)
{
    platforms_.push_back(new Platform(QRectF({200, 0}, QSizeF(100, 2)), *this));
    rocket_.SetSleepingAllowed(false);
}

bool RocketLander::KeyPressEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat())
        return true;
    applyForce = true;
    switch(event->key()) {
        case Qt::Key_Up: {
            bottomEngine = true;
            break;
        }
        case Qt::Key_Down: {
            break;
        }
        case Qt::Key_Left: {
            leftEngine = true;
            //rocket_.SetAngle(rocket_.GetAngle() - 90);
            break;
        }
        case Qt::Key_Right: {
            rightEngine = true;
            //rocket_.SetAngle(rocket_.GetAngle() + 10);
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

    switch(event->key()) {
        case Qt::Key_Up: {
            bottomEngine = false;
            break;
        }
        case Qt::Key_Down: {
            break;
        }
        case Qt::Key_Left: {
            leftEngine = false;
            break;
        }
        case Qt::Key_Right: {
            rightEngine = false;
            break;
        }
        case Qt::Key_Space: {
            rocket_.SetPos(10, 190);
            break;
        }
        case Qt::Key_A: {
            rocket_.SetAngle(0);
            rocket_.SetPos(40, 0);
            rocket_.SetLinearVelocity({0, 0});
            rocket_.SetAngularVelocity(0);
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
    QVector2D lForce = rocket_.MapForceToLocal({-50, 0});
    QVector2D rForce = rocket_.MapForceToLocal({50, 0});
    QVector2D bForce = rocket_.MapForceToLocal({0, 150});

    if (leftEngine)
        rocket_.ApplyForce(lForce, {-10, 20});

    if (rightEngine)
        rocket_.ApplyForce(rForce, {10, 20});

    if (bottomEngine)
        rocket_.ApplyForce(bForce, {0, -20});
}
