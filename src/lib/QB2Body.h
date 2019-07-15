#ifndef QB2BODY_H
#define QB2BODY_H

#include <memory>
#include <QMutex>
#include <QGraphicsItem>
#include <QVector2D>
#include <Box2D/Box2D.h>

#include "utils/ListRef.h"
#include "QB2Object.h"
#include "QB2Fixture.h"
#include "qbox2d_global.h"

class QB2World;
class QB2CircleFixture;
class QB2PolygonFixture;

class QBOX2DSHARED_EXPORT QB2Body : public QGraphicsObject, public QB2Object
{
    friend class QB2Fixture;
public:
    explicit QB2Body(int id, QB2World& scene, QGraphicsItem  *parent = nullptr);
    explicit QB2Body(int id, const b2BodyDef& bodyDef, QB2World& scene, QGraphicsItem  *parent = nullptr);
    explicit QB2Body(int id, const QPointF& position, QB2World& scene, QGraphicsItem  *parent = nullptr);
    ~QB2Body() override;

    int GetId() const;

    void DeleteSelf();

    void AddFixture(QB2Fixture& fixture);
    void RemoveFixture(QB2Fixture& fixture);

    void SetPos(QPointF pos);
    void SetPos(float x, float y);
    // angle in degrees
    void SetAngle(float angle);
    void SetLinearVelocity(const QVector2D& velocity);
    void SetAngularVelocity(float omega);
    // forces
    void ApplyForce(const QVector2D& force, const QPointF& point, bool wake = true);
    void ApplyForceToCenter(const QVector2D& force, bool wake = true);
    void ApplyTorque(float torque, bool wake = true);
    void ApplyLinearImpulse(const QVector2D& impulse, const QPointF& point, bool wake = true);
    void ApplyLinearImpulseToCenter(const QVector2D& impulse, bool wake = true);
    void ApplyAngularImpulse(float impulse, bool wake = true);
    void SetLinearDamping(float linearDamping);
    void SetAngularDamping(float angularDamping);
    void SetGravityScale(float scale);
    void SetType(b2BodyType type);
    void SetBullet(bool bullet);
    void SetSleepingAllowed(bool sleepingAllowed);
    void SetAwake(bool awake);
    void SetActive(bool active);
    void SetFixedRotation(bool fixedRotation);

    void ResetMassData();

    QPointF GetPos() const;
    float GetAngle() const;
    QVector2D GetLinearVelocity() const;
    float32 GetAngularVelocity() const;
    float GetLinearDamping() const;
    float GetAngularDamping() const;
    float GetGravityScale() const;
    b2BodyType GetType() const;
    bool IsBullet() const;
    bool IsSleepingAllowed() const;
    bool IsAwake() const;
    bool IsActive() const;
    bool IsFixedRotation() const;

    QVector2D MapForceToLocal(const QVector2D& force) const;

    void Update();

    QRectF boundingRect() const override;

protected:
    bool event(QEvent* ev) override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;
    virtual void PreparePaint(QPainter* painter) const;

private:
    b2Fixture* CreateB2Fixture(const b2FixtureDef& fixtureDef);
    void DestroyB2Fixture(b2Fixture* fixture);
    void Create(const b2BodyDef& bodyDef);
    void Delete();

    QMutex& GetMutex();

private:
    float MapAngle360(float angle) const;

private:
    int id_ = -1;
    b2Body* b2body_;
    QB2World& scene_;
    ListRef<QB2Fixture> fixtures_;
};

Q_DECLARE_METATYPE(QB2Body*);

#endif // QB2BODY_H
