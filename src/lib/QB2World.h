#ifndef QB2WORLD_H
#define QB2WORLD_H

#include <QGraphicsScene>
#include <Box2D/Box2D.h>

#include "utils/ListRef.h"
#include "qbox2d_global.h"

class QB2Body;

class QBOX2DSHARED_EXPORT QB2World : public QGraphicsScene
{
    Q_OBJECT
    friend class QB2Body;
public:
    explicit QB2World(QObject *parent = nullptr);

    void Step();

    QB2Body CreateBody(const b2BodyDef& bodyDef);
    QB2Body CreateBody(const b2Vec2& position);
    std::unique_ptr<QB2Body> CreateUPtrBody(const b2BodyDef& bodyDef);
    std::unique_ptr<QB2Body> CreateUPtrBody(const b2Vec2& position);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    b2Body* CreateB2Body(const b2BodyDef& bodyDef);
    void DestroyB2Body(b2Body* body);
    void AddBody(QB2Body& body);
    void RemoveBody(QB2Body& body);

private:
    b2World b2world_;
    ListRef<QB2Body> bodies_;
    QPointF mousePosition_;
};

#endif // QB2WORLD_H
