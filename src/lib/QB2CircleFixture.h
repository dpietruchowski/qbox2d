#ifndef QB2CIRCLEFIXTURE_H
#define QB2CIRCLEFIXTURE_H

#include "QB2Fixture.h"
#include "qbox2d_global.h"

class QBOX2DSHARED_EXPORT QB2CircleFixture : public QB2Fixture
{
public:
    QB2CircleFixture(float32 radius,
                     const b2FixtureParams& params,
                     const b2Filter& filter,
                     QB2Body& body);
    QB2CircleFixture(float32 radius,
                     const b2FixtureParams& params,
                     QB2Body& body);
    QB2CircleFixture(float32 radius,
                     QB2Body& body);

    void Paint(QPainter* painter) const override;
    QRectF boundingRect() const override;
    void Debug() const override;

    QRectF CreateEllipse() const;

private:
    b2Shape* CreateShape(float32 radius) const;
    b2FixtureDef CreateFixtureDef(float32 radius,
                                  const b2FixtureParams& params,
                                  const b2Filter& filter = b2Filter()) const;

private:
    QRectF ellipse_;
};

#endif // QB2CIRCLEFIXTURE_H
