#ifndef ROCKETWORLD_H
#define ROCKETWORLD_H

#include "QB2World.h"
#include "Platform.h"
#include "Rocket.h"
#include "RocketLander.h"

class RocketWorld : public QB2World
{
public:
    RocketWorld();

private:
    std::vector<Platform*> platforms_;
    Platform ground_;
};

#endif // ROCKETWORLD_H
