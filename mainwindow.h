#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define REQUEST_INTERVAL 100

#include "settings.h"
#include "serial.h"
#include "datamodel.h"
#include "crc16.h"
#include "rawhandler.h"

#include <QMainWindow>
#include <QTimer>
#include <QScrollBar>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();
    void on_actionSettings_triggered();

    void disabledMenuAtConnection();
    void disabledMenuAtDisconnection();

private:
    Settings *settings;
    Ui::MainWindow *ui;
    Serial *serial;
    DataModel *dataModel;

    RawHandler *rawHandler;

    QTimer *requestTimer;
    bool startRequestTimer();
    bool stopRequestTimer();

private slots:
    void request();
    void scrollToLastVal();


};

#endif // MAINWINDOW_H
