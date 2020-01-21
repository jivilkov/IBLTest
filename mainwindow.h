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
    void on_buttonSettings_clicked();

    void on_buttonDisconnect_clicked();

    void on_buttonConnect_clicked();

private:
    Ui::MainWindow *ui;

    IBLPort *iblPort;
    IblPortSettings *serial;





};

#endif // MAINWINDOW_H
