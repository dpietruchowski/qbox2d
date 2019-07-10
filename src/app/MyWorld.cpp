#include "MyWorld.h"

#include <QDebug>

MyWorld::MyWorld(): QB2World({0, 0.1}), ground(*this), circle(*this)
{
    ground.circle = &circle;
}

MyCircle::MyCircle(QB2World& world): QB2Body(0, world), fixture(30, {0.2, 0.1, 1}, *this)
{
    SetSleepingAllowed(false);
    SetPos(100, -20);
}

void MyCircle::OnUpdate()
{
    if (pos().y() > 230) {
        SetPos(10, 0);
    }
}

MyGround::MyGround(QB2World& world): QB2Body(1, world),
    fixture(QPolygonF(
                {QPointF{0, 0},
                QPointF{0, 10},
                QPointF{500, 0},
                QPointF{500, 10}}
            ),
            b2FixtureParams{0.1, 1, 1}, *this)
{
    SetType(b2_staticBody);
    SetPos(0, 200);
    SetAngle(9);
}

void MyGround::OnUpdate()
{
    static bool show = true;
    if(show) {
        qDebug() << "  My Ground: " << pos() << " angle: " << GetAngle() << " rotation: " << rotation();
        show = false;
    }
}
