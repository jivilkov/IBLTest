#include "serial.h"

#include <QDebug>

Serial::Serial()
{
    serial = NULL;
    workFlag = false;
}

Serial::~Serial()
{
    if (serial) disconnectPort();
}

void Serial::stop()
{
    workFlag = false;
}

void Serial::run()
{
    workFlag = true;
    if (connectPort()){
        qDebug() << "serial thread started";

        while (workFlag){
            if (serial->bytesAvailable() >= SIZE_PACK){
                dataBuffer.append(serial->read(SIZE_PACK));
            }
        };

        disconnectPort();
        qDebug() << "serial thread stopped";
    }
}

bool Serial::connectPort()
{
    settings = new Settings();
    if (!settings){
        qDebug() << "error reading settings file";
        return false;
    }

    serial = new QSerialPort();
    serial->setPortName(settings->serial().portName);
    serial->setBaudRate(settings->serial().baudRate);
    serial->setDataBits((QSerialPort::DataBits)settings->serial().dataBits);
    serial->setParity((QSerialPort::Parity)settings->serial().parity);
    serial->setStopBits((QSerialPort::StopBits)settings->serial().stopBits);
    serial->setFlowControl((QSerialPort::FlowControl)settings->serial().flowControl);

    if (serial->open(QIODevice::ReadWrite)){
        viewPortSettings();
        qDebug() << "port open";
        return true;
    } else {
        qDebug() << "error open port";
        return false;
    }
}

void Serial::disconnectPort()
{
    if (serial!=NULL && serial->isOpen()){
        serial->flush();
        serial->close();
        serial = NULL;
        qDebug() << "port close";
    }
}

void Serial::viewPortSettings()
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
