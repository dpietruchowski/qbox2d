#include "QB2Scene.h"

#include <cmath>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <QDebug>

#include "QB2Body.h"

QB2Scene::QB2Scene(QObject *parent) : QGraphicsScene(parent)
{
    setSceneRect(0, 0, 110, 110);
    addEllipse({0, 0, 5, 5}, QPen(Qt::red), QBrush(Qt::red));
    mousePosText_ = addText("");
}

void QB2Scene::AddBody(QB2Body& body)
{
    addItem(&body);
}

void QB2Scene::RemoveBody(QB2Body& body)
{
    removeItem(&body);
}

void QB2Scene::drawBackground(QPainter* painter, const QRectF& rect)
{
    int step = 10;
    painter->setPen(QPen(QColor(200, 200, 255, 125)));
    auto GetStart = [step](qreal edge) {
        double mod = fmod(edge, step);
        if (edge < 0 || mod == 0.0) {
            return edge - mod;
        } else {
            return edge - mod + step;
        }
    };

    // draw horizontal grid
    qreal startTop = GetStart(rect.top());
    int i = 0;
    for (qreal y = startTop; y <= rect.bottom(); y += step) {
        ++i;
       painter->drawLine(rect.left(), y, rect.right(), y);
    }
    if (rect.top() < 0) {
        int h = 0;
        ++h;
    }
    if (fmod(rect.top(),step) == 0) {
        int h = 0;
        ++h;
    }

    // now draw vertical grid
    qreal startLeft = GetStart(rect.left());
    for (qreal x = startLeft; x <= rect.right(); x += step) {
       painter->drawLine(x, rect.top(), x, rect.bottom());
    }
}

void QB2Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF mousePosition = event->scenePos();

    QString textMouse = "(%1, %2)";
    QString xpos = QString::number(mousePosition.x());
    QString ypos = QString::number(mousePosition.y());
    // now draw mouse position
    mousePosText_->setPlainText(textMouse.arg(xpos).arg(ypos));
    mousePosText_->setPos(mousePosition.x()+4, mousePosition.y());

    QGraphicsScene::mouseMoveEvent(event);
}
