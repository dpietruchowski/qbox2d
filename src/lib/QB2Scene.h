#ifndef QB2SCENE_H
#define QB2SCENE_H

#include <QGraphicsScene>

class QB2Body;

class QB2Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit QB2Scene(QObject *parent = nullptr);

    void AddBody(QB2Body* body);
    void RemoveBody(QB2Body* body);
    void UpdateBody(QB2Body* body);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QGraphicsTextItem *mousePosText_;
};

#endif // QB2SCENE_H
