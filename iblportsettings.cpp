#include "iblportsettings.h"
#include "ui_serialport.h"

#include <QDebug>

IblPortSettings::IblPortSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialPort)
{
    ui->setupUi(this);
    this->setWindowTitle("IBL port settings");

    // Read settings from file
    settings = new QSettings("settings", QSettings::IniFormat);
    readSettings();

    // Set lists values for ComboBox's
    setIBLPortList(ui->comboBoxNumber);
    setBaudRateList(ui->comboBoxBaudRate);
    setDataBitsList(ui->comboBoxDataBits);
    setParityList(ui->comboBoxParity);
    setStopBitsList(ui->comboBoxStopBits);
    setFlowControlList(ui->comboBoxFlowControl);

    // Set selected values in ComboBox's
    ui->comboBoxNumber->setCurrentText(portName);
    ui->comboBoxBaudRate->setCurrentText(QString("%0").arg(baudRate));
    ui->comboBoxDataBits->setCurrentText(QString("%0").arg(bitsData));
    ui->comboBoxParity->setCurrentIndex(parity ? parity - 1 : parity);
    ui->comboBoxStopBits->setCurrentText(QString("%0").arg(stopBits));
    ui->comboBoxFlowControl->setCurrentIndex(flowControl);
}

IblPortSettings::~IblPortSettings()
{
    delete ui;
}

void IblPortSettings::setIBLPortList(QComboBox *cbox)
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
        cbox->addItem(list.first(), list);
    }
}

void IblPortSettings::setBaudRateList(QComboBox *cbox)
{
    cbox->addItem(QString("%0").arg(QSerialPort::Baud1200), QSerialPort::Baud1200);
    cbox->addItem(QString("%0").arg(QSerialPort::Baud2400), QSerialPort::Baud2400);
    cbox->addItem(QString("%0").arg(QSerialPort::Baud4800), QSerialPort::Baud4800);
    cbox->addItem(QString("%0").arg(QSerialPort::Baud9600), QSerialPort::Baud9600);
    cbox->addItem(QString("%0").arg(QSerialPort::Baud19200), QSerialPort::Baud19200);
    cbox->addItem(QString("%0").arg(QSerialPort::Baud38400), QSerialPort::Baud38400);
    cbox->addItem(QString("%0").arg(QSerialPort::Baud57600), QSerialPort::Baud57600);
    cbox->addItem(QString("%0").arg(QSerialPort::Baud115200), QSerialPort::Baud115200);
}

void IblPortSettings::setDataBitsList(QComboBox *cbox)
{
    cbox->addItem(QString("%0").arg(QSerialPort::Data5), QSerialPort::Data5);
    cbox->addItem(QString("%0").arg(QSerialPort::Data6), QSerialPort::Data6);
    cbox->addItem(QString("%0").arg(QSerialPort::Data7), QSerialPort::Data7);
    cbox->addItem(QString("%0").arg(QSerialPort::Data8), QSerialPort::Data8);
}

void IblPortSettings::setParityList(QComboBox *cbox)
{
    cbox->addItem(QString("None"), QSerialPort::NoParity);
    cbox->addItem(QString("Even"), QSerialPort::EvenParity);
    cbox->addItem(QString("Odd"), QSerialPort::OddParity);
    cbox->addItem(QString("Space"), QSerialPort::SpaceParity);
    cbox->addItem(QString("Mark"), QSerialPort::MarkParity);
}

void IblPortSettings::setStopBitsList(QComboBox *cbox)
{
    cbox->addItem(QString("%0").arg(QSerialPort::OneStop), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    cbox->addItem(QString("%0").arg(QSerialPort::OneAndHalfStop), QSerialPort::OneAndHalfStop);
#endif
    cbox->addItem(QString("%0").arg(QSerialPort::TwoStop), QSerialPort::TwoStop);
}

void IblPortSettings::setFlowControlList(QComboBox *cbox)
{
    cbox->addItem(QString("None"), QSerialPort::NoFlowControl);
    cbox->addItem(QString("RTS/CTS"), QSerialPort::HardwareControl);
    cbox->addItem(QString("XON/XOFF"), QSerialPort::SoftwareControl);
}

void IblPortSettings::applySettings()
{
    writeSettings();
    readSettings();
}

void IblPortSettings::readSettings()
{
    portName = settings->value("serial/port", "").toString();
    baudRate = settings->value("serial/baud", QSerialPort::Baud9600).toInt();
    bitsData = settings->value("serial/bits", QSerialPort::Data8).toInt();
    parity = settings->value("serial/part", QSerialPort::NoParity).toInt();
    stopBits = settings->value("serial/stop", QSerialPort::OneStop).toInt();
    flowControl = settings->value("serial/flow", QSerialPort::NoFlowControl).toInt();
}

void IblPortSettings::writeSettings()
{
    settings->setValue("serial/port", ui->comboBoxNumber->currentText());
    settings->setValue("serial/baud", ui->comboBoxBaudRate->itemData(ui->comboBoxBaudRate->currentIndex()).toInt());
    settings->setValue("serial/bits", static_cast<QSerialPort::DataBits>(ui->comboBoxDataBits->itemData(ui->comboBoxDataBits->currentIndex()).toInt()));
    settings->setValue("serial/part", static_cast<QSerialPort::Parity>(ui->comboBoxParity->itemData(ui->comboBoxParity->currentIndex()).toInt()));
    settings->setValue("serial/stop", static_cast<QSerialPort::StopBits>(ui->comboBoxStopBits->itemData(ui->comboBoxStopBits->currentIndex()).toInt()));
    settings->setValue("serial/flow", static_cast<QSerialPort::FlowControl>(ui->comboBoxFlowControl->itemData(ui->comboBoxFlowControl->currentIndex()).toInt()));
    settings->sync();

    emit changeSettings();
}

void IblPortSettings::on_buttonApply_clicked()
{
    applySettings();
}
