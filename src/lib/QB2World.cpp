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
    setSceneRect(0, 0, 1000, 1000);
    addEllipse({0, 0, 5, 5}, QPen(Qt::red), QBrush(Qt::red));
    mousePosText_ = addText("");
    b2world_.SetContactListener(&contactListener_);
    connect(&timer_, &QTimer::timeout, this, &QB2World::Step);
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

void QB2World::InstallEventFilter(QB2EventFilter& filter)
{
    installEventFilter(&filter);
    connect(this, &QB2World::Updated, &filter, &QB2EventFilter::Update);
}

void QB2World::Step()
{
    b2world_.Step(1.f/60, 8, 3);
    Update();
}

void QB2World::Start()
{
    timer_.start(1000/60);
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
    int step = 10;
    painter->setPen(QPen(QColor(200, 200, 255, 125)));
    auto GetStart = [step](qreal edge) {
        double mod = fmod(edge, step);
        if (edge < 0 || mod == 0.0) {
            return edge - mod;
        } else {
            return edge - mod + step;
        }
    };

    // draw horizontal grid
    qreal startTop = GetStart(rect.top());
    int i = 0;
    for (qreal y = startTop; y <= rect.bottom(); y += step) {
        ++i;
       painter->drawLine(rect.left(), y, rect.right(), y);
    }
    // now draw vertical grid
    qreal startLeft = GetStart(rect.left());
    for (qreal x = startLeft; x <= rect.right(); x += step) {
       painter->drawLine(x, rect.top(), x, rect.bottom());
    }
}

void QB2World::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF mousePosition = event->scenePos();

    QString textMouse = "(%1, %2)";
    QString xpos = QString::number(mousePosition.x());
    QString ypos = QString::number(mousePosition.y());
    // now draw mouse position
    mousePosText_->setPlainText(textMouse.arg(xpos).arg(ypos));
    mousePosText_->setPos(mousePosition.x()+4, mousePosition.y());

    QGraphicsScene::mouseMoveEvent(event);
}
