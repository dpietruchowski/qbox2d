#include "QB2World.h"

#include "QB2Body.h"

QB2World::QB2World(const b2Vec2& gravity, QObject *parent) : QObject(parent), b2world_(gravity)
{
}

void QB2World::Step()
{
    b2world_.Step(1, 8, 3);
    Update();
}

void QB2World::Init()
{
    for(auto& body: bodies_) {
        emit BodyAdded(body);
    }
}

void QB2World::Update()
{
    for (QB2Body& body: bodies_) {
        body.Update();
    }
    OnUpdate();
}

b2Body* QB2World::CreateB2Body(const b2BodyDef& bodyDef)
{
    return b2world_.CreateBody(&bodyDef);
}

void QB2World::DestroyB2Body(b2Body* body)
{
    b2world_.DestroyBody(body);
}

void QB2World::AddBody(QB2Body& body)
{
    bodies_.Add(body);
    emit BodyAdded(body);
}

void QB2World::RemoveBody(QB2Body& body)
{
    emit BodyRemoved(body);
    bodies_.Remove(body);
}
