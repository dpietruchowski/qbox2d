#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = nullptr);
    ~ConnectDialog();

    QString GetHost();
    quint16 GetPort();

private:
    void FillHostComboBox();

private:
    Ui::ConnectDialog *ui;
};

#endif // CONNECTDIALOG_H
