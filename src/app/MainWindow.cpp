#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), world_()
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&world_.GetScene());
    ui->graphicsView->scale(1, -1);
    auto items = world_.GetScene().items();
    int i = 0;

    auto Connect = [this](QDoubleSpinBox* spinBox,const std::function<void(double)>& func) {
        connect(spinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), func);
    };

    auto& world = world_;
    //Connect(ui->doubleSpinBoxFX, [&world](double val) { world.force.setX(val); });
    //Connect(ui->doubleSpinBoxFY, [&world](double val) { world.force.setY(val); });
    Connect(ui->doubleSpinBoxVX, [&world](double val) { world.velocity.setX(val); });
    Connect(ui->doubleSpinBoxVY, [&world](double val) { world.velocity.setY(val); });
    Connect(ui->doubleSpinBoxPX, [&world](double val) { world.position.setX(val); });
    Connect(ui->doubleSpinBoxPY, [&world](double val) { world.position.setY(val); });
    world_.Start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
