#ifndef QB2CONTACTLISTENER_H
#define QB2CONTACTLISTENER_H

#include <Box2D/Box2D.h>

class QGraphicsScene;

class QB2ContactListener: public b2ContactListener
{
public:
    QB2ContactListener(QGraphicsScene& scene);

    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

private:
    QGraphicsScene& scene_;
};

#endif // QB2CONTACTLISTENER_H
