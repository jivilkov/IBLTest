#include "serial.h"

#include <QDebug>

Serial::Serial()
{
    serial = NULL;
    rawHandler = NULL;
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
    headMatchFlag = false;
    qDebug() << "serial thread started";
    if (connectPort()){

        startRawHandler();

        while (workFlag){

            qApp->processEvents();
            msleep(1);

            if (serial->bytesAvailable() >= BYTES_FOR_PROCESSING){

                if (rawHandler!=NULL && rawHandler->isRunning()){

                    if (!headMatchFlag){

                        unsigned char head;
                        serial->read((char*)&head, 1);
                        if (head == 0xC0){
                            serial->read((char*)&head, 1);
                            if (head == 0xC5) {
                                quint8 header[2] = {0xC0, 0xC5};
                                QByteArray send(QByteArray((char*)header, 2));
                                rawHandler->setRawData(send);
                                rawHandler->setRawData(serial->read(BYTES_FOR_PROCESSING - 2));
                                headMatchFlag = true;
                            }

                        }
                    } else {
                        rawHandler->setRawData(serial->read(BYTES_FOR_PROCESSING));
                    }
                }

            }
        };

        stopRawHandler();
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

    if (serial->open(QIODevice::ReadOnly)){
        qDebug() << "port open";
        viewPortSettings();
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
        serial->deleteLater();
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

void Serial::startRawHandler()
{
    if (rawHandler!=NULL){
        qDebug() << "rawhandler processing starting";
        rawHandler->start();
    } else qDebug() << "error rawhandler processing starting";
}

void Serial::stopRawHandler()
{
    if (rawHandler!=NULL && rawHandler->isRunning()){
        qDebug() << "rawhandler processing stopping";
        rawHandler->stop();
    } else qDebug() << "rawhandler processing stopping";
}
