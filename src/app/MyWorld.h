#ifndef MYWORLD_H
#define MYWORLD_H

#include "QB2World.h"
#include "QB2Body.h"
#include "QB2Fixture.h"
#include "QB2CircleFixture.h"
#include "QB2PolygonFixture.h"

class MyCircle : public QB2Body
{
public:
    MyCircle(QB2World& world);

private:
    void OnUpdate() override;
    b2BodyDef CreateBodyDef() const;

    QB2CircleFixture fixture;
};

class MyGround : public QB2Body
{
public:
    MyGround(QB2World& world);
    MyCircle* circle;

private:
    void OnUpdate() override;
    b2BodyDef CreateBodyDef() const;
    QB2PolygonFixture fixture;
};

class MyWorld : public QB2World
{
public:
    MyWorld();

private:
    void OnUpdate() override {};

private:
    MyGround ground;
    MyCircle circle;
};

#endif // MYWORLD_H
