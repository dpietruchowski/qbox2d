#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene_);
    ui->graphicsView->setMouseTracking(true);
    body = scene_.CreateUPtrBody({10, 10});
    fixture = body->CreateCircleUPtrFixture(10, {1, 1, 1});
    fixture2 = body->CreatePolygonUPtrFixture(
    {{20, 20},
     {40, 20},
     {20, 40},
     {40, 40}},
    {1, 1, 1});

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]() { scene_.Step(); });
    timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}
