#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <memory>
#include "RocketLander.h"
#include "RocketWorld.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->scale(1, -1);

    server_.SetPlayerFactory([this] (QTcpSocket& socket) {
        return std::make_unique<RocketLander>(server_.NextId(), socket, server_.GetWorld());
    });
    server_.SetWorld(std::make_unique<RocketWorld>());
    server_.OpenSession();
    server_.GetWorld().Start();

    ui->graphicsView->setScene(&server_.GetWorld());

    ui->serverLabel->setText(server_.GetHost());
    ui->portLabel->setText(QString::number(server_.GetPort()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
