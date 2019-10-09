#include "Rocket.h"

namespace {

const QPolygonF rocketShape = QPolygonF({
            QPointF{0, 3.0},
        QPointF{-1.0, 2.0}, QPointF{1.0, 2.0},
        QPointF{-1.0, -2.0}, QPointF{1.0, -2.0}});

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
