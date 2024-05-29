#include "customplotwidget.h"

CustomPlotWidget::CustomPlotWidget(QWidget *parent)
    : QCustomPlot(parent), pos_x(0.0), pos_y(0.0)
{
    // 在这里进行任何自定义的初始化
    setInteractions(QCP::iRangeDrag | QCP::iRangeZoom); // 启动拖拽和缩放功能
    addGraph();
    graph(0)->setPen(QPen(Qt::blue));
    // graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    graph(0)->setAntialiasedFill(false);
    // 设置轴标签
    xAxis->setLabel("x/m");
    yAxis->setLabel("y/m");
    // 设置坐标范围
    xAxis->setRange(-100, 100);
    yAxis->setRange(-100, 100);

    arrow = new QCPItemLine(this);

    plotTimer = new QTimer(this);
    plotTimer->stop(); //先停止定时器
    plotTimer->setTimerType(Qt::CoarseTimer); //定时器精度

    connect(plotTimer, &QTimer::timeout, this, &CustomPlotWidget::do_plotTimer);

    T = 0;
}

void CustomPlotWidget::startPlotTest(bool isStart)
{
    plotTimer->setInterval(100);
    plotTimer->setSingleShot(false); //连续定时
    if (isStart)
    {
        plotTimer->start();
    }
    else
    {
        plotTimer->stop();
    }

}

void CustomPlotWidget::addPoint(QPointF &position)
{
    prepos_x = pos_x;
    prepos_y = pos_y;
    pos_x = position.x();
    pos_y = position.y();
    // posList_x.append(pos_x);
    // posList_y.append(pos_y);
    plotTrajectory();
}

void CustomPlotWidget::plotTrajectory()
{
    graph(0)->addData(pos_x, pos_y);
    // graph(0)->setData(posList_x, posList_y);
    // qDebug()<<pos_x<<pos_y;
    // 添加箭头
    QPointF startPoint(prepos_x, prepos_y);
    QPointF endPoint(pos_x, pos_y); // 终点位置可以调整以显示方向
    arrow->start->setCoords(startPoint);
    arrow->end->setCoords(endPoint);
    arrow->setHead(QCPLineEnding::esSpikeArrow);
    replot();
}

void CustomPlotWidget::do_plotTimer()
{
    // QPointF newPoint(pos_x + (QRandomGenerator::global()->generate() % 10) * 0.1 + 0.1,
    //                 pos_y + (QRandomGenerator::global()->generate() % 10) * 0.1 + 0.1);
    QPointF newPoint(50 * cos(M_PI/50 * T), 50 * sin(M_PI/100 * T));
    addPoint(newPoint);
    ++T;
    // qDebug()<<newPoint;
}
