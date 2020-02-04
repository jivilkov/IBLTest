#include "icgraphsettings.h"
#include "ui_icgraphsettings.h"
#include <QSpacerItem>
#include <QStandardItemModel>
#include <QDebug>

ICGraphSettings::ICGraphSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ICGraphSettings)
{
    ui->setupUi(this);
    dataPaint = 0;
    grNamesModel = 0;
}

ICGraphSettings::~ICGraphSettings()
{
    if (grNamesModel) delete grNamesModel;
    delete ui;
}

void ICGraphSettings::setDataPaint(ICDataPaint *paint)
{
    dataPaint = paint;
    if (dataPaint) {
        QString str;
        QRect r = dataPaint->renderRect();
        QRectF rr = dataPaint->rangeRect();
        str = QString("%1").arg(r.left());
        ui->rectLeft->setText(str);
        str = QString("%1").arg(r.top());
        ui->rectTop->setText(str);
        str = QString("%1").arg(r.width());
        ui->rectWidth->setText(str);
        str = QString("%1").arg(r.height());
        ui->rectHeight->setText(str);

        ui->rangeLeft->setValue(rr.left());
        ui->rangeTop->setValue(rr.top());
        ui->rangeWidth->setValue(rr.width());
        ui->rangeHeight->setValue(rr.height());
        ui->horizontalSteps->setValue(dataPaint->axXSteps());
        ui->verticalSteps->setValue(dataPaint->axYSteps());
        ui->fixedScale->setChecked(dataPaint->fixYStep());
        ui->scaleStep->setValue(dataPaint->YStep());

        ui->graphName->setText(dataPaint->getGraphTitle());
        ui->graphAxX->setText(dataPaint->getAxXTitle());
        ui->graphAxY->setText(dataPaint->getAxYTitle());
        ui->timeFormat->setText(dataPaint->timeFormat());

        //QStringList lab = dataPaint->graphNameTemp();

        //ui->labelsOverride->setChecked(dataPaint->);
        QCheckBox * check;
        ICDataContainer *cont;
        for (int i = 0; i < dataPaint->dataContainerCount(); i++) {
            cont = dataPaint->dataContainer(i);
            check = new QCheckBox(cont->graphName(), ui->scrollAreaLayout);
            ui->scrollAreaLayout->layout()->addWidget(check);
            graphs.append(check);
            check->setChecked(cont->isVisible());
        }
        ui->scrollAreaLayout->layout()->addItem(new QSpacerItem(20,40,QSizePolicy::Expanding,QSizePolicy::Expanding));

    }
}

void ICGraphSettings::setGraphTempNames(QStringList lst)
{
    grTempNames = lst;
    if (grTempNames.count() > 0) {
        ui->labelsOverride->setChecked(true);
        grNamesModel = new QStandardItemModel(grTempNames.count(),1);
        for (int i = 0; i < grTempNames.count(); i++) {

            QStandardItem *item = new QStandardItem(grTempNames.at(i));
            grNamesModel->setItem(i,0,item);
        }
        ui->labelsList->setModel(grNamesModel);
    }
    else {
        ui->labelsOverride->setChecked(false);
    }
}

QStringList ICGraphSettings::graphTempNames()
{
    return grTempNames;
}

bool ICGraphSettings::isLabelsOverride()
{
    return ui->labelsOverride->isChecked();
}

void ICGraphSettings::applySettings()
{
    if (ui->rangeBox->isChecked()) {
        QRectF rr;
        rr.setLeft(ui->rangeLeft->value());
        rr.setTop(ui->rangeTop->value());
        rr.setWidth(ui->rangeWidth->value());
        rr.setHeight(ui->rangeHeight->value());
        dataPaint->setRangeRect(rr);
    }
    if (ui->gridBox->isChecked()) {
        dataPaint->setAxXSteps(ui->horizontalSteps->value());
        dataPaint->setAxYSteps(ui->verticalSteps->value());
        dataPaint->setFixYStep(ui->fixedScale->isChecked());
        if (ui->fixedScale->isChecked()) {
            dataPaint->setYStep(ui->scaleStep->value());
        }
    }
    for (int i = 0; i < dataPaint->dataContainerCount(); i++) {
        dataPaint->dataContainer(i)->setVisible(graphs.at(i)->isChecked());
    }
    if (ui->labelsOverride->isChecked()) {
        if (grNamesModel) {
            grTempNames.clear();
            for (int i = 0; i < grNamesModel->rowCount(); i++) {
                QStandardItem *item = grNamesModel->item(i);
                grTempNames.append(item->text());
            }
        }
    }
    dataPaint->setGraphTitle(ui->graphName->text());
    dataPaint->setAxXTitle(ui->graphAxX->text());
    dataPaint->setAxYTitle(ui->graphAxY->text());
    dataPaint->setTimeFormat(ui->timeFormat->text());
}

bool ICGraphSettings::isXYScroll()
{
    return ui->allowXYScroll->isChecked();
}

void ICGraphSettings::setXYScroll(bool allow)
{
    ui->allowXYScroll->setChecked(allow);
}

void ICGraphSettings::on_allowXYScroll_clicked()
{

}
