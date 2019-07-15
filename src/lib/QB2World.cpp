#include "QB2World.h"

#include <QMutexLocker>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QEvent>
#include <QThread>
#include <QDebug>

#include "QB2Body.h"

QB2World::QB2World(const b2Vec2& gravity, QObject *parent)
    : QB2EventFilter(parent), b2world_(gravity), contactListener_(scene_)
{
    b2world_.SetContactListener(&contactListener_);
    moveToThread(&thread_);
    connect(&timer_, &QTimer::timeout, this, &QB2World::Step);
    connect(this, &QB2World::BodyUpdated, &scene_, &QB2Scene::UpdateBody);
}

QB2World::~QB2World()
{
    qDebug() << "Thread id: " << QThread::currentThreadId();
    Stop();
    while(!thread_.isFinished()) { /* Wait for finish */ }
}

QB2Body* QB2World::GetBody(int id)
{
    auto iter = std::find_if(bodies_.begin(), bodies_.end(),
                 [id](QB2Body& body) {
        return body.GetId() == id;
    });

    if (iter != bodies_.end())
        return &(iter->get());

    return nullptr;
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

void QB2World::InstallEventFilter(QB2EventFilter& eventFilter)
{
    scene_.installEventFilter(&eventFilter);
    connect(this, &QB2World::Updated, &eventFilter, &QB2EventFilter::Update);
}

void QB2World::Update()
{
    for (QB2Body& body: bodies_) {
        emit BodyUpdated(&body);
        body.OnUpdate();
    }
    emit Updated();
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
    emit BodyAdded(&body);
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
