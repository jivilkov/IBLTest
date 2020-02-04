/********************************************************************************
** Form generated from reading UI file 'icgraphsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ICGRAPHSETTINGS_H
#define UI_ICGRAPHSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ICGraphSettings
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *graphTab;
    QHBoxLayout *horizontalLayout_26;
    QScrollArea *graphArea;
    QWidget *scrollAreaLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_13;
    QVBoxLayout *verticalLayout_14;
    QGroupBox *paramsBox;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_27;
    QLineEdit *graphName;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_25;
    QLineEdit *graphAxX;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_26;
    QLineEdit *graphAxY;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *timeFormat;
    QCheckBox *allowXYScroll;
    QGroupBox *labelsOverride;
    QVBoxLayout *verticalLayout_13;
    QListView *labelsList;
    QVBoxLayout *verticalLayout_15;
    QGroupBox *sizeBox;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_15;
    QLineEdit *rectLeft;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_14;
    QLineEdit *rectTop;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_16;
    QLineEdit *rectWidth;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_17;
    QLineEdit *rectHeight;
    QGroupBox *rangeBox;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_19;
    QDoubleSpinBox *rangeLeft;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_18;
    QDoubleSpinBox *rangeTop;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_20;
    QDoubleSpinBox *rangeWidth;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_21;
    QDoubleSpinBox *rangeHeight;
    QGroupBox *gridBox;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_23;
    QSpinBox *horizontalSteps;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_22;
    QSpinBox *verticalSteps;
    QGroupBox *fixedScale;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_24;
    QDoubleSpinBox *scaleStep;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ICGraphSettings)
    {
        if (ICGraphSettings->objectName().isEmpty())
            ICGraphSettings->setObjectName(QLatin1String("ICGraphSettings"));
        ICGraphSettings->resize(745, 558);
        verticalLayout = new QVBoxLayout(ICGraphSettings);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QLatin1String("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(ICGraphSettings);
        tabWidget->setObjectName(QLatin1String("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Rounded);
        graphTab = new QWidget();
        graphTab->setObjectName(QLatin1String("graphTab"));
        horizontalLayout_26 = new QHBoxLayout(graphTab);
        horizontalLayout_26->setSpacing(2);
        horizontalLayout_26->setObjectName(QLatin1String("horizontalLayout_26"));
        horizontalLayout_26->setContentsMargins(2, 2, 2, 2);
        graphArea = new QScrollArea(graphTab);
        graphArea->setObjectName(QLatin1String("graphArea"));
        graphArea->setWidgetResizable(true);
        scrollAreaLayout = new QWidget();
        scrollAreaLayout->setObjectName(QLatin1String("scrollAreaLayout"));
        scrollAreaLayout->setGeometry(QRect(0, 0, 341, 504));
        verticalLayout_2 = new QVBoxLayout(scrollAreaLayout);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QLatin1String("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        label_13 = new QLabel(scrollAreaLayout);
        label_13->setObjectName(QLatin1String("label_13"));

        verticalLayout_2->addWidget(label_13);

        graphArea->setWidget(scrollAreaLayout);

        horizontalLayout_26->addWidget(graphArea);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName(QLatin1String("verticalLayout_14"));
        paramsBox = new QGroupBox(graphTab);
        paramsBox->setObjectName(QLatin1String("paramsBox"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(paramsBox->sizePolicy().hasHeightForWidth());
        paramsBox->setSizePolicy(sizePolicy);
        verticalLayout_12 = new QVBoxLayout(paramsBox);
        verticalLayout_12->setSpacing(2);
        verticalLayout_12->setObjectName(QLatin1String("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QLatin1String("horizontalLayout_25"));
        label_27 = new QLabel(paramsBox);
        label_27->setObjectName(QLatin1String("label_27"));
        label_27->setMinimumSize(QSize(40, 0));

        horizontalLayout_25->addWidget(label_27);

        graphName = new QLineEdit(paramsBox);
        graphName->setObjectName(QLatin1String("graphName"));
        graphName->setReadOnly(true);

        horizontalLayout_25->addWidget(graphName);


        verticalLayout_12->addLayout(horizontalLayout_25);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QLatin1String("horizontalLayout_23"));
        label_25 = new QLabel(paramsBox);
        label_25->setObjectName(QLatin1String("label_25"));
        label_25->setMinimumSize(QSize(40, 0));

        horizontalLayout_23->addWidget(label_25);

        graphAxX = new QLineEdit(paramsBox);
        graphAxX->setObjectName(QLatin1String("graphAxX"));
        graphAxX->setReadOnly(true);

        horizontalLayout_23->addWidget(graphAxX);


        verticalLayout_12->addLayout(horizontalLayout_23);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QLatin1String("horizontalLayout_24"));
        label_26 = new QLabel(paramsBox);
        label_26->setObjectName(QLatin1String("label_26"));
        label_26->setMinimumSize(QSize(40, 0));

        horizontalLayout_24->addWidget(label_26);

        graphAxY = new QLineEdit(paramsBox);
        graphAxY->setObjectName(QLatin1String("graphAxY"));
        graphAxY->setReadOnly(true);

        horizontalLayout_24->addWidget(graphAxY);


        verticalLayout_12->addLayout(horizontalLayout_24);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QLatin1String("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(paramsBox);
        label->setObjectName(QLatin1String("label"));

        horizontalLayout->addWidget(label);

        timeFormat = new QLineEdit(paramsBox);
        timeFormat->setObjectName(QLatin1String("timeFormat"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(timeFormat->sizePolicy().hasHeightForWidth());
        timeFormat->setSizePolicy(sizePolicy1);
        timeFormat->setMaximumSize(QSize(110, 16777215));

        horizontalLayout->addWidget(timeFormat);


        verticalLayout_12->addLayout(horizontalLayout);

        allowXYScroll = new QCheckBox(paramsBox);
        allowXYScroll->setObjectName(QLatin1String("allowXYScroll"));

        verticalLayout_12->addWidget(allowXYScroll);


        verticalLayout_14->addWidget(paramsBox);

        labelsOverride = new QGroupBox(graphTab);
        labelsOverride->setObjectName(QLatin1String("labelsOverride"));
        labelsOverride->setCheckable(true);
        labelsOverride->setChecked(false);
        verticalLayout_13 = new QVBoxLayout(labelsOverride);
        verticalLayout_13->setSpacing(2);
        verticalLayout_13->setObjectName(QLatin1String("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(5, 5, 5, 5);
        labelsList = new QListView(labelsOverride);
        labelsList->setObjectName(QLatin1String("labelsList"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelsList->sizePolicy().hasHeightForWidth());
        labelsList->setSizePolicy(sizePolicy2);
        labelsList->setMaximumSize(QSize(180, 16777215));

        verticalLayout_13->addWidget(labelsList);


        verticalLayout_14->addWidget(labelsOverride);


        horizontalLayout_26->addLayout(verticalLayout_14);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setObjectName(QLatin1String("verticalLayout_15"));
        sizeBox = new QGroupBox(graphTab);
        sizeBox->setObjectName(QLatin1String("sizeBox"));
        sizePolicy.setHeightForWidth(sizeBox->sizePolicy().hasHeightForWidth());
        sizeBox->setSizePolicy(sizePolicy);
        sizeBox->setCheckable(false);
        verticalLayout_8 = new QVBoxLayout(sizeBox);
        verticalLayout_8->setSpacing(2);
        verticalLayout_8->setObjectName(QLatin1String("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QLatin1String("horizontalLayout_13"));
        label_15 = new QLabel(sizeBox);
        label_15->setObjectName(QLatin1String("label_15"));
        label_15->setMinimumSize(QSize(40, 0));

        horizontalLayout_13->addWidget(label_15);

        rectLeft = new QLineEdit(sizeBox);
        rectLeft->setObjectName(QLatin1String("rectLeft"));
        rectLeft->setMaximumSize(QSize(120, 16777215));
        rectLeft->setReadOnly(true);

        horizontalLayout_13->addWidget(rectLeft);


        verticalLayout_8->addLayout(horizontalLayout_13);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QLatin1String("horizontalLayout_12"));
        label_14 = new QLabel(sizeBox);
        label_14->setObjectName(QLatin1String("label_14"));
        label_14->setMinimumSize(QSize(40, 0));

        horizontalLayout_12->addWidget(label_14);

        rectTop = new QLineEdit(sizeBox);
        rectTop->setObjectName(QLatin1String("rectTop"));
        rectTop->setMinimumSize(QSize(120, 0));
        rectTop->setMaximumSize(QSize(120, 16777215));
        rectTop->setReadOnly(true);

        horizontalLayout_12->addWidget(rectTop);


        verticalLayout_8->addLayout(horizontalLayout_12);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QLatin1String("horizontalLayout_14"));
        label_16 = new QLabel(sizeBox);
        label_16->setObjectName(QLatin1String("label_16"));
        label_16->setMinimumSize(QSize(40, 0));

        horizontalLayout_14->addWidget(label_16);

        rectWidth = new QLineEdit(sizeBox);
        rectWidth->setObjectName(QLatin1String("rectWidth"));
        rectWidth->setMaximumSize(QSize(120, 16777215));
        rectWidth->setReadOnly(true);

        horizontalLayout_14->addWidget(rectWidth);


        verticalLayout_8->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QLatin1String("horizontalLayout_15"));
        label_17 = new QLabel(sizeBox);
        label_17->setObjectName(QLatin1String("label_17"));
        label_17->setMinimumSize(QSize(40, 0));

        horizontalLayout_15->addWidget(label_17);

        rectHeight = new QLineEdit(sizeBox);
        rectHeight->setObjectName(QLatin1String("rectHeight"));
        rectHeight->setMaximumSize(QSize(120, 16777215));
        rectHeight->setReadOnly(true);

        horizontalLayout_15->addWidget(rectHeight);


        verticalLayout_8->addLayout(horizontalLayout_15);


        verticalLayout_15->addWidget(sizeBox);

        rangeBox = new QGroupBox(graphTab);
        rangeBox->setObjectName(QLatin1String("rangeBox"));
        sizePolicy.setHeightForWidth(rangeBox->sizePolicy().hasHeightForWidth());
        rangeBox->setSizePolicy(sizePolicy);
        rangeBox->setCheckable(true);
        verticalLayout_9 = new QVBoxLayout(rangeBox);
        verticalLayout_9->setSpacing(2);
        verticalLayout_9->setObjectName(QLatin1String("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QLatin1String("horizontalLayout_17"));
        label_19 = new QLabel(rangeBox);
        label_19->setObjectName(QLatin1String("label_19"));
        label_19->setMinimumSize(QSize(40, 0));

        horizontalLayout_17->addWidget(label_19);

        rangeLeft = new QDoubleSpinBox(rangeBox);
        rangeLeft->setObjectName(QLatin1String("rangeLeft"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(rangeLeft->sizePolicy().hasHeightForWidth());
        rangeLeft->setSizePolicy(sizePolicy3);
        rangeLeft->setMinimumSize(QSize(120, 0));
        rangeLeft->setDecimals(4);
        rangeLeft->setMinimum(-1e+10);
        rangeLeft->setMaximum(1e+10);

        horizontalLayout_17->addWidget(rangeLeft);


        verticalLayout_9->addLayout(horizontalLayout_17);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QLatin1String("horizontalLayout_16"));
        label_18 = new QLabel(rangeBox);
        label_18->setObjectName(QLatin1String("label_18"));
        label_18->setMinimumSize(QSize(40, 0));

        horizontalLayout_16->addWidget(label_18);

        rangeTop = new QDoubleSpinBox(rangeBox);
        rangeTop->setObjectName(QLatin1String("rangeTop"));
        sizePolicy3.setHeightForWidth(rangeTop->sizePolicy().hasHeightForWidth());
        rangeTop->setSizePolicy(sizePolicy3);
        rangeTop->setMinimumSize(QSize(120, 0));
        rangeTop->setDecimals(4);
        rangeTop->setMinimum(-1e+10);
        rangeTop->setMaximum(1e+10);

        horizontalLayout_16->addWidget(rangeTop);


        verticalLayout_9->addLayout(horizontalLayout_16);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QLatin1String("horizontalLayout_18"));
        label_20 = new QLabel(rangeBox);
        label_20->setObjectName(QLatin1String("label_20"));
        label_20->setMinimumSize(QSize(40, 0));

        horizontalLayout_18->addWidget(label_20);

        rangeWidth = new QDoubleSpinBox(rangeBox);
        rangeWidth->setObjectName(QLatin1String("rangeWidth"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(rangeWidth->sizePolicy().hasHeightForWidth());
        rangeWidth->setSizePolicy(sizePolicy4);
        rangeWidth->setMinimumSize(QSize(120, 0));
        rangeWidth->setDecimals(4);
        rangeWidth->setMinimum(-1e+10);
        rangeWidth->setMaximum(1e+10);

        horizontalLayout_18->addWidget(rangeWidth);


        verticalLayout_9->addLayout(horizontalLayout_18);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QLatin1String("horizontalLayout_19"));
        label_21 = new QLabel(rangeBox);
        label_21->setObjectName(QLatin1String("label_21"));
        label_21->setMinimumSize(QSize(40, 0));

        horizontalLayout_19->addWidget(label_21);

        rangeHeight = new QDoubleSpinBox(rangeBox);
        rangeHeight->setObjectName(QLatin1String("rangeHeight"));
        sizePolicy3.setHeightForWidth(rangeHeight->sizePolicy().hasHeightForWidth());
        rangeHeight->setSizePolicy(sizePolicy3);
        rangeHeight->setMinimumSize(QSize(120, 0));
        rangeHeight->setDecimals(4);
        rangeHeight->setMinimum(-1e+10);
        rangeHeight->setMaximum(1e+10);

        horizontalLayout_19->addWidget(rangeHeight);


        verticalLayout_9->addLayout(horizontalLayout_19);


        verticalLayout_15->addWidget(rangeBox);

        gridBox = new QGroupBox(graphTab);
        gridBox->setObjectName(QLatin1String("gridBox"));
        sizePolicy.setHeightForWidth(gridBox->sizePolicy().hasHeightForWidth());
        gridBox->setSizePolicy(sizePolicy);
        gridBox->setCheckable(true);
        verticalLayout_10 = new QVBoxLayout(gridBox);
        verticalLayout_10->setSpacing(2);
        verticalLayout_10->setObjectName(QLatin1String("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QLatin1String("horizontalLayout_21"));
        label_23 = new QLabel(gridBox);
        label_23->setObjectName(QLatin1String("label_23"));
        label_23->setMinimumSize(QSize(40, 0));

        horizontalLayout_21->addWidget(label_23);

        horizontalSteps = new QSpinBox(gridBox);
        horizontalSteps->setObjectName(QLatin1String("horizontalSteps"));
        sizePolicy4.setHeightForWidth(horizontalSteps->sizePolicy().hasHeightForWidth());
        horizontalSteps->setSizePolicy(sizePolicy4);
        horizontalSteps->setMinimumSize(QSize(120, 0));
        horizontalSteps->setMinimum(1);
        horizontalSteps->setMaximum(100);

        horizontalLayout_21->addWidget(horizontalSteps);


        verticalLayout_10->addLayout(horizontalLayout_21);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QLatin1String("horizontalLayout_20"));
        label_22 = new QLabel(gridBox);
        label_22->setObjectName(QLatin1String("label_22"));
        label_22->setMinimumSize(QSize(40, 0));

        horizontalLayout_20->addWidget(label_22);

        verticalSteps = new QSpinBox(gridBox);
        verticalSteps->setObjectName(QLatin1String("verticalSteps"));
        sizePolicy4.setHeightForWidth(verticalSteps->sizePolicy().hasHeightForWidth());
        verticalSteps->setSizePolicy(sizePolicy4);
        verticalSteps->setMinimumSize(QSize(120, 0));
        verticalSteps->setMinimum(1);
        verticalSteps->setMaximum(100);

        horizontalLayout_20->addWidget(verticalSteps);


        verticalLayout_10->addLayout(horizontalLayout_20);

        fixedScale = new QGroupBox(gridBox);
        fixedScale->setObjectName(QLatin1String("fixedScale"));
        fixedScale->setFlat(false);
        fixedScale->setCheckable(true);
        fixedScale->setChecked(false);
        verticalLayout_11 = new QVBoxLayout(fixedScale);
        verticalLayout_11->setSpacing(0);
        verticalLayout_11->setObjectName(QLatin1String("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QLatin1String("horizontalLayout_22"));
        label_24 = new QLabel(fixedScale);
        label_24->setObjectName(QLatin1String("label_24"));
        label_24->setMinimumSize(QSize(40, 0));

        horizontalLayout_22->addWidget(label_24);

        scaleStep = new QDoubleSpinBox(fixedScale);
        scaleStep->setObjectName(QLatin1String("scaleStep"));
        sizePolicy4.setHeightForWidth(scaleStep->sizePolicy().hasHeightForWidth());
        scaleStep->setSizePolicy(sizePolicy4);
        scaleStep->setMinimumSize(QSize(120, 0));
        scaleStep->setMaximum(1e+10);

        horizontalLayout_22->addWidget(scaleStep);


        verticalLayout_11->addLayout(horizontalLayout_22);


        verticalLayout_10->addWidget(fixedScale);


        verticalLayout_15->addWidget(gridBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_15->addItem(verticalSpacer);


        horizontalLayout_26->addLayout(verticalLayout_15);

        tabWidget->addTab(graphTab, QString());

        verticalLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(ICGraphSettings);
        buttonBox->setObjectName(QLatin1String("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ICGraphSettings);
        QObject::connect(buttonBox, SIGNAL(rejected()), ICGraphSettings, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), ICGraphSettings, SLOT(accept()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ICGraphSettings);
    } // setupUi

    void retranslateUi(QDialog *ICGraphSettings)
    {
        ICGraphSettings->setWindowTitle(QApplication::translate("ICGraphSettings", "Graph settings", nullptr));
        label_13->setText(QApplication::translate("ICGraphSettings", "Graphs:", nullptr));
        paramsBox->setTitle(QApplication::translate("ICGraphSettings", "Params", nullptr));
        label_27->setText(QApplication::translate("ICGraphSettings", "Name:", nullptr));
        label_25->setText(QApplication::translate("ICGraphSettings", "Ax X:", nullptr));
        label_26->setText(QApplication::translate("ICGraphSettings", "Ax Y:", nullptr));
        label->setText(QApplication::translate("ICGraphSettings", "Time Format:", nullptr));
        allowXYScroll->setText(QApplication::translate("ICGraphSettings", "Allow XY scroll", nullptr));
        labelsOverride->setTitle(QApplication::translate("ICGraphSettings", "Labels override", nullptr));
        sizeBox->setTitle(QApplication::translate("ICGraphSettings", "Graph szie", nullptr));
        label_15->setText(QApplication::translate("ICGraphSettings", "Left:", nullptr));
        label_14->setText(QApplication::translate("ICGraphSettings", "Top:", nullptr));
        label_16->setText(QApplication::translate("ICGraphSettings", "Width:", nullptr));
        label_17->setText(QApplication::translate("ICGraphSettings", "Height:", nullptr));
        rangeBox->setTitle(QApplication::translate("ICGraphSettings", "Graph range", nullptr));
        label_19->setText(QApplication::translate("ICGraphSettings", "Left:", nullptr));
        label_18->setText(QApplication::translate("ICGraphSettings", "Top:", nullptr));
        label_20->setText(QApplication::translate("ICGraphSettings", "Width:", nullptr));
        label_21->setText(QApplication::translate("ICGraphSettings", "Height:", nullptr));
        gridBox->setTitle(QApplication::translate("ICGraphSettings", "Grid", nullptr));
        label_23->setText(QApplication::translate("ICGraphSettings", "Horiz.:", nullptr));
        label_22->setText(QApplication::translate("ICGraphSettings", "Vertical:", nullptr));
        fixedScale->setTitle(QApplication::translate("ICGraphSettings", "Fixed scale", nullptr));
        label_24->setText(QApplication::translate("ICGraphSettings", "Step:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(graphTab), QApplication::translate("ICGraphSettings", "Graph", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ICGraphSettings: public Ui_ICGraphSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ICGRAPHSETTINGS_H
