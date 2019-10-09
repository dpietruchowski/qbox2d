#ifndef QB2WORLD_H
#define QB2WORLD_H

#include <map>
#include <QEvent>
#include <QMutex>
#include <QTimer>
#include <QObject>
#include <QThread>
#include <QGraphicsScene>
#include <Box2D/Box2D.h>

#include "utils/ListRef.h"
#include "qbox2d_global.h"

#include "QB2Object.h"
#include "QB2Scene.h"
#include "QB2ContactListener.h"

class QB2Body;
class QKeyEvent;
class QB2EventFilter;

class QBOX2DSHARED_EXPORT QB2World : public QGraphicsScene, public QB2Object
{
    Q_OBJECT
    friend class QB2Body;
    friend class QB2EventFilter;
    friend class QB2Scene;
public:
    explicit QB2World(const b2Vec2& gravity, QObject *parent = nullptr);
    virtual ~QB2World() override;

    QB2Body* GetBody(int id);
    ListRef<QB2Body>& GetBodies();

    void InstallEventFilter(QB2EventFilter& filter);
    void RemoveEventFilter(QB2EventFilter& filter);

    const QTransform& GetTransform() const;

    void Start();
    void Stop();

signals:
    void Updated();
    void BodyUpdated(QB2Body*);
    void BodyAdded(QB2Body*);
    void BodyRemoved(QB2Body*);

protected:
    bool event(QEvent* ev) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    void Step();
    void Update();
    void DrawJoints(QPainter *painter);

private:
    void CreateJoint(const b2JointDef& jointDef);
    b2Body* CreateB2Body(const b2BodyDef& bodyDef);
    void DestroyB2Body(b2Body* body);
    void AddBody(QB2Body& body);
    void RemoveBody(QB2Body& body);

private:
    b2World b2world_;
    QTransform transform_;
    ListRef<QB2Body> bodies_;
    QB2ContactListener contactListener_;
    QTimer timer_;
    QGraphicsTextItem *mousePosText_;
};

#endif // QB2WORLD_H
