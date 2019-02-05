#ifndef QB2WORLDSCENE_H
#define QB2WORLDSCENE_H

#include <QThread>

#include "QB2Scene.h"
#include "QB2World.h"

class QB2WorldScene : public QObject
{
public:
    QB2WorldScene(std::unique_ptr<QB2World> world);
    ~QB2WorldScene();

    QB2Scene& GetScene();
    void SetWorld(std::unique_ptr<QB2World> world);
    void ConnectWorldScene();

private:
    QThread worldThread_;
    QB2Scene scene_;
    std::unique_ptr<QB2World> world_;
};

#endif // QB2WORLDSCENE_H
