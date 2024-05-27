#include "udpthread.h"
#include <QMetaObject>

UdpThread::UdpThread(QObject *parent)
    : QThread(parent), udpSocket(new QUdpSocket(parent)), running(false)
{
    connect(udpSocket, &QUdpSocket::readyRead, this, &UdpThread::readPendingDatagrams);

}

UdpThread::~UdpThread()
{
    stopUdpCommunication();
    // qDebug()<<"关闭了udpsocket";
}

void UdpThread::run()
{
    exec(); // 启动事件循环
}

void UdpThread::startUdpCommunication(const QHostAddress &address, quint16 port)
{
    if (running) {
        return;
    }
    // 配置udpsocket
    if (udpSocket->bind(address, port)) {
        running = true;
        start(); // 启动线程
        // qDebug()<<"启动了udpsocket";
    }
    else {
        emit errorOccurred(tr("Failed to bind to port %1").arg(port));
    }
}

void UdpThread::stopUdpCommunication()
{
    if (!running) {
        return;
    }

    running = false;
    if (udpSocket->isOpen()) {
        udpSocket->close();
    }
    quit();
    wait();
}

void UdpThread::sendData(const QByteArray &data, const QHostAddress &address, quint16 port)
{
    if (udpSocket) {
        udpSocket->writeDatagram(data, address, port);
    }
}

void UdpThread::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(static_cast<int>(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());
        emit dataReceived(datagram);
    }
}
