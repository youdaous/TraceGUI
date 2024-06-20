#include "serialthread.h"
#include <QMessageBox>
#include <QDebug>

SerialThread::SerialThread(QObject *parent)
    : QThread(parent), serialPort(new QSerialPort(this)), running(false)
{
    connect(serialPort, &QSerialPort::readyRead, this, &SerialThread::readData);
}

SerialThread::~SerialThread()
{
    stopSerialCommunication();
    // qDebug()<<"关闭串口，释放线程";
}

void SerialThread::run()
{
    exec(); // 启动事件循环
}

void SerialThread::startSerialCommunication(const QString &portName, const int &baudRate)
{
    if (running) {
        return;
    }

    serialPort->setPortName(portName);
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (serialPort->open(QIODevice::ReadWrite)) {
        running = true;
        start(); // 启动线程
    } else {
        emit errorOccurred(tr("打开端口 %1 错误").arg(portName));
    }
}

void SerialThread::stopSerialCommunication()
{
    if (!running) {
        return;
    }

    running = false;
    if (serialPort->isOpen())
    {
        serialPort->close();
    }
    quit();
    wait();
}

bool SerialThread::getRunningState()
{
    return running;
}

void SerialThread::readData()
{
    if (!serialPort->canReadLine()) {
        return;
    }

    QByteArray data = serialPort->readAll();
    emit dataReceived(data);
}

void SerialThread::sendData(const QByteArray &data)
{
    serialPort->write(data);
}

