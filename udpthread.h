#ifndef UDPTHREAD_H
#define UDPTHREAD_H

#include <QThread>
#include <QUdpSocket>
#include <QHostAddress>

class UdpThread : public QThread
{
    Q_OBJECT

public:
    explicit UdpThread(QObject *parent = nullptr);
    ~UdpThread();

    void run() override;

signals:
    void dataReceived(const QByteArray &data);
    void errorOccurred(const QString &message);

public slots:
    void startUdpCommunication(const QHostAddress &address, quint16 port);
    void stopUdpCommunication();
    void sendData(const QByteArray &data, const QHostAddress &address, quint16 port);

private slots:
    void readPendingDatagrams();

private:
    QUdpSocket *udpSocket;
    bool running;
};

#endif // UDPTHREAD_H
