#include "QB2ContactListener.h"

#include <QApplication>
#include <QGraphicsScene>

#include "QB2ContactEvent.h"
#include "QB2Body.h"

QB2ContactListener::QB2ContactListener(QGraphicsScene& scene): scene_(scene)
{
}

void QB2ContactListener::BeginContact(b2Contact* contact)
{
    QB2ContactEvent event(QB2ContactEvent::BeginContact, contact);

    QB2Body& bodyA = event.GetFixtureA()->GetBody();
    QB2Body& bodyB = event.GetFixtureB()->GetBody();

    qApp->sendEvent(&scene_, &event);
    event.SetA();
    scene_.sendEvent(&bodyA, &event);
    event.SetB();
    scene_.sendEvent(&bodyB, &event);
}

void QB2ContactListener::EndContact(b2Contact* contact)
{
    QB2ContactEvent event(QB2ContactEvent::EndContact, contact);

    QB2Body& bodyA = event.GetFixtureA()->GetBody();
    QB2Body& bodyB = event.GetFixtureB()->GetBody();

    qApp->sendEvent(&scene_, &event);
    event.SetA();
    scene_.sendEvent(&bodyA, &event);
    event.SetB();
    scene_.sendEvent(&bodyB, &event);
}

void QB2ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    QB2ContactEvent event(QB2ContactEvent::PreSolveContact, contact);

    QB2Body& bodyA = event.GetFixtureA()->GetBody();
    QB2Body& bodyB = event.GetFixtureB()->GetBody();

    qApp->sendEvent(&scene_, &event);
    event.SetA();
    scene_.sendEvent(&bodyA, &event);
    event.SetB();
    scene_.sendEvent(&bodyB, &event);
}

void QB2ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    QB2ContactEvent event(QB2ContactEvent::PostSolveContact, contact);

    QB2Body& bodyA = event.GetFixtureA()->GetBody();
    QB2Body& bodyB = event.GetFixtureB()->GetBody();

    qApp->sendEvent(&scene_, &event);
    event.SetA();
    scene_.sendEvent(&bodyA, &event);
    event.SetB();
    scene_.sendEvent(&bodyB, &event);
}
