#include "RocketWorld.h"

#include <QLineF>
#include <QVector2D>

#include <QKeyEvent>
#include <QDebug>

RocketWorld::RocketWorld() : QB2World({0, -6.0}), platforms_{},
    ground_(0, QRectF({-2.0, 0}, QSizeF(500, 0.2)), *this)
{
    platforms_.push_back(new Platform(1, QRectF({10, 10}, QSizeF(10, 0.2)), *this));
}

