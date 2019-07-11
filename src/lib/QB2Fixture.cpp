#include "QB2Fixture.h"

#include <QPainter>
#include <QMutexLocker>
#include "QB2Body.h"

QB2Fixture::QB2Fixture(const b2FixtureDef& fixtureDef, QB2Body& body)
    : b2fixture_(nullptr), body_(body)
{
    Create(fixtureDef);
    delete fixtureDef.shape;
}

QB2Fixture::QB2Fixture(const b2Shape* shape, QB2Body& body)
    : b2fixture_(nullptr), body_(body)
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = 0.001f;
    Create(fixtureDef);
    delete shape;
}

QB2Fixture::~QB2Fixture()
{
    Delete();
}

void QB2Fixture::PaintFixture(QPainter* painter) const
{
    painter->save();
    PreparePainter(painter);
    Paint(painter);
    painter->restore();
}

void QB2Fixture::SetFilterData(const b2Filter& filter)
{
    QMutexLocker ml(&body_.GetMutex());
    b2fixture_->SetFilterData(filter);
}

void QB2Fixture::SetParams(const b2FixtureParams& params)
{
    SetParams(params.friction, params.restitution, params.denstity);
}

void QB2Fixture::SetParams(float32 friction, float32 restitution, float32 denstity)
{
    SetFriction(friction);
    SetRestitution(restitution);
    SetDensity(denstity);
}

void QB2Fixture::SetFriction(float32 friction)
{
    QMutexLocker ml(&body_.GetMutex());
    b2fixture_->SetFriction(friction);
}

void QB2Fixture::SetRestitution(float32 restitution)
{
    QMutexLocker ml(&body_.GetMutex());
    b2fixture_->SetRestitution(restitution);
}

void QB2Fixture::SetDensity(float32 denstity)
{
    QMutexLocker ml(&body_.GetMutex());
    b2fixture_->SetDensity(denstity);
}

b2Filter QB2Fixture::GetFilterData() const
{
    return b2fixture_->GetFilterData();
}

float32 QB2Fixture::GetFriction() const
{
    return b2fixture_->GetFriction();
}

float32 QB2Fixture::GetRestitution() const
{
    return b2fixture_->GetRestitution();
}

float32 QB2Fixture::GetDensity() const
{
    return b2fixture_->GetDensity();
}

bool QB2Fixture::IsSensor() const
{
    return b2fixture_->IsSensor();
}

void QB2Fixture::PreparePainter(QPainter*) const
{
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

const b2Shape* QB2Fixture::GetShape() const
{
    return b2fixture_->GetShape();
}
