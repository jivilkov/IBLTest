#ifndef SETTINGS_H
#define SETTINGS_H

#include "ibldata.h"

#include <QWidget>
#include <QComboBox>
#include <QSettings>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    struct Serial {
        QString portName;
        int baudRate;
        int dataBits;
        int stopBits;
        int parity;
        int flowControl;
        int responseTime;
        int numberOfRetries;
    };

    explicit Settings(QWidget *parent = 0);
    ~Settings();

    Serial serial() const;

private:
    Ui::Settings *ui;
    void portNameList(QComboBox *box);
    QSettings *settings;
    Serial serialSettings;
};

#endif // SETTINGS_H
