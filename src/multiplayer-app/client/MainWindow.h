#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QB2Client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void OnConnectButton();

signals:

private:
    Ui::MainWindow *ui;
    QB2Client client_;
};

#endif // MAINWINDOW_H
