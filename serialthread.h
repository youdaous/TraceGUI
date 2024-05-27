#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialThread : public QThread
{
    Q_OBJECT

public:
    explicit SerialThread(QObject *parent = nullptr);
    ~SerialThread();

    void run() override;

signals:
    void dataReceived(const QByteArray &data);

    void errorOccurred(const QString &message);

public:
    void startSerialCommunication(const QString &portName, const int &baudRate);
    void stopSerialCommunication();

private slots:
    void readData();

private:
    QSerialPort *serialPort;
    bool running;
};

#endif // SERIALTHREAD_H
