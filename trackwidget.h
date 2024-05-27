#ifndef TRACKWIDGET_H
#define TRACKWIDGET_H

#include <QWidget>

class TrackWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TrackWidget(QWidget *parent = nullptr);
    void addPoint(const QPoint &point);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QVector<QPoint> m_points;
    QPixmap m_pixmap;
    void updatePixmap();

signals:

};

#endif // TRACKWIDGET_H
