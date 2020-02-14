#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dataModel = new DataModel();
    connect(dataModel,
            SIGNAL(layoutChanged(QList<QPersistentModelIndex>,QAbstractItemModel::LayoutChangeHint)),
            SLOT(scrollToLastVal()));

    ui->tableView->setModel(dataModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalScrollBarPolicy();

    // For selected columns
    itemModel = ui->tableView->selectionModel();
    connect(itemModel,
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            SLOT(selectCols(QItemSelection,QItemSelection)));

    settings = NULL;
    serial = NULL;
    rawHandler = NULL;
    requestTimer = NULL;

    // Default button
    ui->actionConnect->setDisabled(false);
    ui->actionDisconnect->setDisabled(true);
}

MainWindow::~MainWindow()
{
    if (settings) delete settings;
    if (serial) delete serial;
    if (requestTimer) delete requestTimer;
    if (rawHandler) delete rawHandler;
    delete ui;
}

void MainWindow::on_actionConnect_triggered()
{
    rawHandler = new RawHandler();
    settings = new Settings();
    serial = new Serial();
    serial->setRawHandler(rawHandler);
    serial->setSettings(settings);

    connect(serial, SIGNAL(started()), SLOT(disabledMenuAtConnection()));
    connect(serial, SIGNAL(finished()), SLOT(disabledMenuAtDisconnection()));

    serial->start();
    startRequestTimer();
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

QString MainWindow::toBin(int dec)
{
    QString str = "";
    while (dec > 0){
        str += QString("%0").arg(dec%2);
        dec /= 2;
    }
    return str;
}

void MainWindow::request()
{
    QList<IBLData> iblDatas = rawHandler->getIblPacks();
    foreach(IBLData iblData, iblDatas){
        dataModel->addTableData(iblData);
        if (gWindows.length() > 0){
            foreach(GraphWindow *gWindow, gWindows){
                gWindow->setData(iblData);
            }
        }
    }

    foreach(GraphWindow *gWindow, gWindows){
        gWindow->repaintGraph();
    }

    ui->statusBar->showMessage(QString("Ibl data: %0 b").arg(dataModel->count() * 44));

}

void MainWindow::scrollToLastVal()
{
    if (ui->checkBoxAutoScroll->isChecked()){
        ui->tableView->verticalScrollBar()->setValue(ui->tableView->verticalScrollBar()->maximum());
    }
}

void MainWindow::on_buttonClearData_clicked()
{
    dataModel->clear();
}

void MainWindow::on_buttonGraphics_clicked()
{
    GraphWindow *gWindow = new GraphWindow(columnSelection);
    gWindows.append(gWindow);
    ui->tabWidget->addTab(gWindow, "test");
}

void MainWindow::selectCols(QItemSelection selected, QItemSelection deselected){
    int sFirstCol = 0;
    int sLastCol = 0;
    int dFirstCol = 0;
    int dLastCol = 0;

    if (!selected.isEmpty()) {
        if (selected.length()>1){
            for (int i=0; i<selected.length(); i++)

                if (columnSelection.indexOf(selected.at(i).topLeft().column())==-1)
                    columnSelection.append(selected.at(i).topLeft().column());
        } else {

        sFirstCol = selected.first().topLeft().column();
        sLastCol = selected.first().bottomRight().column();
        if (sFirstCol==sLastCol)
            if (columnSelection.indexOf(sFirstCol)==-1)
                columnSelection.append(sFirstCol);
        else {
            for (int i=sFirstCol; i<=sLastCol; i++){
                if (columnSelection.indexOf(sFirstCol)==-1)
                    columnSelection.append(i);
            }
        }
        }
    }

    if (!deselected.isEmpty()) {
        if (deselected.length()>1) {
            for (int i=0; i<deselected.length(); i++)
                columnSelection.removeOne(deselected.at(i).topLeft().column());
        } else {
            dFirstCol = deselected.first().topLeft().column();
            dLastCol = deselected.first().bottomRight().column();
            if (dFirstCol==dLastCol) columnSelection.removeOne(dFirstCol);
            else for (int i=dFirstCol; i<=dLastCol; i++) columnSelection.removeOne(i);
        }
    }

//    qDebug() << "select: " << selected;

//    qDebug() << "deselect: " << deselected;
//    qDebug() << columnSelection;
//    qDebug() << "--------";

}
