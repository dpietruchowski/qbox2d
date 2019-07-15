#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), world_()
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&world_);
    ui->graphicsView->scale(1, -1);
    auto items = world_.items();
    int i = 0;

    world_.Start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
