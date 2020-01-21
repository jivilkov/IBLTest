#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QComboBox>

#include <QSettings>
#include <QWidget>

namespace Ui {
class SerialPort;
}

class SerialPort : public QWidget
{
    Q_OBJECT

public:
    explicit SerialPort(QWidget *parent = 0);
    ~SerialPort();

private slots:
    void on_buttonApply_clicked();

private:
    Ui::SerialPort *ui;

    QSettings *settings;
    QSerialPort *IBLPort;

    void setIBLPortList(QComboBox *cbox);
    void setBaudRateList(QComboBox *cbox);
    void setDataBitsList(QComboBox *cbox);
    void setParityList(QComboBox *cbox);
    void setStopBitsList(QComboBox *cbox);
    void setFlowControlList(QComboBox *cbox);

    QString port;
    int baud;
    int bits;
    int part;
    int stop;
    int flow;

    void reconnect();
    void applySettings();
    void readSettings();
    void writeSettings();

    void viewCurrentSettings();

private slots:

};

#endif // SERIALPORT_H
