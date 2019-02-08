#ifndef QB2FIXTURE_H
#define QB2FIXTURE_H

#include <QMutex>
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
    explicit QB2Fixture(const b2Shape* shape, QB2Body& body);
    virtual ~QB2Fixture();

    virtual void Paint(QPainter* painter) const = 0;
    virtual QRectF boundingRect() const = 0;

    void SetFilterData(const b2Filter& filter);
    void SetParams(const b2FixtureParams& params);
    void SetParams(float32 friction, float32 restitution, float32 denstity);
    void SetFriction(float32 friction);
    void SetRestitution(float32 restitution);
    void SetDensity(float32 denstity);
    void SetSensor(bool sensor);

    b2Filter GetFilterData() const;
    float32 GetFriction() const;
    float32 GetRestitution() const;
    float32 GetDensity() const;
    bool IsSensor() const;

    virtual void Debug() const = 0;

private:
    void Create(const b2FixtureDef& fixtureDef);
    void Delete();

protected:
    const b2Shape* GetShape() const;

private:
    b2Fixture* b2fixture_;
    QB2Body& body_;
    QMutex mutex_;
};

#endif // QB2FIXTURE_H
