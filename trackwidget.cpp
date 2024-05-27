#include "trackwidget.h"
#include <QPainter>


TrackWidget::TrackWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumWidth(500);
    m_pixmap = QPixmap(size());  // 初始化 pixmap 大小
    m_pixmap.fill(Qt::white);    // 填充背景颜色
}

void TrackWidget::addPoint(const QPoint &point)
{
    m_points.append(point);
    updatePixmap(); // Update the pixmap when a new point is added
    update(); // Trigger a repaint
}

void TrackWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // Draw the cached pixmap
    painter.drawPixmap(0, 0, m_pixmap);
}

void TrackWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    // Update the pixmap size when the widget is resized
    m_pixmap = QPixmap(size());
    m_pixmap.fill(Qt::white);
    updatePixmap(); // Redraw the pixmap content
    update();
}

void TrackWidget::updatePixmap()
{
    // Create a QPainter to draw on the pixmap
    QPainter painter(&m_pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    // Fill the pixmap with a background color
    m_pixmap.fill(Qt::white);

    // Draw the track using the points
    painter.setPen(QPen(Qt::blue, 2));
    for (int i = 1; i < m_points.size(); ++i) {
        painter.drawLine(m_points[i - 1], m_points[i]);
    }
}
