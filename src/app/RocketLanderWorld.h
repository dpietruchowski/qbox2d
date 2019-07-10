#ifndef ROCKETLANDERWORLD_H
#define ROCKETLANDERWORLD_H

#include <vector>
#include "QB2World.h"
#include "Platform.h"
#include "Rocket.h"
#include "RocketLander.h"

class RocketLanderWorld : public QB2World
{
public:
    RocketLanderWorld();

private:
    std::vector<Platform*> platforms_;
    Platform ground_;
    Rocket rocket_;
    RocketLander lander_;
};

#endif // ROCKETLANDERWORLD_H
