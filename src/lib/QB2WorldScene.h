#ifndef QB2WORLDSCENE_H
#define QB2WORLDSCENE_H

#include <QThread>

#include "QB2Scene.h"
#include "QB2World.h"
#include "QB2EventFilter.h"

class QB2WorldScene : public QObject
{
public:
    QB2WorldScene(std::unique_ptr<QB2World> world);
    ~QB2WorldScene();

    QB2Scene& GetScene();

    template<typename WorldType>
    WorldType& GetWorld() { return dynamic_cast<WorldType&>(*world_); }
    void SetWorld(std::unique_ptr<QB2World> world);
    void AfterWorldSet();
    void ConnectWorldScene();

private:
    QThread worldThread_;
    QB2Scene scene_;
    std::unique_ptr<QB2World> world_;
    std::unique_ptr<QB2EventFilter> eventFilter_;
};

#endif // QB2WORLDSCENE_H
