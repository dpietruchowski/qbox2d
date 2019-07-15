#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <memory>
#include "RocketLander.h"
#include "RocketWorld.h"

#include "ConnectDialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->scale(1, -1);

    client_.SetPlayerFactory([] (int id, QB2World& world) {
        return std::make_unique<Rocket>(id, world);
    });
    client_.SetWorld(std::make_unique<RocketWorld>());
    client_.GetWorld().Start();

    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::OnConnectButton);

    ui->graphicsView->setScene(&client_.GetWorld());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnConnectButton()
{
    ConnectDialog dialog;
    int result = dialog.exec();
    if (result == QDialog::Accepted) {
        client_.Connect(dialog.GetHost(), dialog.GetPort());
    }
}
