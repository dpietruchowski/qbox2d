#include "QB2CircleFixture.h"

#include <QPainter>

#include "Box2D/Box2D.h"

QB2CircleFixture::QB2CircleFixture(float32 radius,
                                   const b2FixtureParams& params,
                                   const b2Filter& filter,
                                   QB2Body& body)
    : QB2Fixture(CreateFixtureDef(radius, params, filter), body)
{
    ellipse_ = CreateEllipse();
}

QB2CircleFixture::QB2CircleFixture(float32 radius,
                                   const b2FixtureParams& params,
                                   QB2Body& body)
    : QB2Fixture(CreateFixtureDef(radius, params), body)
{
    ellipse_ = CreateEllipse();
}

void QB2CircleFixture::Paint(QPainter* painter) const
{
    float32 radius = b2fixture_->GetShape()->m_radius;

    QPointF center = ellipse_.center();
    QPointF right = {center.x() + radius, center.y()};
    painter->drawEllipse(ellipse_);
    painter->drawLine(center, right);
}

QRectF QB2CircleFixture::boundingRect() const
{
    return ellipse_.marginsAdded({2, 2, 2, 2});
}

void QB2CircleFixture::Debug() const
{

}

QRectF QB2CircleFixture::CreateEllipse() const
{
    float32 radius = b2fixture_->GetShape()->m_radius;
    float32 diameter = radius * 2;
    return QRectF(-radius, -radius, diameter, diameter);
}

b2Shape* QB2CircleFixture::CreateShape(float32 radius) const
{
    b2Shape* shape = new b2CircleShape();
    shape->m_radius = radius;
    return shape;
}

b2FixtureDef QB2CircleFixture::CreateFixtureDef(float32 radius,
                                                const b2FixtureParams& params,
                                                const b2Filter& filter) const
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = CreateShape(radius);
    fixtureDef.friction = params.friction;
    fixtureDef.restitution = params.restitution;
    fixtureDef.density = params.denstity;
    fixtureDef.filter = filter;

    return fixtureDef;
}
