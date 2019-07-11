#include "QB2Body.h"

#include <math.h>

#include <QApplication>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMutexLocker>
#include <QPainter>
#include <QThread>
#include <QVector2D>
#include <QtMath>

#include "QB2Fixture.h"
#include "QB2CircleFixture.h"
#include "QB2PolygonFixture.h"
#include "QB2World.h"

QB2Body::QB2Body(int id, QB2World& scene, QGraphicsItem *parent)
    : QGraphicsItem(parent), id_(id), b2body_(nullptr), scene_(scene)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    Create(bodyDef);
}

QB2Body::QB2Body(int id, const b2BodyDef& bodyDef, QB2World& scene, QGraphicsItem* parent)
    : QGraphicsItem(parent), id_(id), b2body_(nullptr), scene_(scene)
{
    Create(bodyDef);
}

QB2Body::QB2Body(int id, const QPointF& position, QB2World& scene, QGraphicsItem* parent)
    : QGraphicsItem(parent), id_(id), b2body_(nullptr), scene_(scene)
{
    b2BodyDef bodyDef;
    bodyDef.position = {position.x(), position.y()};
    Create(bodyDef);
}

QB2Body::~QB2Body()
{
    Delete();
}

int QB2Body::GetId() const
{
    return id_;
}

void QB2Body::AddFixture(QB2Fixture& fixture)
{
    QMutexLocker ml(&scene_.GetMutex());
    fixtures_.Add(fixture);
}

void QB2Body::RemoveFixture(QB2Fixture& fixture)
{
    QMutexLocker ml(&scene_.GetMutex());
    fixtures_.Remove(fixture);
}

void QB2Body::SetPos(QPointF pos)
{
    SetPos(pos.x(), pos.y());
}


void QB2Body::SetPos(float x, float y)
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->SetTransform({x, y}, b2body_->GetAngle());
}

void QB2Body::SetAngle(float angle)
{
    angle = MapAngle360(angle);
    QMutexLocker ml(&scene_.GetMutex());
    QPointF pos = GetPos();
    b2body_->SetTransform({pos.x(), pos.y()}, qDegreesToRadians(angle));
}

void QB2Body::SetLinearVelocity(const QVector2D& velocity)
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->SetLinearVelocity({velocity.x(), velocity.y()});
}

void QB2Body::SetAngularVelocity(float omega)
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->SetAngularVelocity(omega);
}

void QB2Body::ApplyForce(const QVector2D& force, const QPointF& point, bool wake)
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->ApplyForce({force.x(), force.y()},
                        b2body_->GetWorldPoint({point.x(), point.y()}),
                        wake);
}

void QB2Body::ApplyForceToCenter(const QVector2D& force, bool wake)
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->ApplyForceToCenter({force.x(), force.y()}, wake);
}

void QB2Body::ApplyTorque(float torque, bool wake)
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->ApplyTorque(torque, wake);
}

void QB2Body::ApplyLinearImpulse(const QVector2D& impulse, const QPointF& point, bool wake)
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->ApplyLinearImpulse({impulse.x(), impulse.y()}, {point.x(), point.y()}, wake);
}

void QB2Body::ApplyLinearImpulseToCenter(const QVector2D& impulse, bool wake)
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->ApplyLinearImpulseToCenter({impulse.x(), impulse.y()}, wake);
}

void QB2Body::ApplyAngularImpulse(float impulse, bool wake)
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->ApplyAngularImpulse(impulse, wake);
}

void QB2Body::SetLinearDamping(float linearDamping)
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->SetLinearDamping(linearDamping);
}

void QB2Body::SetAngularDamping(float angularDamping)
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->SetAngularDamping(angularDamping);
}

void QB2Body::SetGravityScale(float scale)
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->SetGravityScale(scale);
}

void QB2Body::SetType(b2BodyType type)
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->SetType(type);
}

void QB2Body::SetBullet(bool bullet)
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->SetBullet(bullet);
}

void QB2Body::SetSleepingAllowed(bool sleepingAllowed)
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->SetSleepingAllowed(sleepingAllowed);
}

void QB2Body::SetAwake(bool awake)
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->SetAwake(awake);
}

void QB2Body::SetActive(bool active)
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->SetActive(active);
}

void QB2Body::SetFixedRotation(bool fixedRotation)
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->SetFixedRotation(fixedRotation);
}

void QB2Body::ResetMassData()
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->ResetMassData();
}

QPointF QB2Body::GetPos() const
{
    b2Vec2 pos = b2body_->GetPosition();
    return QPointF(pos.x, pos.y);
}

float QB2Body::GetAngle() const
{
    float angle = qRadiansToDegrees(b2body_->GetAngle());
    angle = MapAngle360(angle);
    return angle;
}

QVector2D QB2Body::GetLinearVelocity() const
{
    b2Vec2 velocity = b2body_->GetLinearVelocity();
    return {velocity.x, velocity.y};
}

float32 QB2Body::GetAngularVelocity() const
{
    return b2body_->GetAngularDamping();
}

float QB2Body::GetLinearDamping() const
{
    return b2body_->GetLinearDamping();
}

float QB2Body::GetAngularDamping() const
{
    return b2body_->GetAngularDamping();
}

float QB2Body::GetGravityScale() const
{
    return b2body_->GetGravityScale();
}

b2BodyType QB2Body::GetType() const
{
    return b2body_->GetType();
}

bool QB2Body::IsBullet() const
{
    return b2body_->IsBullet();
}

bool QB2Body::IsSleepingAllowed() const
{
    return b2body_->IsSleepingAllowed();
}

bool QB2Body::IsAwake() const
{
    return b2body_->IsAwake();
}

bool QB2Body::IsActive() const
{
    return b2body_->IsActive();
}

bool QB2Body::IsFixedRotation() const
{
    return b2body_->IsFixedRotation();
}

QVector2D QB2Body::MapForceToLocal(const QVector2D& force) const
{
    QPointF point = {force.x(), force.y()};
    QTransform transform;
    transform.rotate(GetAngle());
    auto p = transform.map(point);
    return QVector2D(p.x(), p.y());
}

void QB2Body::Update()
{
    // Must be called from main thread
    if (QThread::currentThread() != QApplication::instance()->thread())
        qDebug() << "Update called from not main thread!";
    for(const QB2Fixture& fixture: fixtures_) {
        fixture.Debug();
    }
    setPos(GetPos());
    setRotation(GetAngle());
}

void QB2Body::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    for(const QB2Fixture& fixture: fixtures_) {
        /*painter->save();
        painter->setBrush(QBrush(QColor(Qt::yellow)));
        painter->drawRect(fixture.boundingRect());
        painter->restore();*/
        painter->save();
        PreparePainter(painter);
        fixture.Paint(painter);
        painter->restore();
    }
}

QRectF QB2Body::boundingRect() const
{
    if (fixtures_.size() == 0)
        return {0, 0, 0, 0};
    QB2Fixture& f = *fixtures_.begin();
    QRectF rect = f.boundingRect();
    for(const QB2Fixture& fixture: fixtures_) {
        rect = rect.united(fixture.boundingRect());
    }
    return rect;
}

void QB2Body::PreparePainter(QPainter*) const
{
}

b2Fixture* QB2Body::CreateB2Fixture(const b2FixtureDef& fixtureDef)
{
    QMutexLocker ml(&scene_.GetMutex());
    return b2body_->CreateFixture(&fixtureDef);
}

void QB2Body::DestroyB2Fixture(b2Fixture* fixture)
{
    QMutexLocker ml(&scene_.GetMutex());
    b2body_->DestroyFixture(fixture);
}

void QB2Body::Create(const b2BodyDef& bodyDef)
{
    if (b2body_)
        return;
    b2body_ = scene_.CreateB2Body(bodyDef);
    scene_.AddBody(*this);
}

void QB2Body::Delete()
{
    if (b2body_)
        scene_.DestroyB2Body(b2body_);
    scene_.RemoveBody(*this);
}

QMutex& QB2Body::GetMutex()
{
    return scene_.GetMutex();
}

float QB2Body::MapAngle360(float angle) const
{
    angle = std::fmod(angle, 360.f);
    if (angle < 0)
        angle += 360;
    return angle;
}
