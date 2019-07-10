#ifndef ROCKET_H
#define ROCKET_H

#include "QB2Body.h"
#include "QB2PolygonFixture.h"

class Rocket : public QB2Body
{
public:
    Rocket(int id, QB2World& world);

private:
    QB2PolygonFixture fixture_;
};

#endif // ROCKET_H
