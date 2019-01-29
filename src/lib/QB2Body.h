#ifndef QB2BODY_H
#define QB2BODY_H

#include <memory>
#include <QGraphicsItem>
#include <Box2D/Box2D.h>

#include "utils/ListRef.h"
#include "QB2Fixture.h"
#include "qbox2d_global.h"

class QB2World;
class QB2CircleFixture;
class QB2PolygonFixture;

class QBOX2DSHARED_EXPORT QB2Body : public QGraphicsItem
{
    friend class QB2Fixture;
public:
    explicit QB2Body(const b2BodyDef& bodyDef, QB2World& scene, QGraphicsItem  *parent = nullptr);
    explicit QB2Body(const b2Vec2& position, QB2World& scene, QGraphicsItem  *parent = nullptr);
    ~QB2Body() override;

    void AddFixture(QB2Fixture& fixture);
    void RemoveFixture(QB2Fixture& fixture);

    void Update();

    QB2CircleFixture CreateCircleFixture(float32 radius,
                                     const b2FixtureParams& params,
                                     const b2Filter& filter = b2Filter());
    QB2PolygonFixture CreatePolygonFixture(const std::vector<b2Vec2>& vertices,
                                      const b2FixtureParams& params,
                                      const b2Filter& filter = b2Filter());

    std::unique_ptr<QB2Fixture> CreateCircleUPtrFixture(float32 radius,
                                                          const b2FixtureParams& params,
                                                          const b2Filter& filter = b2Filter());
    std::unique_ptr<QB2Fixture> CreatePolygonUPtrFixture(const std::vector<b2Vec2>& vertices,
                                                           const b2FixtureParams& params,
                                                           const b2Filter& filter = b2Filter());


    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;

    QRectF boundingRect() const override;

private:
    b2Fixture* CreateB2Fixture(const b2FixtureDef& fixtureDef);
    void DestroyB2Fixture(b2Fixture* fixture);
    void Create(const b2BodyDef& bodyDef);
    void Delete();

private:
    b2Body* b2body_;
    QB2World& scene_;
    ListRef<QB2Fixture> fixtures_;
};

#endif // QB2BODY_H
