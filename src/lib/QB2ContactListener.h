#ifndef QB2CONTACTLISTENER_H
#define QB2CONTACTLISTENER_H

#include <Box2D/Box2D.h>
#include "QB2ContactEvent.h"

class QB2World;

class QB2ContactListener: public b2ContactListener
{
public:
    QB2ContactListener(QB2World& scene);

    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

private:
    void SendContactEvent(QB2ContactEvent::Type eventType, b2Contact* contact);

private:
    QB2World& world_;
};

#endif // QB2CONTACTLISTENER_H
