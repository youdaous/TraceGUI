#ifndef CONNECTUDPDIALOG_H
#define CONNECTUDPDIALOG_H

#include <QDialog>
#include <QString>
namespace Ui {
class ConnectUDPDialog;
}

class ConnectUDPDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectUDPDialog(QWidget *parent = nullptr);
    ~ConnectUDPDialog();

    void setTargetIP(QString &IP);
    void setTargetPort(int &port);
    void setBindPort(int &port);
    QString getTargetIP();
    int getTargetPort();
    int getBindPort();

private:
    Ui::ConnectUDPDialog *ui;
};

#endif // CONNECTUDPDIALOG_H
