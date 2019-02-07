#include "QB2World.h"

#include <QMutexLocker>
#include <QTimerEvent>
#include <QThread>
#include <QDebug>

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
    for(QB2Body& body: bodies_) {
        emit BodyAdded(&body);
    }
}

void QB2World::Start()
{
    Init();
    startTimer(1000/60);
}

void QB2World::timerEvent(QTimerEvent* event)
{
    Step();
}

void QB2World::Update()
{
    for (QB2Body& body: bodies_) {
        emit BodyUpdated(&body);
        body.OnUpdate();
    }
    OnUpdate();
}

b2Body* QB2World::CreateB2Body(const b2BodyDef& bodyDef)
{
    QMutexLocker ml(&mutex_);
    return b2world_.CreateBody(&bodyDef);
}

void QB2World::DestroyB2Body(b2Body* body)
{
    QMutexLocker ml(&mutex_);
    b2world_.DestroyBody(body);
}

void QB2World::AddBody(QB2Body& body)
{
    QMutexLocker ml(&mutex_);
    bodies_.Add(body);
    emit BodyAdded(&body);
}

void QB2World::RemoveBody(QB2Body& body)
{
    QMutexLocker ml(&mutex_);
    emit BodyRemoved(&body);
    bodies_.Remove(body);
}
