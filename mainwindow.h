#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "iblport.h"
#include "iblportsettings.h"

#include <QMainWindow>

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
    Ui::MainWindow *ui;

    IBLPort *iblPort;
    IblPortSettings *serial;





};

#endif // MAINWINDOW_H
