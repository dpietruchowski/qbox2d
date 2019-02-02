#ifndef QB2FIXTURE_H
#define QB2FIXTURE_H

#include <QRect>
#include <Box2D/Box2D.h>

#include "qbox2d_global.h"

class QPainter;
class QB2Body;

struct QBOX2DSHARED_EXPORT b2FixtureParams
{
    float32 friction;
    float32 restitution;
    float32 denstity;
};

class QBOX2DSHARED_EXPORT QB2Fixture
{
public:
    explicit QB2Fixture(const b2FixtureDef& fitureDef, QB2Body& body);
    virtual ~QB2Fixture();

    virtual void Paint(QPainter* painter) const = 0;
    virtual QRectF boundingRect() const = 0;

    virtual void Debug() const = 0;

private:
    void Create(const b2FixtureDef& fixtureDef);
    void Delete();

protected:
    b2Fixture* b2fixture_;

private:
    QB2Body& body_;
};

#endif // QB2FIXTURE_H
