#ifndef SERIAL_H
#define SERIAL_H

#define SIZE_PACK 44

#include <QSerialPort>
#include <QThread>

#include "settings.h"

class Serial : public QThread
{
    Q_OBJECT

public:
    Serial();
    ~Serial();

    void stop();
    void setSettings(Settings *s){ settings = s; }
    qint64 sizeDataBuffer() { return dataBuffer.length() * SIZE_PACK; }

protected:
    virtual void run();

private:
    bool workFlag;
    bool connectPort();
    void disconnectPort();
    void viewPortSettings();

    QList<QByteArray> dataBuffer;

    Settings *settings;
    QSerialPort *serial;
};

#endif // SERIAL_H
