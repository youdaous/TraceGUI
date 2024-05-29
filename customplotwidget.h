#ifndef CUSTOMPLOTWIDGET_H
#define CUSTOMPLOTWIDGET_H

#include "qcustomplot.h"

class CustomPlotWidget : public QCustomPlot
{
    Q_OBJECT

public:
    explicit CustomPlotWidget(QWidget *parent = nullptr);

    void startPlotTest();

private:
    void addPoint(QPoint &position);
    void plotTrajectory();

private:
    double pos_x, pos_y; //unit: m
    // double vel_x, vel_y; //unit: m/s
    QTimer *plotTimer;
    QCPItemLine *arrow;

private slots:
    void do_plotTimer();
};

#endif // CUSTOMPLOTWIDGET_H
