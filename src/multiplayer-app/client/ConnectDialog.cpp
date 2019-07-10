#include "ConnectDialog.h"
#include "ui_ConnectDialog.h"

#include <QtNetwork>

ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    FillHostComboBox();
    ui->lineEdit->setValidator(new QIntValidator(1, 65535, this));
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

QString ConnectDialog::GetHost()
{
    return ui->comboBox->currentText();
}

quint16 ConnectDialog::GetPort()
{
    return static_cast<quint16>(ui->lineEdit->text().toInt());
}

void ConnectDialog::FillHostComboBox()
{
    QString name = QHostInfo::localHostName();
    if (!name.isEmpty()) {
        ui->comboBox->addItem(name);
        QString domain = QHostInfo::localDomainName();
        if (!domain.isEmpty())
            ui->comboBox->addItem(name + QChar('.') + domain);
    }
    if (name != QLatin1String("localhost"))
        ui->comboBox->addItem(QString("localhost"));
    // find out IP addresses of this machine
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // add non-localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (!ipAddressesList.at(i).isLoopback())
            ui->comboBox->addItem(ipAddressesList.at(i).toString());
    }
}
