#ifndef IBLPORTSETTINGS_H
#define IBLPORTSETTINGS_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QComboBox>

#include <QSettings>
#include <QWidget>

namespace Ui {
class SerialPort;
}

class IblPortSettings : public QWidget
{
    Q_OBJECT

public:
    explicit IblPortSettings(QWidget *parent = 0);
    ~IblPortSettings();

    QString portName;
    int baudRate;
    int bitsData;
    int parity;
    int stopBits;
    int flowControl;

signals:
    void changeSettings();

private slots:
    void on_buttonApply_clicked();

private:
    Ui::SerialPort *ui;

    QSettings *settings;

    void setIBLPortList(QComboBox *cbox);
    void setBaudRateList(QComboBox *cbox);
    void setDataBitsList(QComboBox *cbox);
    void setParityList(QComboBox *cbox);
    void setStopBitsList(QComboBox *cbox);
    void setFlowControlList(QComboBox *cbox);

    void applySettings();
    void readSettings();
    void writeSettings();

};

#endif // IBLPORTSETTINGS_H
