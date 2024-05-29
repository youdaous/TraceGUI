#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostInfo>
class ConnectUDPDialog;
class TrackWidget;
class QLabel;
class SerialThread;
class UdpThread;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_actConnectUDP_toggled(bool arg1);

    void on_actConnectSerial_toggled(bool arg1);

    void on_btnSendData_clicked();

    void handleSerialData(const QByteArray &data);

    void handleSerialError(const QString &message);

    void handleUdpData(const QByteArray &data);

    void handleUdpError(const QString &message);

private:
    Ui::MainWindow *ui;

    TrackWidget *trackWidget;

    QLabel *labComInfoA;
    QLabel *labComInfoB;
    QLabel *labComInfoC;

    QLabel *labComInfoCom;
    QLabel *labComInfoBaudRate;


    QString localIP;
    QString getlocalIP();
    // UDP通信参数
    QString udpTargetIP;
    int udpTargetPort;
    int udpBindPort;
    // UDP通信类对象
    UdpThread *udpThread;
    // 串口通信参数
    QString serialName;
    int baudRate;
    // 串口通信类对象
    SerialThread *serialThread;

signals:
    void sendDataRequest(const QByteArray &data, const QHostAddress &address, quint16 port);
};
#endif // MAINWINDOW_H
