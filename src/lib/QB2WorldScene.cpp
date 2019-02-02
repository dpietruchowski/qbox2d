#include "QB2WorldScene.h"

QB2WorldScene::QB2WorldScene(std::unique_ptr<QB2World> world): world_(std::move(world))
{
    worldTimer_.setInterval(1000/60);

    ConnectWorldScene();
    ConnectTimerWorld();
    world_->Init();

    worldTimer_.start();
    //worldThread_.start();
}

QB2WorldScene::~QB2WorldScene()
{
    worldTimer_.stop();
    worldThread_.terminate();
    worldThread_.wait();
}

QB2Scene& QB2WorldScene::GetScene()
{
    return scene_;
}

void QB2WorldScene::SetWorld(std::unique_ptr<QB2World> world)
{
    world_ = std::move(world);

    ConnectWorldScene();
    ConnectTimerWorld();
    world_->Init();
}

void QB2WorldScene::ConnectWorldScene()
{
    connect(world_.get(), &QB2World::BodyAdded, &scene_, &QB2Scene::AddBody);
    connect(world_.get(), &QB2World::BodyRemoved, &scene_, &QB2Scene::RemoveBody);
}

void QB2WorldScene::ConnectTimerWorld()
{
    connect(&worldTimer_, &QTimer::timeout, world_.get(), &QB2World::Step);
    //world_->moveToThread(&worldThread_);
}
