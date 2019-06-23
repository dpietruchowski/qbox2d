#ifndef PLATFORM_H
#define PLATFORM_H

#include "QB2Body.h"
#include "QB2PolygonFixture.h"

class Platform : public QB2Body
{
public:
    Platform(const QRectF& rect, QB2World& world);

private:
    QB2PolygonFixture fixture_;
};

#endif // PLATFORM_H
