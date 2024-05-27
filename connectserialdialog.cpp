#include "connectserialdialog.h"
#include "ui_connectserialdialog.h"
#include <QtSerialPort/QSerialPortInfo>

ConnectSerialDialog::ConnectSerialDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConnectSerialDialog)
{
    ui->setupUi(this);
    for (QSerialPortInfo &portinfo : QSerialPortInfo::availablePorts())
    {
        ui->comboBoxCom->addItem(portinfo.portName());
    }
    for (int &baud : QSerialPortInfo::standardBaudRates())
    {
        ui->comboBoxBaud->addItem(QString::number(baud));
    }
    ui->comboBoxBaud->setCurrentText("115200");
}

ConnectSerialDialog::~ConnectSerialDialog()
{
    delete ui;
}

QString ConnectSerialDialog::getPortName()
{
    QString portName;
    portName = ui->comboBoxCom->currentText();
    return portName;
}

int ConnectSerialDialog::getBaudRate()
{
    int baudRate;
    baudRate = ui->comboBoxBaud->currentText().toInt();
    return baudRate;
}
