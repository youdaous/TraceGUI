#include "mainwindow.h"
#include "ui_mainwindow.h"
// #include "trackwidget.h"
#include "customplotwidget.h"
#include "connectudpdialog.h"
#include "connectserialdialog.h"
#include "serialthread.h"
#include "udpthread.h"
#include <QRandomGenerator>
#include <QLabel>
#include <QLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serialThread = new SerialThread(this);
    udpThread = new UdpThread(this);
    localIP = getlocalIP();
    setWindowTitle(windowTitle()+"---本机IP："+localIP);

    // 绘图界面
    customPlotWidget = new CustomPlotWidget(this);
    QHBoxLayout *mainlayout =  new QHBoxLayout(ui->centralwidget);
    QHBoxLayout *plotlayout =  new QHBoxLayout(ui->centralwidget);
    plotlayout->addWidget(customPlotWidget);
    QGroupBox *groupBoxPlot = new QGroupBox(this);
    groupBoxPlot->setTitle("目标轨迹");
    groupBoxPlot->setLayout(plotlayout);
    mainlayout->addWidget(groupBoxPlot, 3);
    mainlayout->addWidget(ui->groupBox_state,1);
    // ui->centralwidget->setLayout(mainlayout);

    // 状态栏标签
    labComInfoA = new QLabel(this);
    labComInfoB = new QLabel(this);
    labComInfoC = new QLabel(this);
    labComInfoA->setText("TargetIP:    ");
    labComInfoB->setText("TargetPort:    ");
    labComInfoC->setText("BindPort:    ");
    labComInfoCom = new QLabel(this);
    labComInfoBaudRate = new QLabel(this);
    labComInfoCom->setText("COM端口:    ");
    labComInfoBaudRate->setText("波特率:    ");
    labComInfoA->setMinimumWidth(120);
    labComInfoB->setMinimumWidth(120);
    labComInfoC->setMinimumWidth(120);
    labComInfoCom->setMinimumWidth(120);
    labComInfoBaudRate->setMinimumWidth(120);
    ui->statusbar->addWidget(labComInfoA);
    ui->statusbar->addWidget(labComInfoB);
    ui->statusbar->addWidget(labComInfoC);
    ui->statusbar->addWidget(labComInfoCom);
    ui->statusbar->addWidget(labComInfoBaudRate);

    // 串口通信数据接受与连接错误警告
    connect(serialThread, &SerialThread::dataReceived, this, &MainWindow::handleSerialData);
    connect(serialThread, &SerialThread::errorOccurred, this, &MainWindow::handleSerialError);
    // UDP通信数据接受与连接错误警告
    connect(udpThread, &UdpThread::dataReceived, this, &MainWindow::handleUdpData);
    connect(udpThread, &UdpThread::errorOccurred, this, &MainWindow::handleUdpError);
    // UDP发送数据
    connect(this, &MainWindow::sendDataRequest, udpThread, &UdpThread::sendData);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // // 测试绘图功能
    // // Add a new point to the trackWidget (for demonstration, use random points)
    // QPoint newPoint(QRandomGenerator::global()->generate() % trackWidget->width(),
    //                 QRandomGenerator::global()->generate() % trackWidget->height());
    // trackWidget->addPoint(newPoint);
}

QString MainWindow::getlocalIP()
{
    QString hostName= QHostInfo::localHostName(); //本机主机名
    QHostInfo hostInfo= QHostInfo::fromName(hostName);
    QString localIP= "";
    QList<QHostAddress> addrList= hostInfo.addresses(); //本机 IP 地址列表
    if (addrList.isEmpty())
        return localIP;
    foreach(QHostAddress aHost, addrList)
        if (QAbstractSocket::IPv4Protocol == aHost.protocol())
        {
            localIP= aHost.toString();
            break;
        }
    return localIP;
}


void MainWindow::on_actConnectUDP_toggled(bool arg1)
{
    if (arg1)
    {
        ConnectUDPDialog *conudpDialog = new ConnectUDPDialog();
        conudpDialog->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
        conudpDialog->setTargetIP(localIP);
        int targetPort = 1200, bindPort = 3600;
        conudpDialog->setTargetPort(targetPort);
        conudpDialog->setBindPort(bindPort);

        int ret = conudpDialog->exec();
        if (ret==QDialog::Accepted)
        {
            udpTargetIP = conudpDialog->getTargetIP();
            udpTargetPort = conudpDialog->getTargetPort();
            udpBindPort = conudpDialog->getBindPort();

            QHostAddress targetAddr(localIP);
            udpThread->startUdpCommunication(targetAddr, udpBindPort);

            if (udpThread->getRunnigState())
            {
                labComInfoA->setText("TargetIP: "+udpTargetIP);
                labComInfoB->setText("TargetPort: "+QString::number(udpTargetPort));
                labComInfoC->setText("BindPort: "+QString::number(udpBindPort));
            }
        }
        else
        {
            ui->actConnectUDP->setChecked(false);
        }

        delete conudpDialog;
        // socket绑定端口

    }
    else
    {
        if (udpThread->getRunnigState())
        {
            // 取消udp连接
            udpThread->stopUdpCommunication();
            QString dlgTitle= "消息框";
            QString strInfo = "udp连接已取消！";
            QMessageBox::information(this, dlgTitle, strInfo,
                                     QMessageBox::Ok, QMessageBox::NoButton);

            labComInfoA->setText("TargetIP:    ");
            labComInfoB->setText("TargetPort:    ");
            labComInfoC->setText("BindPort:    ");
        }

    }

}


void MainWindow::on_actConnectSerial_toggled(bool arg1)
{
    if (arg1)
    {
        ConnectSerialDialog *conSerialDialog = new ConnectSerialDialog();
        conSerialDialog->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);

        int ret = conSerialDialog->exec();
        if (ret==QDialog::Accepted)
        {
            serialName = conSerialDialog->getPortName();
            baudRate = conSerialDialog->getBaudRate();

            serialThread->startSerialCommunication(serialName, baudRate);

            if (serialThread->getRunningState())
            {
                labComInfoCom->setText("COM端口: "+serialName);
                labComInfoBaudRate->setText("波特率: "+QString::number(baudRate));
            }
        }
        else
        {
            ui->actConnectSerial->setChecked(false);
        }

        delete conSerialDialog;

    }
    else
    {
        if (serialThread->getRunningState())
        {
            // 取消serial连接
            serialThread->stopSerialCommunication();
            QString dlgTitle= "消息框";
            QString strInfo = "串口连接已取消！";
            QMessageBox::information(this, dlgTitle, strInfo,
                                     QMessageBox::Ok, QMessageBox::NoButton);

            labComInfoCom->setText("COM端口:    ");
            labComInfoBaudRate->setText("波特率:    ");
        }

    }
}

void MainWindow::on_btnSendData_clicked()
{
    // 获取用户输入的要发送的数据
    QByteArray data = ui->lineEditSetDepth->text().toUtf8();
    QHostAddress address(udpTargetIP); // 根据实际情况设置目标地址
    quint16 port = udpTargetPort; // 根据实际情况设置目标端口

    // 通过信号槽机制将数据发送请求传递给子线程
    emit sendDataRequest(data, address, port);
}

void MainWindow::handleSerialData(const QByteArray &data)
{
    // 处理从串口线程接收到的数据，例如显示在UI上
    Q_UNUSED(data)
}

void MainWindow::handleSerialError(const QString &message)
{
    QMessageBox::warning(this, tr("Warning"), message);
}

void MainWindow::handleUdpData(const QByteArray &data)
{
    // 处理从UDP线程接收到的数据，例如显示在UI上
    Q_UNUSED(data)
}

void MainWindow::handleUdpError(const QString &message)
{
    QMessageBox::warning(this, tr("Warning"), message);
}


void MainWindow::on_pushButton_clicked(bool checked)
{
    // Q_UNUSED(checked)
    customPlotWidget->startPlotTest(checked);
}

