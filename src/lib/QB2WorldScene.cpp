#include "QB2WorldScene.h"

#include <QDebug>

#include "QB2Body.h"

QB2WorldScene::QB2WorldScene(std::unique_ptr<QB2World> world): world_(std::move(world))
{
    AfterWorldSet();
    connect(&worldThread_, &QThread::started, world_.get(), &QB2World::Start);
    worldThread_.start();
}

QB2WorldScene::~QB2WorldScene()
{
}

QB2Scene& QB2WorldScene::GetScene()
{
    return scene_;
}

void QB2WorldScene::AfterWorldSet()
{
    eventFilter_ = std::make_unique<QB2EventFilter>(*world_);
    scene_.installEventFilter(eventFilter_.get());
    world_->moveToThread(&worldThread_);
    ConnectWorldScene();
}

void QB2WorldScene::SetWorld(std::unique_ptr<QB2World> world)
{
    world_ = std::move(world);
    AfterWorldSet();
}

void QB2WorldScene::ConnectWorldScene()
{
    connect(world_.get(), &QB2World::BodyAdded,
            &scene_, &QB2Scene::AddBody, Qt::BlockingQueuedConnection);
    connect(world_.get(), &QB2World::BodyRemoved,
            &scene_, &QB2Scene::RemoveBody, Qt::BlockingQueuedConnection);
    connect(world_.get(), &QB2World::BodyUpdated,
            &scene_, &QB2Scene::UpdateBody);
}
