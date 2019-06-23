#include "QB2EventFilter.h"

QB2EventFilter::QB2EventFilter(QB2World& world): world_(world)
{

}

bool QB2EventFilter::eventFilter(QObject* obj, QEvent* event)
{
    return world_.eventFilter(obj, event);
}
