#include "QB2Fixture.h"

#include "QB2Body.h"

QB2Fixture::QB2Fixture(const b2FixtureDef& fixtureDef, QB2Body& body)
    : b2fixture_(nullptr), body_(body)
{
    Create(fixtureDef);
    delete fixtureDef.shape;
}

QB2Fixture::~QB2Fixture()
{
    Delete();
}

QRectF QB2Fixture::boundingRect() const
{
    b2AABB aabb = b2fixture_->GetAABB(0);

    QRectF rect = QRectF(QPointF(aabb.lowerBound.x, aabb.lowerBound.y),
                         QPointF(aabb.upperBound.x, aabb.upperBound.y));

    rect = rect.marginsAdded(QMarginsF(5,5,5,5));
    return rect;
}

void QB2Fixture::Create(const b2FixtureDef& fixtureDef)
{
    if (b2fixture_)
        return;
    b2fixture_ = body_.CreateB2Fixture(fixtureDef);
    body_.AddFixture(*this);
}

void QB2Fixture::Delete()
{
    if (b2fixture_)
        body_.DestroyB2Fixture(b2fixture_);
    body_.RemoveFixture(*this);
}
