#include "QB2Scene.h"

#include <cmath>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <QDebug>

#include "QB2Body.h"

QB2Scene::QB2Scene(QObject *parent) : QGraphicsScene(parent)
{
    // Origin marker (small red circle at 0,0)
    constexpr qreal originMarkerSize = 5.0;
    addEllipse({0, 0, originMarkerSize, originMarkerSize}, QPen(Qt::red), QBrush(Qt::red));
    mousePosText_ = addText("");
}

void QB2Scene::AddBody(QB2Body* body)
{
    addItem(body);
}

void QB2Scene::RemoveBody(QB2Body* body)
{
    removeItem(body);
}

void QB2Scene::UpdateBody(QB2Body* body)
{
    body->Update();
}

void QB2Scene::drawBackground(QPainter* painter, const QRectF& rect)
{
    constexpr int gridStep = 10;
    painter->setPen(QPen(QColor(200, 200, 255, 125)));
    
    auto GetStart = [](qreal edge, int step) {
        double mod = fmod(edge, step);
        if (edge < 0 || mod == 0.0) {
            return edge - mod;
        } else {
            return edge - mod + step;
        }
    };

    // draw horizontal grid
    qreal startTop = GetStart(rect.top(), gridStep);
    for (qreal y = startTop; y <= rect.bottom(); y += gridStep) {
       painter->drawLine(rect.left(), y, rect.right(), y);
    }
    // now draw vertical grid
    qreal startLeft = GetStart(rect.left(), gridStep);
    for (qreal x = startLeft; x <= rect.right(); x += gridStep) {
       painter->drawLine(x, rect.top(), x, rect.bottom());
    }
}
