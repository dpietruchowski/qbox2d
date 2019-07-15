#ifndef QB2EVENTFILTER_H
#define QB2EVENTFILTER_H

#include <QObject>
#include "qbox2d_global.h"

class QKeyEvent;
class QB2ContactEvent;

class QBOX2DSHARED_EXPORT QB2EventFilter : public QObject
{
public:
    QB2EventFilter(QObject* parent = nullptr);

   void Update();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

    virtual bool Event(QEvent*) { return false; }
    virtual bool KeyPressEvent(QKeyEvent*) { return false; }
    virtual bool KeyReleaseEvent(QKeyEvent*) { return false; }
    virtual bool BeginContact(QB2ContactEvent*) { return false; }
    virtual bool EndContact(QB2ContactEvent*) { return false; }
    virtual bool PreSolveContact(QB2ContactEvent*) { return false; }
    virtual bool PostSolveContact(QB2ContactEvent*) { return false; }

private:
    virtual void OnUpdate() {};
};

#endif // QB2EVENTFILTER_H
