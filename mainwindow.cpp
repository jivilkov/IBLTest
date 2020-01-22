#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionConnect->setDisabled(false);
    ui->actionDisconnect->setDisabled(true);

    iblPort = new IBLPort();

    connect(iblPort, SIGNAL(started()), SLOT(disabledMenuAtConnection()));
    connect(iblPort, SIGNAL(finished()), SLOT(disabledMenuAtDisconnection()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConnect_triggered()
{
    iblPort->start();
}

void MainWindow::on_actionDisconnect_triggered()
{
    iblPort->stop();
}

void MainWindow::on_actionSettings_triggered()
{
    iblPort->showSettings();
}

void MainWindow::disabledMenuAtConnection()
{
    ui->actionConnect->setDisabled(true);
    ui->actionDisconnect->setDisabled(false);
}

void MainWindow::disabledMenuAtDisconnection()
{
    ui->actionConnect->setDisabled(false);
    ui->actionDisconnect->setDisabled(true);
}
