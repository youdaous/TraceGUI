#ifndef CUSTOMPLOTWIDGET_H
#define CUSTOMPLOTWIDGET_H

#include "qcustomplot.h"

class CustomPlotWidget : public QCustomPlot
{
    Q_OBJECT

public:
    explicit CustomPlotWidget(QWidget *parent = nullptr);

    void startPlotTest(bool isStart);

    void addPoint(QPointF &position);

private:

    void plotTrajectory();

private:
    double pos_x, pos_y; //unit: m
    double prepos_x, prepos_y; //unit: m
    // double vel_x, vel_y; //unit: m/s
    QTimer *plotTimer;
    QCPItemLine *arrow;
    // QList<double> posList_x, posList_y;

    QCPCurve *curve;

    int T;

private slots:
    void do_plotTimer();
};

#endif // CUSTOMPLOTWIDGET_H
