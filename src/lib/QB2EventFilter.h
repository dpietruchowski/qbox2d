#ifndef QB2EVENTFILTER_H
#define QB2EVENTFILTER_H

#include <QObject>
#include "qbox2d_global.h"
#include "QB2Object.h"

class QKeyEvent;
class QB2ContactEvent;

class QBOX2DSHARED_EXPORT QB2EventFilter : public QObject, public QB2Object
{
public:
    QB2EventFilter(QObject* parent = nullptr);

   void Update();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

    virtual bool Event(QEvent*) { return false; }
    virtual bool KeyPressEvent(QKeyEvent*) { return false; }
    virtual bool KeyReleaseEvent(QKeyEvent*) { return false; }
};

#endif // QB2EVENTFILTER_H
