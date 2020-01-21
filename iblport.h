#ifndef IBLPORT_H
#define IBLPORT_H

#include <QSerialPort>
#include <QThread>

#include "iblportsettings.h"

class IBLPort : public QThread
{
    Q_OBJECT

public:
    IBLPort();
    ~IBLPort();

    void showSettings();
    void stop();

private:
    IblPortSettings *settings;
    QSerialPort *serial;
    void viewSettings();
    bool workFlag;

    bool connect();
    void disconnect();

private slots:
    void reconnect();

protected:
    virtual void run();

};

#endif // IBLPORT_H
