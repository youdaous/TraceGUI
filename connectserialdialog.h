#ifndef CONNECTSERIALDIALOG_H
#define CONNECTSERIALDIALOG_H

#include <QDialog>

namespace Ui {
class ConnectSerialDialog;
}

class ConnectSerialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectSerialDialog(QWidget *parent = nullptr);
    ~ConnectSerialDialog();

    QString getPortName();
    int getBaudRate();

private:
    Ui::ConnectSerialDialog *ui;
};

#endif // CONNECTSERIALDIALOG_H
