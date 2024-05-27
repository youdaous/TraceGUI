#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "trackwidget.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QHBoxLayout *mainlayout =  new QHBoxLayout(ui->centralwidget);
    trackwidget = new TrackWidget(parent);
    mainlayout->addWidget(trackwidget);
    mainlayout->addWidget(ui->groupBox_state);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // Add a new point to the trackWidget (for demonstration, use random points)
    QPoint newPoint(QRandomGenerator::global()->generate() % trackwidget->width(),
                    QRandomGenerator::global()->generate() % trackwidget->height());
    trackwidget->addPoint(newPoint);
}

