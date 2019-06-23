#ifndef QB2EVENTFILTER_H
#define QB2EVENTFILTER_H

#include <QObject>

#include "QB2World.h"

class QB2EventFilter : public QObject
{
public:
    QB2EventFilter(QB2World& world);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    QB2World& world_;
};

#endif // QB2EVENTFILTER_H
