#include "RocketLanderWorld.h"

#include <QLineF>
#include <QVector2D>

#include <QKeyEvent>
#include <QDebug>

RocketLanderWorld::RocketLanderWorld() : QB2World({0, -6.0}), platforms_{},
    ground_(0, QRectF({-2.0, 0.0}, QSizeF(500, 0.2)), *this), rocket_(2, *this), lander_(rocket_)
{
    platforms_.push_back(new Platform(1, QRectF({20.0, 10}, QSizeF(10.0, 0.2)), *this));
    InstallEventFilter(lander_);
}

