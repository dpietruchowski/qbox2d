#include "MyWorld.h"

#include <QDebug>

MyWorld::MyWorld(): QB2World({0, 0.1}), ground(*this), circle(*this)
{
    ground.circle = &circle;
}

MyCircle::MyCircle(QB2World& world): QB2Body(world), fixture(30, {0.2, 0.1, 1}, *this)
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

MyGround::MyGround(QB2World& world): QB2Body(world),
    fixture(std::vector<b2Vec2>{
                {0, 0},
                {0, 2},
                {500, 0},
                {500, 2}
            },
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
