#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), ws(std::make_unique<MyWorld>())
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&ws.GetScene());
    auto items = ws.GetScene().items();
    int i = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}
