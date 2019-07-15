#ifndef QB2CONTACTEVENT_H
#define QB2CONTACTEVENT_H

#include <QGraphicsSceneEvent>

#include "QB2Fixture.h"
#include "qbox2d_global.h"

class QBOX2DSHARED_EXPORT QB2ContactEvent: public QGraphicsSceneEvent
{
public:
    enum Type {
        BeginContact = QEvent::User,
        EndContact,
        PreSolveContact,
        PostSolveContact
    };
    QB2ContactEvent(Type type, b2Contact* contact);

    void SetA();
    void SetB();

    bool IsA() const;
    bool IsB() const;

    QB2Fixture* GetOtherFixture();
    QB2Body* GetOtherBody();

    QB2Fixture* GetFixtureA();
    QB2Fixture* GetFixtureB();
    QB2Body* GetBodyA();
    QB2Body* GetBodyB();

private:
    bool isA = true;
    QB2Fixture* fixtureA_ = nullptr;
    QB2Fixture* fixtureB_ = nullptr;
    b2Contact* contact_ = nullptr;
};

#endif // QB2CONTACTEVENT_H
