#ifndef ICGRAPHSETTINGS_H
#define ICGRAPHSETTINGS_H

#include <QDialog>
#include <QCheckBox>
#include "icdatapaint.h"

class QStandardItemModel;

namespace Ui {
class ICGraphSettings;
}

class ICGraphSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ICGraphSettings(QWidget *parent = 0);
    ~ICGraphSettings();
    void setDataPaint(ICDataPaint *paint);
    void setGraphTempNames(QStringList lst);
    QStringList graphTempNames();
    bool isLabelsOverride();
    void applySettings();
    bool isXYScroll();
    void setXYScroll(bool allow);

private slots:
    void on_allowXYScroll_clicked();

private:
    Ui::ICGraphSettings *ui;
    ICDataPaint *dataPaint;
    QList <QCheckBox *> graphs;
    QStandardItemModel *grNamesModel;
    QStringList grTempNames;
};

#endif // ICGRAPHSETTINGS_H
