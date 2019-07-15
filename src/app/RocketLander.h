#ifndef ROCKETLANDER_H
#define ROCKETLANDER_H

#include "QB2EventFilter.h"

class Rocket;

class RocketLander: public QB2EventFilter
{
public:
    RocketLander(Rocket& rocket);

protected:
    bool KeyPressEvent(QKeyEvent* event) override;
    bool KeyReleaseEvent(QKeyEvent* event) override;
    void OnUpdate() override;

private:
    Rocket& rocket_;
    bool leftEngine = false;
    bool rightEngine = false;
    bool bottomEngine = false;
};

#endif // ROCKETLANDER_H
