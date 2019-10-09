#include "QB2PolygonFixture.h"

#include <QPainter>
#include <QDebug>

#include "Box2D/Box2D.h"

QB2PolygonFixture::QB2PolygonFixture(const QPolygonF& polygon,
                                     const b2FixtureParams& params,
                                     const b2Filter& filter,
                                     QB2Body& body)
    : QB2Fixture(CreateFixtureDef(polygon, params, filter), body), polygon_(polygon)
{
    polygon_ = CreatePolygon();
}

QB2PolygonFixture::QB2PolygonFixture(const QPolygonF& polygon,
                                     const b2FixtureParams& params,
                                     QB2Body& body)
    : QB2Fixture(CreateFixtureDef(polygon, params), body)
{
    polygon_ = CreatePolygon();
}

QB2PolygonFixture::QB2PolygonFixture(const QPolygonF& polygon,
                                     QB2Body& body)
    : QB2Fixture(CreateShape(polygon), body), polygon_(polygon)
{
    polygon_ = CreatePolygon();
}

void QB2PolygonFixture::Paint(QPainter* painter) const
{
    painter->drawPolygon(polygon_);
}

QRectF QB2PolygonFixture::boundingRect() const
{
    return polygon_.boundingRect().marginsAdded({2, 2, 2, 2});
}

void QB2PolygonFixture::Debug() const
{
}

QPolygonF QB2PolygonFixture::CreatePolygon() const
{
    const b2PolygonShape* polygon = dynamic_cast<const b2PolygonShape*>(GetShape());
    int count = static_cast<int>(polygon->m_count);

    QVector<QPointF> points;
    for(int i = 0; i < count; i++) {
        b2Vec2 p = polygon->m_vertices[i];
        QPointF point(p.x, p.y);
        points.push_back(point);
    }

    return GetWorldTransform().map(QPolygonF(points));
}

b2Shape* QB2PolygonFixture::CreateShape(const QPolygonF& polygon) const
{
    b2PolygonShape* shape = new b2PolygonShape();
    std::vector<b2Vec2> vertices = {};
    for (const auto& point: polygon) {
        vertices.emplace_back(point.x(), point.y());
    }
    shape->Set(vertices.data(), static_cast<int>(vertices.size()));
    return shape;
}

b2FixtureDef QB2PolygonFixture::CreateFixtureDef(const QPolygonF& polygon,
                                                 const b2FixtureParams& params,
                                                 const b2Filter& filter) const
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = CreateShape(polygon);
    fixtureDef.friction = params.friction;
    fixtureDef.restitution = params.restitution;
    fixtureDef.density = params.denstity;
    fixtureDef.filter = filter;

    return fixtureDef;
}
