#include "MyWorld.h"

#include <QDebug>

MyWorld::MyWorld(): QB2World({0, 0.1}), ground(*this), circle(*this)
{
    ground.circle = &circle;
}

MyCircle::MyCircle(QB2World& world): QB2Body(CreateBodyDef(), world), fixture(30, {0.2, 0.1, 1}, *this)
{
    SetPos({10, 0});
}

void MyCircle::OnUpdate()
{
    if (pos().y() > 230) {
        SetPos(10, 0);
    }
}

b2BodyDef MyCircle::CreateBodyDef() const
{
    b2BodyDef def;
    def.type = b2_dynamicBody;
    return def;
}

MyGround::MyGround(QB2World& world): QB2Body(CreateBodyDef(), world),
    fixture(std::vector<b2Vec2>{
                {0, 0},
                {0, 2},
                {500, 0},
                {500, 2}
            },
            b2FixtureParams{0.1, 1, 1}, *this)
{
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

b2BodyDef MyGround::CreateBodyDef() const
{
    b2BodyDef def;
    def.type = b2_staticBody;
    def.position = {0, 200};
    return def;
}
