#include "QB2Fixture.h"

#include <memory>
#include <QPainter>
#include <QMutexLocker>
#include "QB2Body.h"

QB2Fixture::QB2Fixture(const b2FixtureDef& fixtureDef, QB2Body& body)
    : b2fixture_(nullptr), body_(body)
{
    // Note: The shape will be deleted after creating the fixture
    // This is safe because Box2D makes an internal copy of the shape
    // Use unique_ptr for automatic cleanup in case of exceptions
    std::unique_ptr<const b2Shape> shape(fixtureDef.shape);
    Create(fixtureDef);
    // Shape is automatically deleted when unique_ptr goes out of scope
}

QB2Fixture::QB2Fixture(const b2Shape* shape, QB2Body& body)
    : b2fixture_(nullptr), body_(body)
{
    // Use unique_ptr for automatic cleanup in case of exceptions
    std::unique_ptr<const b2Shape> shapePtr(shape);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shapePtr.get();
    fixtureDef.density = 0.001f;
    Create(fixtureDef);
    // Shape is automatically deleted when unique_ptr goes out of scope
}

QB2Fixture::~QB2Fixture()
{
    Delete();
}

void QB2Fixture::PaintFixture(QPainter* painter) const
{
    painter->save();
    PreparePaint(painter);
    Paint(painter);
    painter->restore();
}

void QB2Fixture::SetFilterData(const b2Filter& filter)
{
    b2fixture_->SetFilterData(filter);
}

void QB2Fixture::SetParams(const b2FixtureParams& params)
{
    SetParams(params.friction, params.restitution, params.density);
}

void QB2Fixture::SetParams(float32 friction, float32 restitution, float32 density)
{
    SetFriction(friction);
    SetRestitution(restitution);
    SetDensity(density);
}

void QB2Fixture::SetFriction(float32 friction)
{
    b2fixture_->SetFriction(friction);
}

void QB2Fixture::SetRestitution(float32 restitution)
{
    b2fixture_->SetRestitution(restitution);
}

void QB2Fixture::SetDensity(float32 density)
{
    b2fixture_->SetDensity(density);
}

void QB2Fixture::SetSensor(bool sensor)
{
    b2fixture_->SetSensor(sensor);
}

QB2Body& QB2Fixture::GetBody()
{
    return body_;
}

const QTransform& QB2Fixture::GetWorldTransform() const
{
    return body_.GetWorldTransform();
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

void QB2Fixture::PreparePaint(QPainter*) const
{
}

QRectF QB2Fixture::boundingRect() const
{
    constexpr qreal margin = 5.0;
    b2AABB aabb = b2fixture_->GetAABB(0);

    QRectF rect = QRectF(QPointF(aabb.lowerBound.x, aabb.lowerBound.y),
                         QPointF(aabb.upperBound.x, aabb.upperBound.y));

    rect = rect.marginsAdded(QMarginsF(margin, margin, margin, margin));
    return rect;
}

void QB2Fixture::Create(const b2FixtureDef& fixtureDef)
{
    if (b2fixture_)
        return;
    b2fixture_ = body_.CreateB2Fixture(fixtureDef);
    b2fixture_->SetUserData(this);
    body_.AddFixture(*this);
}

void QB2Fixture::Delete()
{
    if (b2fixture_) {
        body_.DestroyB2Fixture(b2fixture_);
        b2fixture_ = nullptr;
    }
    body_.RemoveFixture(*this);
}

const b2Shape* QB2Fixture::GetShape() const
{
    return b2fixture_->GetShape();
}
