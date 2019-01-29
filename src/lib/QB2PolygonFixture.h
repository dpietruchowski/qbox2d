#ifndef QB2POLYGONFIXTURE_H
#define QB2POLYGONFIXTURE_H

#include <vector>
#include <QPolygonF>

#include "QB2Fixture.h"
#include "qbox2d_global.h"

class QBOX2DSHARED_EXPORT QB2PolygonFixture : public QB2Fixture
{
public:
    QB2PolygonFixture(const std::vector<b2Vec2>& vertices,
                      const b2FixtureParams& params,
                      const b2Filter& filter,
                      QB2Body& body);
    QB2PolygonFixture(const std::vector<b2Vec2>& vertices,
                      const b2FixtureParams& params,
                      QB2Body& body);

    void Paint(QPainter* painter) const override;
    QRectF boundingRect() const override;

    QPolygonF CreatePolygon() const;

private:
    b2Shape* CreateShape(const std::vector<b2Vec2>& vertices) const;
    b2FixtureDef CreateFixtureDef(const std::vector<b2Vec2>& vertices,
                                  const b2FixtureParams& params,
                                  const b2Filter& filter = b2Filter()) const;

private:
    QPolygonF polygon_;
};

#endif // QB2POLYGONFIXTURE_H
