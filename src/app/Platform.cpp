#include "Platform.h"


Platform::Platform(int id, const QRectF& rect, QB2World& world)
    : QB2Body(id, world), fixture_(QRectF({0, 0}, rect.size()), *this)
{
    SetType(b2_staticBody);
    SetPos(rect.topLeft());
}
