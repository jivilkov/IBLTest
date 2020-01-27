#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dataModel = new DataModel();
    //connect(dataModel, SIGNAL(layoutChanged(QList<QPersistentModelIndex>,QAbstractItemModel::LayoutChangeHint)),SLOT(scrollToLastVal()));
    ui->tableView->setModel(dataModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalScrollBarPolicy();

    serial = new Serial();

    ui->actionConnect->setDisabled(false);
    ui->actionDisconnect->setDisabled(true);

    settings = NULL;
    serial = NULL;
    requestTimer = NULL;
}

MainWindow::~MainWindow()
{
    if (settings) delete settings;
    if (serial) delete serial;
    if (requestTimer) delete requestTimer;
    delete ui;
}

void MainWindow::on_actionConnect_triggered()
{
    settings = new Settings();
    serial = new Serial();
    serial->setSettings(settings);
    connect(serial, SIGNAL(started()), SLOT(disabledMenuAtConnection()));
    connect(serial, SIGNAL(finished()), SLOT(disabledMenuAtDisconnection()));


    serial->start();
    startRequestTimer();

    IBLData t;
    for (int i=0; i<100; i++){
        t.counter = i;
        dataModel->addTableData(t);
    }
}

void MainWindow::on_actionDisconnect_triggered()
{
    if (serial!=NULL && serial->isRunning()){
        serial->stop();
        stopRequestTimer();
    }
}

void MainWindow::on_actionSettings_triggered()
{
    settings->show();
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

bool MainWindow::startRequestTimer()
{
    if (serial!=NULL && serial->isRunning()){
        requestTimer = new QTimer();
        connect(requestTimer, SIGNAL(timeout()), SLOT(request()));
        requestTimer->start(REQUEST_INTERVAL);
        qDebug() << "request timer started";
        return true;
    } else return false;
}

bool MainWindow::stopRequestTimer()
{
    if (requestTimer!=NULL && requestTimer->isActive()){
        requestTimer->stop();
        requestTimer = NULL;
        qDebug() << "request timer stopped";
        return true;
    } else return false;
}

void MainWindow::request()
{

}

void MainWindow::scrollToLastVal()
{
    ui->tableView->verticalScrollBar()->setValue(ui->tableView->verticalScrollBar()->maximum());
}
