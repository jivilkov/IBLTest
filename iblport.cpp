#include "iblport.h"

#include <QDebug>

IBLPort::IBLPort()
{
    serial = NULL;
    settings = new IblPortSettings();
    connect(settings, SIGNAL(changeSettings()), this, SLOT(reconnect()));
}

IBLPort::~IBLPort()
{
    if (settings) delete settings;
    if (serial) delete serial;
}

void IBLPort::showSettings()
{
    if (settings){ settings->show(); }
}

void IBLPort::stop()
{
    workFlag = false;
}

void IBLPort::viewSettings()
{
    if (serial!=NULL && serial->isOpen()){
        qDebug() << "IBLPort name: " << serial->portName();
        qDebug() << "Baud rate: " << serial->baudRate();
        qDebug() << "Data bits: " << serial->dataBits();
        qDebug() << "Parity:" << serial->parity();
        qDebug() << "Stop bits: " << serial->stopBits();
        qDebug() << "Flow control: " << serial->flowControl();
    }
}

bool IBLPort::connect()
{
    serial = new QSerialPort();
    serial->setPortName(settings->portName);
    serial->setBaudRate(settings->baudRate);
    serial->setDataBits(QSerialPort::DataBits(settings->bitsData));
    serial->setParity(QSerialPort::Parity(settings->parity));
    serial->setStopBits(QSerialPort::StopBits(settings->stopBits));
    serial->setFlowControl(QSerialPort::FlowControl(settings->flowControl));
    if (serial->open(QIODevice::ReadWrite)){ return true; }
    else return false;

}

void IBLPort::disconnect()
{
    if (serial!=NULL && serial->isOpen()) {
        serial->flush();
        serial->close();
        serial = NULL;
        qDebug() << "Com port close";
    }
}

void IBLPort::reconnect()
{
    workFlag = false;
    disconnect();
    connect();
}

void IBLPort::run()
{
    workFlag = true;
    if (connect()) {
        qDebug() << "Port connect";

        // Делаем вид, что работаем
        while (workFlag);
        if (!workFlag);

    } else {
        qDebug() << "error open port,  " << serial->error();
    }
}
