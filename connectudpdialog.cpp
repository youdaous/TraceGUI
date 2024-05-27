#include "connectudpdialog.h"
#include "ui_connectudpdialog.h"

ConnectUDPDialog::ConnectUDPDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConnectUDPDialog)
{
    ui->setupUi(this);
}

ConnectUDPDialog::~ConnectUDPDialog()
{
    delete ui;
}

void ConnectUDPDialog::setTargetIP(QString &IP)
{
    ui->lineEditTIP->setText(IP);
}

void ConnectUDPDialog::setTargetPort(int &port)
{
    ui->lineEditTPort->setText(QString::number(port));
}

void ConnectUDPDialog::setBindPort(int &port)
{
    ui->lineEditBPort->setText(QString::number(port));
}

QString ConnectUDPDialog::getTargetIP()
{
    QString targetIP = ui->lineEditTIP->text();
    return targetIP;
}

int ConnectUDPDialog::getTargetPort()
{
    QString targetport = ui->lineEditTPort->text();
    return targetport.toInt();
}

int ConnectUDPDialog::getBindPort()
{
    QString bindport = ui->lineEditBPort->text();
    return bindport.toInt();
}
