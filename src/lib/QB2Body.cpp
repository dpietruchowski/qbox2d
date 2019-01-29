#include "QB2Body.h"

#include <QPainter>
#include <QtMath>

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

void QB2Body::Update()
{
    setPos(b2body_->GetPosition().x, b2body_->GetPosition().y);
    setRotation(qDegreesToRadians(b2body_->GetAngle()));
}

QB2CircleFixture QB2Body::CreateCircleFixture(float32 radius,
                                                  const b2FixtureParams& params,
                                                  const b2Filter& filter)
{
    return QB2CircleFixture(radius, params, filter, *this);
}

QB2PolygonFixture QB2Body::CreatePolygonFixture(const std::vector<b2Vec2>& vertices,
                                                    const b2FixtureParams& params,
                                                    const b2Filter& filter)
{
    return QB2PolygonFixture(vertices, params, filter, *this);
}

std::unique_ptr<QB2Fixture> QB2Body::CreateCircleUPtrFixture(float32 radius,
                                                                 const b2FixtureParams& params,
                                                                 const b2Filter& filter)
{
    return std::make_unique<QB2CircleFixture>(radius, params, filter, *this);
}

std::unique_ptr<QB2Fixture> QB2Body::CreatePolygonUPtrFixture(const std::vector<b2Vec2>& vertices,
                                                                  const b2FixtureParams& params,
                                                                  const b2Filter& filter)
{
    return std::make_unique<QB2PolygonFixture>(vertices, params, filter, *this);
}

void QB2Body::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    for(const QB2Fixture& fixture: fixtures_) {
        painter->save();
        painter->setBrush(QBrush(QColor(Qt::yellow)));
        painter->drawRect(fixture.boundingRect());
        painter->restore();
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
