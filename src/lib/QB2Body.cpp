#include "QB2Body.h"

#include <QPainter>
#include <QtMath>
#include <QGraphicsSceneMouseEvent>

#include "QB2Fixture.h"
#include "QB2CircleFixture.h"
#include "QB2PolygonFixture.h"
#include "QB2World.h"

QB2Body::QB2Body(const b2BodyDef& bodyDef, QB2World& scene, QGraphicsItem *parent)
    : QGraphicsItem(parent), b2body_(nullptr), scene_(scene)
{
    Create(bodyDef);
}

QB2Body::QB2Body(const b2Vec2& position, QB2World& scene, QGraphicsItem* parent)
    : QGraphicsItem(parent), b2body_(nullptr), scene_(scene)
{
    b2BodyDef bodyDef;
    bodyDef.position = position;
    bodyDef.type = b2_dynamicBody;
    Create(bodyDef);
}

QB2Body::~QB2Body()
{
    Delete();
}

void QB2Body::AddFixture(QB2Fixture& fixture)
{
    fixtures_.Add(fixture);
}

void QB2Body::RemoveFixture(QB2Fixture& fixture)
{
    fixtures_.Remove(fixture);
}

void QB2Body::SetPos(QPointF pos)
{
    SetPos(pos.x(), pos.y());
}


void QB2Body::SetPos(float x, float y)
{
    b2body_->SetTransform({x, y}, b2body_->GetAngle());
}

void QB2Body::SetAngle(float angle)
{
    QPointF pos = GetPos();
    b2body_->SetTransform({pos.x(), pos.y()}, qDegreesToRadians(angle));
}

QPointF QB2Body::GetPos() const
{
    b2Vec2 pos = b2body_->GetPosition();
    return QPointF(pos.x, pos.y);
}

float QB2Body::GetAngle() const
{
    return qRadiansToDegrees(b2body_->GetAngle());
}

void QB2Body::SetAwake(bool awake)
{
    b2body_->SetAwake(awake);
}

bool QB2Body::IsAwake() const
{
    return b2body_->IsAwake();
}

void QB2Body::Update()
{
    for(const QB2Fixture& fixture: fixtures_) {
        fixture.Debug();
    }
    setPos(GetPos());
    setRotation(GetAngle());
    OnUpdate();
}

void QB2Body::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    for(const QB2Fixture& fixture: fixtures_) {
        /*painter->save();
        painter->setBrush(QBrush(QColor(Qt::yellow)));
        painter->drawRect(fixture.boundingRect());
        painter->restore();*/
        painter->save();
        fixture.Paint(painter);
        painter->restore();
    }
}

QRectF QB2Body::boundingRect() const
{
    if (fixtures_.size() == 0)
        return {0, 0, 0, 0};
    QB2Fixture& f = *fixtures_.begin();
    QRectF rect = f.boundingRect();
    for(const QB2Fixture& fixture: fixtures_) {
        rect = rect.united(fixture.boundingRect());
    }
    return rect;
}

void QB2Body::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    SetPos(event->scenePos());
}

void QB2Body::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    SetAwake(false);
}

void QB2Body::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    SetAwake(true);
}

b2Fixture* QB2Body::CreateB2Fixture(const b2FixtureDef& fixtureDef)
{
    return b2body_->CreateFixture(&fixtureDef);
}

void QB2Body::DestroyB2Fixture(b2Fixture* fixture)
{
    b2body_->DestroyFixture(fixture);
}

void QB2Body::Create(const b2BodyDef& bodyDef)
{
    if (b2body_)
        return;
    b2body_ = scene_.CreateB2Body(bodyDef);
    scene_.AddBody(*this);
}

void QB2Body::Delete()
{
    if (b2body_)
        scene_.DestroyB2Body(b2body_);
    scene_.RemoveBody(*this);
}
