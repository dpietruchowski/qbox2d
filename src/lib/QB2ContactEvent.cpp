#include "QB2ContactEvent.h"

QB2ContactEvent::QB2ContactEvent(QB2ContactEvent::Type type, b2Contact* contact)
    : QGraphicsSceneEvent(QEvent::Type(type)), contact_(contact)
{
    fixtureA_ = static_cast<QB2Fixture*>(contact_->GetFixtureA()->GetUserData());
    fixtureB_ = static_cast<QB2Fixture*>(contact_->GetFixtureB()->GetUserData());
}

void QB2ContactEvent::SetA()
{
    isA_ = true;
}

void QB2ContactEvent::SetB()
{
    isA_ = false;
}

bool QB2ContactEvent::IsA() const
{
    return isA_;
}

bool QB2ContactEvent::IsB() const
{
    return !IsA();
}

QB2Fixture* QB2ContactEvent::GetOtherFixture()
{
    if (IsA())
        return GetFixtureB();
    else
        return GetFixtureA();
}

QB2Body* QB2ContactEvent::GetOtherBody()
{
    if (IsA())
        return GetBodyB();
    else
        return GetBodyA();
}

QB2Fixture* QB2ContactEvent::GetFixtureA()
{
    return fixtureA_;
}

QB2Fixture* QB2ContactEvent::GetFixtureB()
{
    return fixtureB_;
}

QB2Body* QB2ContactEvent::GetBodyA()
{
    if (fixtureA_)
        return &fixtureA_->GetBody();
    return nullptr;
}

QB2Body* QB2ContactEvent::GetBodyB()
{
    if (fixtureB_)
        return &fixtureB_->GetBody();
    return nullptr;
}
