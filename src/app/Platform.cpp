#include "Platform.h"


Platform::Platform(const QRectF& rect, QB2World& world)
    : QB2Body(world), fixture_(QRectF({0, 0}, rect.size()), *this)
{
    SetType(b2_staticBody);
    SetPos(rect.topLeft());
}
