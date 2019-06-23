#include "Rocket.h"

Rocket::Rocket(QB2World& world)
    : QB2Body(world),
      fixture_(QPolygonF({
                        QPoint{0, 30},
                    QPoint{-10, 20}, QPoint{10, 20},
                    QPoint{-10, -20}, QPoint{10, -20}
                    }), *this)
{
    SetType(b2_dynamicBody);
    SetPos(10, 0);
    fixture_.SetDensity(0.5);
}
