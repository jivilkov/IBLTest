#ifndef SERIAL_H
#define SERIAL_H

#define BYTES_FOR_PROCESSING 44

#include "settings.h"
#include "rawhandler.h"
#include <QSerialPort>
#include <QThread>

#include <QApplication>

class Serial : public QThread
{
    Q_OBJECT

public:
    Serial();
    ~Serial();

    void stop();
    void setSettings(Settings *s){ settings = s; }
    void setRawHandler(RawHandler *r){ rawHandler = r; }

protected:
    virtual void run();

private:
    bool workFlag;
    bool headMatchFlag;

    bool connectPort();
    void disconnectPort();
    void viewPortSettings();

    void startRawHandler();
    void stopRawHandler();

    Settings *settings;
    QSerialPort *serial;
    RawHandler *rawHandler;
};

#endif // SERIAL_H
