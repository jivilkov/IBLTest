#include "settings.h"
#include "ui_settings.h"

#include <QDebug>

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    portNameList(ui->comboBoxPortName);

    settings = new QSettings("settings", QSettings::IniFormat);
    serialSettings.portName = settings->value("serial/portName", "").toString();
    serialSettings.baudRate = settings->value("serial/baudRate", QSerialPort::Baud115200).toInt();
    serialSettings.dataBits = settings->value("serial/dataBits", QSerialPort::Data8).toInt();
    serialSettings.parity = settings->value("serial/parity", QSerialPort::NoParity).toInt();
    serialSettings.stopBits = settings->value("serial/stopBits", QSerialPort::OneStop).toInt();
    serialSettings.flowControl = settings->value("serial/flowControl", QSerialPort::NoFlowControl).toInt();
    serialSettings.numberOfRetries = settings->value("serial/numberOfRetries", 3).toInt();
    serialSettings.responseTime = settings->value("serial/responseTime", 200).toInt();

    ui->comboBoxPortName->setCurrentText(serialSettings.portName);
    ui->comboBoxBaudRate->setCurrentText(QString::number(serialSettings.baudRate));
    ui->comboBoxDataBits->setCurrentText(QString::number(serialSettings.dataBits));

    int parity = serialSettings.parity;
    parity ? --parity : parity;
    ui->comboBoxParity->setCurrentIndex(parity);

    ui->comboBoxStopBits->setCurrentText(QString::number(serialSettings.stopBits));
    ui->comboBoxFlowControl->setCurrentIndex(serialSettings.flowControl);
    ui->retriesSpinner->setValue(serialSettings.numberOfRetries);
    ui->timeoutSpinner->setValue(serialSettings.responseTime);

    connect(ui->buttonSerialApply, &QPushButton::clicked, [this](){

        serialSettings.portName = ui->comboBoxPortName->currentText();
        serialSettings.baudRate = ui->comboBoxBaudRate->currentText().toInt();
        serialSettings.dataBits = ui->comboBoxDataBits->currentText().toInt();

        int parity = ui->comboBoxParity->currentIndex();
        serialSettings.parity = parity ? ++parity : parity;

        serialSettings.stopBits = ui->comboBoxStopBits->currentText().toInt();
        serialSettings.flowControl = ui->comboBoxFlowControl->currentIndex();
        serialSettings.numberOfRetries = ui->retriesSpinner->value();
        serialSettings.responseTime = ui->timeoutSpinner->value();

        settings->setValue("serial/portName", serialSettings.portName);
        settings->setValue("serial/baudRate", serialSettings.baudRate);
        settings->setValue("serial/dataBits", serialSettings.dataBits);
        settings->setValue("serial/parity", serialSettings.parity);
        settings->setValue("serial/stopBits", serialSettings.stopBits);
        settings->setValue("serial/flowControl", serialSettings.flowControl);
        settings->setValue("serial/numberOfRetries", serialSettings.numberOfRetries);
        settings->setValue("serial/responseTime", serialSettings.responseTime);

        hide();

    });
}

Settings::~Settings()
{
    delete ui;
}

Settings::Serial Settings::serial() const
{
    return serialSettings;
}

void Settings::portNameList(QComboBox *box)
{
    QString description;
    QString manufacturer;
    QString serialNumber;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName()
             << (!description.isEmpty() ? description : NULL)
             << (!manufacturer.isEmpty() ? manufacturer : NULL)
             << (!serialNumber.isEmpty() ? serialNumber : NULL)
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : NULL)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : NULL);
        box->addItem(list.first(), list);
    }
}
