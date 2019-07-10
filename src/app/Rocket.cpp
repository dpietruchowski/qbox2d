#include "Rocket.h"

namespace {

const QPolygonF rocketShape = QPolygonF({
            QPoint{0, 30},
        QPoint{-10, 20}, QPoint{10, 20},
        QPoint{-10, -20}, QPoint{10, -20}});

}

Rocket::Rocket(int id, QB2World& world)
    : QB2Body(id, world),
      fixture_(rocketShape, *this)
{
    SetType(b2_dynamicBody);
    SetPos(0, 0);
    fixture_.SetDensity(5);
    fixture_.SetFriction(10);
    fixture_.SetRestitution(0.1f);
}
