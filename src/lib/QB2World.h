#ifndef QB2WORLD_H
#define QB2WORLD_H

#include <QObject>
#include <Box2D/Box2D.h>

#include "utils/ListRef.h"
#include "qbox2d_global.h"

class QB2Body;

class QBOX2DSHARED_EXPORT QB2World : public QObject
{
    Q_OBJECT
    friend class QB2Body;
public:
    explicit QB2World(const b2Vec2& gravity, QObject *parent = nullptr);
    virtual ~QB2World() = default;

    void Init();
    void Start();

signals:
    void BodyAdded(QB2Body* body);
    void BodyRemoved(QB2Body* body);
    void BodyUpdated(QB2Body* body);

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    void Step();
    void Update();
    virtual void OnUpdate() = 0;

private:
    b2Body* CreateB2Body(const b2BodyDef& bodyDef);
    void DestroyB2Body(b2Body* body);
    void AddBody(QB2Body& body);
    void RemoveBody(QB2Body& body);
private:
    b2World b2world_;
    ListRef<QB2Body> bodies_;
};

#endif // QB2WORLD_H
