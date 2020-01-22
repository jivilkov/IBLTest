#include "iblport.h"
#include <QDebug>

#define SIZE_PACK 44

IBLPort::IBLPort()
{
    serial = NULL;
    settings = new IblPortSettings();
    connect(settings, SIGNAL(changeSettings()), this, SLOT(stop()));
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
    if (this->isRunning()){ workFlag = false; }
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

bool IBLPort::connectPort()
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

void IBLPort::disconnectPort()
{
    if (serial!=NULL && serial->isOpen()){
        serial->flush();
        serial->close();
        serial = NULL;
        qDebug() << "Port close";
    }
}

void IBLPort::run()
{
    workFlag = true;
    if (connectPort()){

        qDebug() << "Port open";
        viewSettings();

        // Workin
        qDebug() << "Serial thread started";

        while (workFlag){

            if (serial->bytesAvailable() == SIZE_PACK){
                QByteArray pack = serial->readAll();
                byteList.append(pack);
                serial->flush();
            }

        };

        qDebug() << "Serial thread stopped";
        disconnectPort();

    } else {
        qDebug() << "Error open port,  " << serial->error();
    }

}
