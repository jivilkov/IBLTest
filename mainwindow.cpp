#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    iblPort = new IBLPort();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonConnect_clicked()
{
    iblPort->start();
}

void MainWindow::on_buttonDisconnect_clicked()
{
    iblPort->stop();
}

void MainWindow::on_buttonSettings_clicked()
{
    iblPort->showSettings();
}
