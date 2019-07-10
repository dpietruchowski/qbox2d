#ifndef ROCKETLANDER_H
#define ROCKETLANDER_H

#include "QB2Player.h"
#include "Rocket.h"

class Rocket;

class RocketLander: public QB2Player
{
public:
    RocketLander(int id, QTcpSocket& socket, QB2World& world);

protected:
    bool KeyPressEvent(QKeyEvent* event) override;
    bool KeyReleaseEvent(QKeyEvent* event) override;

private:
    void OnUpdate() override;

private:
    Rocket rocket_;
    bool leftEngine = false;
    bool rightEngine = false;
    bool bottomEngine = false;
};

#endif // ROCKETLANDER_H
