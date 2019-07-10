#ifndef QB2EVENTFILTER_H
#define QB2EVENTFILTER_H

#include <QObject>

class QKeyEvent;

class QB2EventFilter : public QObject
{
public:
    QB2EventFilter();

   void Update();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

    virtual bool Event(QEvent*) { return false; }
    virtual bool KeyPressEvent(QKeyEvent*) { return false; }
    virtual bool KeyReleaseEvent(QKeyEvent*) { return false; }

private:
    virtual void OnUpdate() = 0;
};

#endif // QB2EVENTFILTER_H
