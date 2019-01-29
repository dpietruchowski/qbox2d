#include "QB2World.h"

#include <cmath>

#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include "QB2Body.h"

QB2World::QB2World(QObject *parent) : QGraphicsScene(parent), b2world_({1, 1})
{
    setSceneRect(-10, -10, 10000, 10000);
}

void QB2World::Step()
{
    b2world_.Step(1, 8, 3);
    for (QB2Body& body: bodies_) {
        body.Update();
    }
}

QB2Body QB2World::CreateBody(const b2BodyDef& bodyDef)
{
    return QB2Body(bodyDef, *this);
}

QB2Body QB2World::CreateBody(const b2Vec2& position)
{
    return QB2Body(position, *this);
}

std::unique_ptr<QB2Body> QB2World::CreateUPtrBody(const b2BodyDef& bodyDef)
{
    return std::make_unique<QB2Body>(bodyDef, *this);
}

std::unique_ptr<QB2Body> QB2World::CreateUPtrBody(const b2Vec2& position)
{
    return std::make_unique<QB2Body>(position, *this);
}

void QB2World::drawBackground(QPainter* painter, const QRectF& rect)
{
    int step = 10;
    painter->setPen(QPen(QColor(200, 200, 255, 125)));
    // draw horizontal grid
    qreal start = 0;
    if (start > rect.top()) {
       start -= step;
    }
    for (qreal y = start - step; y < rect.bottom(); ) {
       y += step;
       painter->drawLine(rect.left(), y, rect.right(), y);
    }
    // now draw vertical grid
    start = 0;
    if (start > rect.left()) {
       start -= step;
    }
    for (qreal x = start - step; x < rect.right(); ) {
       x += step;
       painter->drawLine(x, rect.top(), x, rect.bottom());
    }

    QString textMouse = "(%1, %2)";
    QString xpos = QString::number(mousePosition_.x());
    QString ypos = QString::number(mousePosition_.y());
    // now draw mouse position
    painter->drawText(mousePosition_, textMouse.arg(xpos).arg(ypos));
}

void QB2World::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    mousePosition_ = event->scenePos();
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
    addItem(&body);
    bodies_.Add(body);
}

void QB2World::RemoveBody(QB2Body& body)
{
    bodies_.Remove(body);
}
