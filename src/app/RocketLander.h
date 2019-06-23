#ifndef ROCKETLANDER_H
#define ROCKETLANDER_H

#include <vector>
#include <QVector2D>
#include "QB2World.h"
#include "Rocket.h"
#include "Platform.h"

class RocketLander : public QB2World
{
public:
    RocketLander();
    QVector2D force;
    QVector2D velocity;
    QPointF position;

protected:
    bool KeyPressEvent(QKeyEvent* event) override;
    bool KeyReleaseEvent(QKeyEvent* event) override;

private:
    void OnUpdate() override;

private:
    std::vector<Platform> platforms_;
    Platform ground_;
    Rocket rocket_;
    bool applyForce;
};

#endif // ROCKETLANDER_H
