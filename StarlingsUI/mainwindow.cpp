#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, ui->GLWidgetObject, &GLWidget::animate);
    timer->start(50);

    connect(ui->pushButton, &QPushButton::clicked, ui->GLWidgetObject, &GLWidget::addBoid);

}

MainWindow::~MainWindow()
{
    delete ui;
}
