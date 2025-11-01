#include "QB2World.h"

#include <QMutexLocker>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QEvent>
#include <QThread>
#include <QDebug>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include "QB2EventFilter.h"
#include "QB2Body.h"

QB2World::QB2World(const b2Vec2& gravity, QObject *parent)
    : QGraphicsScene(parent), b2world_(gravity), contactListener_(*this)
{
    addEllipse({0, 0, 5, 5}, QPen(Qt::red), QBrush(Qt::red));
    mousePosText_ = addText("");
    b2world_.SetContactListener(&contactListener_);
    connect(&timer_, &QTimer::timeout, this, &QB2World::Step);
    transform_.scale(10, 10);
}

QB2World::~QB2World()
{
    Stop();
    for (QB2Body& body: bodies_) {
        removeItem(&body);
    }
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

ListRef<QB2Body>& QB2World::GetBodies()
{
    return bodies_;
}

void QB2World::InstallEventFilter(QB2EventFilter& filter)
{
    installEventFilter(&filter);
    connect(this, &QB2World::Updated, &filter, &QB2EventFilter::Update);
}

void QB2World::RemoveEventFilter(QB2EventFilter& filter)
{
    removeEventFilter(&filter);
    disconnect(&filter);
}

const QTransform& QB2World::GetTransform() const
{
    return transform_;
}

void QB2World::Step()
{
    // Box2D recommended physics step parameters:
    // timeStep: fixed time step of 1/60 second (60 FPS)
    // velocityIterations: 8 iterations for velocity constraint solver
    // positionIterations: 3 iterations for position constraint solver
    constexpr float timeStep = 1.0f / 60.0f;
    constexpr int32 velocityIterations = 8;
    constexpr int32 positionIterations = 3;
    
    b2world_.Step(timeStep, velocityIterations, positionIterations);
    Update();
}

void QB2World::Start()
{
    constexpr int framesPerSecond = 60;
    constexpr int millisecondsPerFrame = 1000 / framesPerSecond;
    timer_.start(millisecondsPerFrame);
}

void QB2World::Stop()
{
    timer_.stop();
}

bool QB2World::event(QEvent* ev)
{
    if (OnEvent(ev))
        return true;
    return QGraphicsScene::event(ev);
}

void QB2World::Update()
{
    for (QB2Body& body: bodies_) {
        body.Update();
        emit BodyUpdated(&body);
    }
    OnUpdate();
    emit Updated();
}

void QB2World::DrawJoints(QPainter* painter)
{
    b2Joint* joint = b2world_.GetJointList();
    for (int i = 0; i < b2world_.GetJointCount(); ++i) {
        QPointF anchorA = {joint->GetAnchorA().x, joint->GetAnchorA().y};
        QPointF anchorB = {joint->GetAnchorB().x, joint->GetAnchorB().y};
        painter->drawLine(anchorA, anchorB);
        joint = joint->GetNext();
    }
}

void QB2World::CreateJoint(const b2JointDef& jointDef)
{
    b2world_.CreateJoint(&jointDef);
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
    addItem(&body);
    emit BodyAdded(&body);
}

void QB2World::RemoveBody(QB2Body& body)
{
    emit BodyRemoved(&body);
    removeItem(&body);
    bodies_.Remove(body);
}

void QB2World::drawBackground(QPainter* painter, const QRectF& rect)
{
    constexpr int gridStep = 10;
    painter->setPen(QPen(QColor(200, 200, 255, 125)));
    
    auto GetStart = [](qreal edge, int step) {
        double mod = fmod(edge, step);
        if (edge < 0 || mod == 0.0) {
            return edge - mod;
        } else {
            return edge - mod + step;
        }
    };

    // draw horizontal grid
    qreal startTop = GetStart(rect.top(), gridStep);
    for (qreal y = startTop; y <= rect.bottom(); y += gridStep) {
       painter->drawLine(rect.left(), y, rect.right(), y);
    }
    // now draw vertical grid
    qreal startLeft = GetStart(rect.left(), gridStep);
    for (qreal x = startLeft; x <= rect.right(); x += gridStep) {
       painter->drawLine(x, rect.top(), x, rect.bottom());
    }
}
