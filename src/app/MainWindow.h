#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "QB2World.h"
#include "QB2Body.h"
#include "QB2Fixture.h"
#include "QB2CircleFixture.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QB2World scene_;
    std::unique_ptr<QB2Body> body;
    std::unique_ptr<QB2Fixture> fixture;
    std::unique_ptr<QB2Body> body2;
    std::unique_ptr<QB2Fixture> fixture2;
    std::unique_ptr<QB2Body> body3;
    std::unique_ptr<QB2Fixture> fixture3;
};

#endif // MAINWINDOW_H
