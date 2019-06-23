#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), ws(std::make_unique<RocketLander>())
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&ws.GetScene());
    auto items = ws.GetScene().items();
    int i = 0;

    auto Connect = [this](QDoubleSpinBox* spinBox,const std::function<void(double)>& func) {
        connect(spinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), func);
    };

    auto& world = ws.GetWorld<RocketLander>();
    //Connect(ui->doubleSpinBoxFX, [&world](double val) { world.force.setX(val); });
    //Connect(ui->doubleSpinBoxFY, [&world](double val) { world.force.setY(val); });
    Connect(ui->doubleSpinBoxVX, [&world](double val) { world.velocity.setX(val); });
    Connect(ui->doubleSpinBoxVY, [&world](double val) { world.velocity.setY(val); });
    Connect(ui->doubleSpinBoxPX, [&world](double val) { world.position.setX(val); });
    Connect(ui->doubleSpinBoxPY, [&world](double val) { world.position.setY(val); });
}

MainWindow::~MainWindow()
{
    delete ui;
}
