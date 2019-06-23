#include "QB2World.h"

#include <QMutexLocker>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QEvent>
#include <QThread>
#include <QDebug>

#include "QB2Body.h"

QB2World::QB2World(const b2Vec2& gravity, QObject *parent)
    : QObject(parent), b2world_(gravity), eventFilter_(*this)
{
    moveToThread(&thread_);
    connect(&timer_, &QTimer::timeout, this, &QB2World::Step);
    connect(this, &QB2World::BodyUpdated, &scene_, &QB2Scene::UpdateBody);
    scene_.installEventFilter(&eventFilter_);
}

QB2World::~QB2World()
{
    qDebug() << "Thread id: " << QThread::currentThreadId();
    Stop();
    while(!thread_.isFinished()) { /* Wait for finish */ }
}

void QB2World::Step()
{
    QMutexLocker ml(&mutex_);
    b2world_.Step(1.f/60, 8, 3);
    ml.unlock();
    Update();
}

void QB2World::Start()
{
    thread_.start();
    timer_.start(1000/60);
}

void QB2World::Stop()
{
    timer_.stop();
    thread_.quit();
}

QB2Scene& QB2World::GetScene()
{
    return scene_;
}

bool QB2World::eventFilter(QObject* obj, QEvent* event)
{
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

bool QB2World::KeyReleaseEvent(QKeyEvent*)
{
    return false;
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
    scene_.AddBody(&body);
}

void QB2World::RemoveBody(QB2Body& body)
{
    QMutexLocker ml(&mutex_);
    scene_.RemoveBody(&body);
    bodies_.Remove(body);
}

QMutex& QB2World::GetMutex()
{
    return mutex_;
}
