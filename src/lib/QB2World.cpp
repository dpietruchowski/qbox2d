#include "QB2World.h"

#include <QMutexLocker>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QEvent>
#include <QThread>
#include <QDebug>

#include "QB2Body.h"

QB2World::QB2World(const b2Vec2& gravity, QObject *parent) : QObject(parent), b2world_(gravity)
{
}

void QB2World::Step()
{
    QMutexLocker ml(&mutex_);
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

bool QB2World::eventFilter(QObject* obj, QEvent* event)
{
    QMutexLocker ml(&mutex_);
    switch(event->type()) {
        case QEvent::KeyPress: return KeyPressEvent(dynamic_cast<QKeyEvent*>(event));
        case QEvent::KeyRelease: return KeyReleaseEvent(dynamic_cast<QKeyEvent*>(event));
        default: return QObject::eventFilter(obj, event);
    }
}

bool QB2World::KeyPressEvent(QKeyEvent*)
{
    return false;
}

bool QB2World::KeyReleaseEvent(QKeyEvent* keyEvent)
{
    return false;
}

void QB2World::timerEvent(QTimerEvent*)
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
