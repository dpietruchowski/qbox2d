#include "QB2ContactListener.h"

#include <QApplication>
#include <QGraphicsScene>

#include "QB2ContactEvent.h"
#include "QB2Body.h"
#include "QB2World.h"

QB2ContactListener::QB2ContactListener(QB2World& scene): world_(scene)
{
}

void QB2ContactListener::SendContactEvent(QB2ContactEvent::Type eventType, b2Contact* contact)
{
    QB2ContactEvent event(eventType, contact);

    QB2Body& bodyA = event.GetFixtureA()->GetBody();
    QB2Body& bodyB = event.GetFixtureB()->GetBody();

    qApp->sendEvent(&world_, &event);
    event.SetA();
    world_.sendEvent(&bodyA, &event);
    event.SetB();
    world_.sendEvent(&bodyB, &event);
}

void QB2ContactListener::BeginContact(b2Contact* contact)
{
    SendContactEvent(QB2ContactEvent::BeginContact, contact);
}

void QB2ContactListener::EndContact(b2Contact* contact)
{
    SendContactEvent(QB2ContactEvent::EndContact, contact);
}

void QB2ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    SendContactEvent(QB2ContactEvent::PreSolveContact, contact);
}

void QB2ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    SendContactEvent(QB2ContactEvent::PostSolveContact, contact);
}
