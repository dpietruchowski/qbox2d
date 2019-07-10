#include "RocketWorld.h"

#include <QLineF>
#include <QVector2D>

#include <QKeyEvent>
#include <QDebug>

RocketWorld::RocketWorld() : QB2World({0, -60}), platforms_{},
    ground_(0, QRectF({-20, -160}, QSizeF(500, 2)), *this)
{
    platforms_.push_back(new Platform(1, QRectF({200, 0}, QSizeF(100, 2)), *this));
}

