#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "QB2Server.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:

public slots:

private:
    Ui::MainWindow *ui;
    QB2Server server_;
};

#endif // MAINWINDOW_H
