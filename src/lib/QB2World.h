#ifndef QB2WORLD_H
#define QB2WORLD_H

#include <map>
#include <QEvent>
#include <QMutex>
#include <QTimer>
#include <QObject>
#include <QThread>
#include <Box2D/Box2D.h>

#include "utils/ListRef.h"
#include "qbox2d_global.h"

#include "QB2Object.h"
#include "QB2Scene.h"
#include "QB2ContactListener.h"

class QB2Body;
class QKeyEvent;
class QB2EventFilter;

class QBOX2DSHARED_EXPORT QB2World : public QObject, public QB2Object
{
    Q_OBJECT
    friend class QB2Body;
    friend class QB2EventFilter;
    friend class QB2Scene;
public:
    explicit QB2World(const b2Vec2& gravity, QObject *parent = nullptr);
    virtual ~QB2World() override;

    QB2Body* GetBody(int id);

    void Start();
    void Stop();

    QB2Scene& GetScene();

    void InstallEventFilter(QB2EventFilter& eventFilter);

signals:
    void Updated();
    void BodyUpdated(QB2Body*);
    void BodyAdded(QB2Body*);

protected:
    bool event(QEvent* ev) override;

private:
    void Step();
    void Update();

private:
    b2Body* CreateB2Body(const b2BodyDef& bodyDef);
    void DestroyB2Body(b2Body* body);
    void AddBody(QB2Body& body);
    void RemoveBody(QB2Body& body);

    QMutex& GetMutex();

protected:
    QB2Scene scene_;

private:
    b2World b2world_;
    ListRef<QB2Body> bodies_;
    QTimer timer_;
    QThread thread_;
    QMutex mutex_;
    QB2ContactListener contactListener_;
};

#endif // QB2WORLD_H
