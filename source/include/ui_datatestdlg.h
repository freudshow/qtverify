/********************************************************************************
** Form generated from reading UI file 'datatestdlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATATESTDLG_H
#define UI_DATATESTDLG_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3GroupBox>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataTestDlgClass
{
public:
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    Q3ButtonGroup *buttonGroup;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    Q3ButtonGroup *buttonGroup_2;
    QGridLayout *gridLayout;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QLineEdit *lineEdit;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QLabel *label_6;
    QLineEdit *lineEdit_5;
    QLabel *label_7;
    QGroupBox *groupBox_heatmeter;
    QGridLayout *gridLayout_13;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_12;
    QLabel *label_25;
    QLineEdit *lnEditMeterNo;
    QLabel *label_26;
    QLineEdit *lnEditVolumn0;
    QLabel *label_27;
    QLineEdit *lnEditVolumn1;
    QLabel *label_28;
    QLineEdit *lnEditEnergy0;
    QLabel *label_29;
    QLineEdit *lnEditEnergy1;
    QLabel *label_31;
    QLineEdit *lnEditVolumnError;
    QLabel *label_32;
    QLineEdit *lnEditEnergyError;
    QPushButton *btnReadMeterNo;
    QPushButton *btnReadMeterData;
    QPushButton *pushButton_7;
    QPushButton *btnSetVerifyStatus;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_10;
    QLabel *label_24;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_11;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_9;
    QPushButton *btnWaterIn;
    QPushButton *btnValveBig;
    QPushButton *btnValveMiddle1;
    QPushButton *btnValveSmall;
    QPushButton *btnValveMiddle2;
    QPushButton *btnWaterOut;
    QPushButton *btnWaterPump;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_18;
    QSpinBox *spinBox1;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnRegulate1;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnQueryStatus;
    QGridLayout *gridLayout_7;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_6;
    QLabel *label_8;
    QLineEdit *lnEditBigBalance;
    QLabel *label_13;
    QLabel *label_9;
    QLineEdit *lnEditSmallBalance;
    QLabel *label_14;
    QLabel *label_10;
    QLineEdit *lnEditFlow;
    QLabel *label_15;
    QLabel *label_11;
    QLineEdit *lnEditTempIn;
    QLabel *label_16;
    QLabel *label_12;
    QLineEdit *lnEditTempOut;
    QLabel *label_17;
    QSpacerItem *verticalSpacer;
    QSpinBox *spinBoxTime;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_8;
    QPushButton *btnParaSet;
    QPushButton *pushButton_4;
    QPushButton *btnStart;
    QPushButton *btnExit;

    void setupUi(QWidget *DataTestDlgClass)
    {
        if (DataTestDlgClass->objectName().isEmpty())
            DataTestDlgClass->setObjectName(QString::fromUtf8("DataTestDlgClass"));
        DataTestDlgClass->resize(711, 627);
        groupBox = new QGroupBox(DataTestDlgClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(11, 11, 691, 173));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        buttonGroup = new Q3ButtonGroup(groupBox);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->setColumnLayout(0, Qt::Vertical);
        gridLayout_2 = new QGridLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(buttonGroup->layout());
        if (boxlayout)
            boxlayout->addLayout(gridLayout_2);
        gridLayout_2->setAlignment(Qt::AlignTop);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        radioButton = new QRadioButton(buttonGroup);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        gridLayout_2->addWidget(radioButton, 0, 0, 1, 1);

        radioButton_2 = new QRadioButton(buttonGroup);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        gridLayout_2->addWidget(radioButton_2, 0, 1, 1, 1);


        gridLayout_5->addWidget(buttonGroup, 0, 0, 1, 1);

        buttonGroup_2 = new Q3ButtonGroup(groupBox);
        buttonGroup_2->setObjectName(QString::fromUtf8("buttonGroup_2"));
        buttonGroup_2->setColumnLayout(0, Qt::Vertical);
        gridLayout = new QGridLayout();
        QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(buttonGroup_2->layout());
        if (boxlayout1)
            boxlayout1->addLayout(gridLayout);
        gridLayout->setAlignment(Qt::AlignTop);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        radioButton_3 = new QRadioButton(buttonGroup_2);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        gridLayout->addWidget(radioButton_3, 0, 0, 1, 1);

        radioButton_4 = new QRadioButton(buttonGroup_2);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));

        gridLayout->addWidget(radioButton_4, 0, 1, 1, 1);


        gridLayout_5->addWidget(buttonGroup_2, 0, 1, 1, 1);

        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        lineEdit = new QLineEdit(groupBox_4);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(lineEdit, 0, 0, 1, 1);

        label = new QLabel(groupBox_4);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 0, 1, 1, 1);


        gridLayout_5->addWidget(groupBox_4, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(190, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 0, 3, 1, 1);

        groupBox_5 = new QGroupBox(groupBox);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_4 = new QGridLayout(groupBox_5);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pushButton = new QPushButton(groupBox_5);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_4->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(groupBox_5);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout_4->addWidget(pushButton_2, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox_5);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_4->addWidget(label_2, 0, 2, 1, 1);

        lineEdit_2 = new QLineEdit(groupBox_5);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        sizePolicy.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(lineEdit_2, 0, 3, 1, 1);

        label_3 = new QLabel(groupBox_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_4->addWidget(label_3, 0, 4, 1, 1);

        lineEdit_3 = new QLineEdit(groupBox_5);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        sizePolicy.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(lineEdit_3, 0, 5, 1, 1);

        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 0, 6, 1, 1);

        label_5 = new QLabel(groupBox_5);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_4->addWidget(label_5, 0, 7, 1, 1);

        lineEdit_4 = new QLineEdit(groupBox_5);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        sizePolicy.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(lineEdit_4, 0, 8, 1, 1);

        label_6 = new QLabel(groupBox_5);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_4->addWidget(label_6, 0, 9, 1, 1);

        lineEdit_5 = new QLineEdit(groupBox_5);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        sizePolicy.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(lineEdit_5, 0, 10, 1, 1);

        label_7 = new QLabel(groupBox_5);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_4->addWidget(label_7, 0, 11, 1, 1);


        gridLayout_5->addWidget(groupBox_5, 1, 0, 1, 4);

        groupBox_heatmeter = new QGroupBox(DataTestDlgClass);
        groupBox_heatmeter->setObjectName(QString::fromUtf8("groupBox_heatmeter"));
        groupBox_heatmeter->setGeometry(QRect(11, 191, 251, 315));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_heatmeter->sizePolicy().hasHeightForWidth());
        groupBox_heatmeter->setSizePolicy(sizePolicy1);
        groupBox_heatmeter->setFlat(false);
        gridLayout_13 = new QGridLayout(groupBox_heatmeter);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        groupBox_9 = new QGroupBox(groupBox_heatmeter);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        gridLayout_12 = new QGridLayout(groupBox_9);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        label_25 = new QLabel(groupBox_9);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy2);

        gridLayout_12->addWidget(label_25, 0, 0, 1, 1);

        lnEditMeterNo = new QLineEdit(groupBox_9);
        lnEditMeterNo->setObjectName(QString::fromUtf8("lnEditMeterNo"));
        sizePolicy.setHeightForWidth(lnEditMeterNo->sizePolicy().hasHeightForWidth());
        lnEditMeterNo->setSizePolicy(sizePolicy);

        gridLayout_12->addWidget(lnEditMeterNo, 0, 1, 1, 4);

        label_26 = new QLabel(groupBox_9);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_12->addWidget(label_26, 1, 0, 1, 1);

        lnEditVolumn0 = new QLineEdit(groupBox_9);
        lnEditVolumn0->setObjectName(QString::fromUtf8("lnEditVolumn0"));
        sizePolicy.setHeightForWidth(lnEditVolumn0->sizePolicy().hasHeightForWidth());
        lnEditVolumn0->setSizePolicy(sizePolicy);

        gridLayout_12->addWidget(lnEditVolumn0, 1, 2, 1, 3);

        label_27 = new QLabel(groupBox_9);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_12->addWidget(label_27, 2, 0, 1, 1);

        lnEditVolumn1 = new QLineEdit(groupBox_9);
        lnEditVolumn1->setObjectName(QString::fromUtf8("lnEditVolumn1"));
        sizePolicy.setHeightForWidth(lnEditVolumn1->sizePolicy().hasHeightForWidth());
        lnEditVolumn1->setSizePolicy(sizePolicy);

        gridLayout_12->addWidget(lnEditVolumn1, 2, 2, 1, 3);

        label_28 = new QLabel(groupBox_9);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout_12->addWidget(label_28, 3, 0, 1, 2);

        lnEditEnergy0 = new QLineEdit(groupBox_9);
        lnEditEnergy0->setObjectName(QString::fromUtf8("lnEditEnergy0"));
        sizePolicy.setHeightForWidth(lnEditEnergy0->sizePolicy().hasHeightForWidth());
        lnEditEnergy0->setSizePolicy(sizePolicy);

        gridLayout_12->addWidget(lnEditEnergy0, 3, 2, 1, 3);

        label_29 = new QLabel(groupBox_9);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout_12->addWidget(label_29, 4, 0, 1, 2);

        lnEditEnergy1 = new QLineEdit(groupBox_9);
        lnEditEnergy1->setObjectName(QString::fromUtf8("lnEditEnergy1"));
        sizePolicy.setHeightForWidth(lnEditEnergy1->sizePolicy().hasHeightForWidth());
        lnEditEnergy1->setSizePolicy(sizePolicy);

        gridLayout_12->addWidget(lnEditEnergy1, 4, 2, 1, 3);

        label_31 = new QLabel(groupBox_9);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout_12->addWidget(label_31, 5, 0, 1, 1);

        lnEditVolumnError = new QLineEdit(groupBox_9);
        lnEditVolumnError->setObjectName(QString::fromUtf8("lnEditVolumnError"));
        sizePolicy.setHeightForWidth(lnEditVolumnError->sizePolicy().hasHeightForWidth());
        lnEditVolumnError->setSizePolicy(sizePolicy);

        gridLayout_12->addWidget(lnEditVolumnError, 5, 2, 1, 3);

        label_32 = new QLabel(groupBox_9);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        gridLayout_12->addWidget(label_32, 6, 0, 1, 1);

        lnEditEnergyError = new QLineEdit(groupBox_9);
        lnEditEnergyError->setObjectName(QString::fromUtf8("lnEditEnergyError"));
        sizePolicy.setHeightForWidth(lnEditEnergyError->sizePolicy().hasHeightForWidth());
        lnEditEnergyError->setSizePolicy(sizePolicy);

        gridLayout_12->addWidget(lnEditEnergyError, 6, 2, 1, 3);

        btnReadMeterNo = new QPushButton(groupBox_9);
        btnReadMeterNo->setObjectName(QString::fromUtf8("btnReadMeterNo"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btnReadMeterNo->sizePolicy().hasHeightForWidth());
        btnReadMeterNo->setSizePolicy(sizePolicy3);

        gridLayout_12->addWidget(btnReadMeterNo, 7, 0, 1, 1);

        btnReadMeterData = new QPushButton(groupBox_9);
        btnReadMeterData->setObjectName(QString::fromUtf8("btnReadMeterData"));
        sizePolicy3.setHeightForWidth(btnReadMeterData->sizePolicy().hasHeightForWidth());
        btnReadMeterData->setSizePolicy(sizePolicy3);

        gridLayout_12->addWidget(btnReadMeterData, 7, 3, 1, 1);

        pushButton_7 = new QPushButton(groupBox_9);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        sizePolicy1.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy1);

        gridLayout_12->addWidget(pushButton_7, 7, 4, 1, 1);

        btnSetVerifyStatus = new QPushButton(groupBox_9);
        btnSetVerifyStatus->setObjectName(QString::fromUtf8("btnSetVerifyStatus"));
        sizePolicy1.setHeightForWidth(btnSetVerifyStatus->sizePolicy().hasHeightForWidth());
        btnSetVerifyStatus->setSizePolicy(sizePolicy1);

        gridLayout_12->addWidget(btnSetVerifyStatus, 7, 1, 1, 1);


        gridLayout_13->addWidget(groupBox_9, 0, 0, 1, 1);

        groupBox_7 = new QGroupBox(DataTestDlgClass);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(11, 513, 251, 101));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(groupBox_7->sizePolicy().hasHeightForWidth());
        groupBox_7->setSizePolicy(sizePolicy4);
        gridLayout_10 = new QGridLayout(groupBox_7);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        label_24 = new QLabel(groupBox_7);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        sizePolicy1.setHeightForWidth(label_24->sizePolicy().hasHeightForWidth());
        label_24->setSizePolicy(sizePolicy1);

        gridLayout_10->addWidget(label_24, 0, 0, 1, 1);

        layoutWidget = new QWidget(DataTestDlgClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(280, 190, 419, 425));
        gridLayout_11 = new QGridLayout(layoutWidget);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout_11->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(layoutWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        gridLayout_9 = new QGridLayout(groupBox_2);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        btnWaterIn = new QPushButton(groupBox_2);
        btnWaterIn->setObjectName(QString::fromUtf8("btnWaterIn"));
        sizePolicy2.setHeightForWidth(btnWaterIn->sizePolicy().hasHeightForWidth());
        btnWaterIn->setSizePolicy(sizePolicy2);
        btnWaterIn->setMaximumSize(QSize(40, 100));
        btnWaterIn->setLayoutDirection(Qt::LeftToRight);
        btnWaterIn->setAutoFillBackground(false);
        btnWaterIn->setAutoDefault(false);
        btnWaterIn->setDefault(false);
        btnWaterIn->setFlat(false);

        gridLayout_9->addWidget(btnWaterIn, 0, 0, 1, 1);

        btnValveBig = new QPushButton(groupBox_2);
        btnValveBig->setObjectName(QString::fromUtf8("btnValveBig"));
        sizePolicy2.setHeightForWidth(btnValveBig->sizePolicy().hasHeightForWidth());
        btnValveBig->setSizePolicy(sizePolicy2);
        btnValveBig->setMaximumSize(QSize(40, 100));
        btnValveBig->setLayoutDirection(Qt::LeftToRight);
        btnValveBig->setAutoFillBackground(false);
        btnValveBig->setAutoDefault(false);
        btnValveBig->setDefault(false);
        btnValveBig->setFlat(false);

        gridLayout_9->addWidget(btnValveBig, 0, 1, 1, 1);

        btnValveMiddle1 = new QPushButton(groupBox_2);
        btnValveMiddle1->setObjectName(QString::fromUtf8("btnValveMiddle1"));
        sizePolicy2.setHeightForWidth(btnValveMiddle1->sizePolicy().hasHeightForWidth());
        btnValveMiddle1->setSizePolicy(sizePolicy2);
        btnValveMiddle1->setMaximumSize(QSize(40, 100));
        btnValveMiddle1->setLayoutDirection(Qt::LeftToRight);
        btnValveMiddle1->setAutoFillBackground(false);
        btnValveMiddle1->setAutoDefault(false);
        btnValveMiddle1->setDefault(false);
        btnValveMiddle1->setFlat(false);

        gridLayout_9->addWidget(btnValveMiddle1, 0, 2, 1, 1);

        btnValveSmall = new QPushButton(groupBox_2);
        btnValveSmall->setObjectName(QString::fromUtf8("btnValveSmall"));
        sizePolicy2.setHeightForWidth(btnValveSmall->sizePolicy().hasHeightForWidth());
        btnValveSmall->setSizePolicy(sizePolicy2);
        btnValveSmall->setMaximumSize(QSize(40, 100));
        btnValveSmall->setLayoutDirection(Qt::LeftToRight);
        btnValveSmall->setAutoFillBackground(false);
        btnValveSmall->setAutoDefault(false);
        btnValveSmall->setDefault(false);
        btnValveSmall->setFlat(false);

        gridLayout_9->addWidget(btnValveSmall, 0, 3, 1, 1);

        btnValveMiddle2 = new QPushButton(groupBox_2);
        btnValveMiddle2->setObjectName(QString::fromUtf8("btnValveMiddle2"));
        sizePolicy2.setHeightForWidth(btnValveMiddle2->sizePolicy().hasHeightForWidth());
        btnValveMiddle2->setSizePolicy(sizePolicy2);
        btnValveMiddle2->setMaximumSize(QSize(40, 100));
        btnValveMiddle2->setLayoutDirection(Qt::LeftToRight);
        btnValveMiddle2->setAutoFillBackground(false);
        btnValveMiddle2->setAutoDefault(false);
        btnValveMiddle2->setDefault(false);
        btnValveMiddle2->setFlat(false);

        gridLayout_9->addWidget(btnValveMiddle2, 0, 4, 1, 1);

        btnWaterOut = new QPushButton(groupBox_2);
        btnWaterOut->setObjectName(QString::fromUtf8("btnWaterOut"));
        sizePolicy2.setHeightForWidth(btnWaterOut->sizePolicy().hasHeightForWidth());
        btnWaterOut->setSizePolicy(sizePolicy2);
        btnWaterOut->setMaximumSize(QSize(40, 100));
        btnWaterOut->setLayoutDirection(Qt::LeftToRight);
        btnWaterOut->setAutoFillBackground(false);
        btnWaterOut->setAutoDefault(false);
        btnWaterOut->setDefault(false);
        btnWaterOut->setFlat(false);

        gridLayout_9->addWidget(btnWaterOut, 0, 5, 1, 1);

        btnWaterPump = new QPushButton(groupBox_2);
        btnWaterPump->setObjectName(QString::fromUtf8("btnWaterPump"));
        sizePolicy2.setHeightForWidth(btnWaterPump->sizePolicy().hasHeightForWidth());
        btnWaterPump->setSizePolicy(sizePolicy2);
        btnWaterPump->setMaximumSize(QSize(40, 100));
        btnWaterPump->setLayoutDirection(Qt::LeftToRight);
        btnWaterPump->setAutoFillBackground(false);
        btnWaterPump->setAutoDefault(false);
        btnWaterPump->setDefault(false);
        btnWaterPump->setFlat(false);

        gridLayout_9->addWidget(btnWaterPump, 0, 6, 1, 1);


        gridLayout_11->addWidget(groupBox_2, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_18 = new QLabel(layoutWidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        horizontalLayout->addWidget(label_18);

        spinBox1 = new QSpinBox(layoutWidget);
        spinBox1->setObjectName(QString::fromUtf8("spinBox1"));
        spinBox1->setMaximum(9999);

        horizontalLayout->addWidget(spinBox1);


        horizontalLayout_2->addLayout(horizontalLayout);

        horizontalSpacer_3 = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        btnRegulate1 = new QPushButton(layoutWidget);
        btnRegulate1->setObjectName(QString::fromUtf8("btnRegulate1"));
        sizePolicy3.setHeightForWidth(btnRegulate1->sizePolicy().hasHeightForWidth());
        btnRegulate1->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(btnRegulate1);

        horizontalSpacer_2 = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnQueryStatus = new QPushButton(layoutWidget);
        btnQueryStatus->setObjectName(QString::fromUtf8("btnQueryStatus"));
        sizePolicy3.setHeightForWidth(btnQueryStatus->sizePolicy().hasHeightForWidth());
        btnQueryStatus->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(btnQueryStatus);


        gridLayout_11->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        groupBox_3 = new QGroupBox(layoutWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy3.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy3);
        gridLayout_6 = new QGridLayout(groupBox_3);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_6->addWidget(label_8, 0, 0, 1, 1);

        lnEditBigBalance = new QLineEdit(groupBox_3);
        lnEditBigBalance->setObjectName(QString::fromUtf8("lnEditBigBalance"));
        sizePolicy.setHeightForWidth(lnEditBigBalance->sizePolicy().hasHeightForWidth());
        lnEditBigBalance->setSizePolicy(sizePolicy);
        lnEditBigBalance->setReadOnly(true);

        gridLayout_6->addWidget(lnEditBigBalance, 0, 1, 1, 1);

        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_6->addWidget(label_13, 0, 2, 1, 1);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_6->addWidget(label_9, 1, 0, 1, 1);

        lnEditSmallBalance = new QLineEdit(groupBox_3);
        lnEditSmallBalance->setObjectName(QString::fromUtf8("lnEditSmallBalance"));
        sizePolicy.setHeightForWidth(lnEditSmallBalance->sizePolicy().hasHeightForWidth());
        lnEditSmallBalance->setSizePolicy(sizePolicy);
        lnEditSmallBalance->setReadOnly(true);

        gridLayout_6->addWidget(lnEditSmallBalance, 1, 1, 1, 1);

        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_6->addWidget(label_14, 1, 2, 1, 1);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_6->addWidget(label_10, 2, 0, 1, 1);

        lnEditFlow = new QLineEdit(groupBox_3);
        lnEditFlow->setObjectName(QString::fromUtf8("lnEditFlow"));
        sizePolicy.setHeightForWidth(lnEditFlow->sizePolicy().hasHeightForWidth());
        lnEditFlow->setSizePolicy(sizePolicy);
        lnEditFlow->setReadOnly(true);

        gridLayout_6->addWidget(lnEditFlow, 2, 1, 1, 1);

        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_6->addWidget(label_15, 2, 2, 1, 1);

        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_6->addWidget(label_11, 3, 0, 1, 1);

        lnEditTempIn = new QLineEdit(groupBox_3);
        lnEditTempIn->setObjectName(QString::fromUtf8("lnEditTempIn"));
        sizePolicy.setHeightForWidth(lnEditTempIn->sizePolicy().hasHeightForWidth());
        lnEditTempIn->setSizePolicy(sizePolicy);
        lnEditTempIn->setReadOnly(true);

        gridLayout_6->addWidget(lnEditTempIn, 3, 1, 1, 1);

        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_6->addWidget(label_16, 3, 2, 1, 1);

        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_6->addWidget(label_12, 4, 0, 1, 1);

        lnEditTempOut = new QLineEdit(groupBox_3);
        lnEditTempOut->setObjectName(QString::fromUtf8("lnEditTempOut"));
        sizePolicy.setHeightForWidth(lnEditTempOut->sizePolicy().hasHeightForWidth());
        lnEditTempOut->setSizePolicy(sizePolicy);
        lnEditTempOut->setReadOnly(true);

        gridLayout_6->addWidget(lnEditTempOut, 4, 1, 1, 1);

        label_17 = new QLabel(groupBox_3);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_6->addWidget(label_17, 4, 2, 1, 1);


        gridLayout_7->addWidget(groupBox_3, 0, 0, 2, 1);

        verticalSpacer = new QSpacerItem(20, 118, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer, 0, 1, 1, 1);

        spinBoxTime = new QSpinBox(layoutWidget);
        spinBoxTime->setObjectName(QString::fromUtf8("spinBoxTime"));
        sizePolicy3.setHeightForWidth(spinBoxTime->sizePolicy().hasHeightForWidth());
        spinBoxTime->setSizePolicy(sizePolicy3);
        spinBoxTime->setValue(45);

        gridLayout_7->addWidget(spinBoxTime, 1, 1, 1, 1);


        gridLayout_11->addLayout(gridLayout_7, 2, 0, 1, 1);

        groupBox_8 = new QGroupBox(layoutWidget);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(groupBox_8->sizePolicy().hasHeightForWidth());
        groupBox_8->setSizePolicy(sizePolicy5);
        gridLayout_8 = new QGridLayout(groupBox_8);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        btnParaSet = new QPushButton(groupBox_8);
        btnParaSet->setObjectName(QString::fromUtf8("btnParaSet"));

        gridLayout_8->addWidget(btnParaSet, 0, 0, 1, 1);

        pushButton_4 = new QPushButton(groupBox_8);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout_8->addWidget(pushButton_4, 0, 1, 1, 1);

        btnStart = new QPushButton(groupBox_8);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));

        gridLayout_8->addWidget(btnStart, 0, 2, 1, 1);

        btnExit = new QPushButton(groupBox_8);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));

        gridLayout_8->addWidget(btnExit, 0, 3, 1, 1);


        gridLayout_11->addWidget(groupBox_8, 3, 0, 1, 1);


        retranslateUi(DataTestDlgClass);

        QMetaObject::connectSlotsByName(DataTestDlgClass);
    } // setupUi

    void retranslateUi(QWidget *DataTestDlgClass)
    {
        DataTestDlgClass->setWindowTitle(QApplication::translate("DataTestDlgClass", "\351\207\207\351\233\206\344\270\216\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("DataTestDlgClass", "\346\200\273\346\243\200\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        buttonGroup->setTitle(QApplication::translate("DataTestDlgClass", "\345\256\211\350\243\205\344\275\215\347\275\256", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("DataTestDlgClass", "\350\277\233\345\217\243", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("DataTestDlgClass", "\345\207\272\345\217\243", 0, QApplication::UnicodeUTF8));
        buttonGroup_2->setTitle(QApplication::translate("DataTestDlgClass", "\347\203\255\351\207\217\345\215\225\344\275\215", 0, QApplication::UnicodeUTF8));
        radioButton_3->setText(QApplication::translate("DataTestDlgClass", "KWH", 0, QApplication::UnicodeUTF8));
        radioButton_4->setText(QApplication::translate("DataTestDlgClass", "MJ", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("DataTestDlgClass", "\346\234\200\345\260\217\346\270\251\345\267\256", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DataTestDlgClass", "K", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("DataTestDlgClass", "\346\240\207\345\207\206\346\270\251\345\272\246\350\256\241", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("DataTestDlgClass", "\351\207\207\351\233\206", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("DataTestDlgClass", "\345\201\234\346\255\242", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DataTestDlgClass", "\350\277\233\345\217\243", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("DataTestDlgClass", "\316\251", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("DataTestDlgClass", "\342\204\203", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("DataTestDlgClass", "\345\207\272\345\217\243", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("DataTestDlgClass", "\316\251", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("DataTestDlgClass", "\342\204\203", 0, QApplication::UnicodeUTF8));
        groupBox_heatmeter->setTitle(QApplication::translate("DataTestDlgClass", "\346\243\200\345\256\232\347\203\255\351\207\217\350\241\250", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("DataTestDlgClass", "1", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("DataTestDlgClass", "\350\241\250\345\217\267", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("DataTestDlgClass", "V0(L)", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("DataTestDlgClass", "V1(L)", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("DataTestDlgClass", "E0(kwh)", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("DataTestDlgClass", "E1(kwh)", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("DataTestDlgClass", "\316\264v(%)", 0, QApplication::UnicodeUTF8));
        label_32->setText(QApplication::translate("DataTestDlgClass", "\316\264e(%)", 0, QApplication::UnicodeUTF8));
        btnReadMeterNo->setText(QApplication::translate("DataTestDlgClass", "\350\257\273\345\217\226\n"
"\350\241\250\345\217\267", 0, QApplication::UnicodeUTF8));
        btnReadMeterData->setText(QApplication::translate("DataTestDlgClass", "\350\257\273\350\241\250\n"
"\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("DataTestDlgClass", "d", 0, QApplication::UnicodeUTF8));
        btnSetVerifyStatus->setText(QApplication::translate("DataTestDlgClass", "\346\243\200\345\256\232\n"
"\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("DataTestDlgClass", "\346\265\201\347\250\213\346\217\220\347\244\272", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("DataTestDlgClass", "\346\265\201\347\250\213\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("DataTestDlgClass", "\351\230\200\351\227\250\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        btnWaterIn->setText(QApplication::translate("DataTestDlgClass", "\350\277\233\n"
"\346\260\264\n"
"\351\230\200", 0, QApplication::UnicodeUTF8));
        btnValveBig->setText(QApplication::translate("DataTestDlgClass", "\345\244\247\n"
"\346\265\201\n"
"\351\207\217\n"
"\351\230\200", 0, QApplication::UnicodeUTF8));
        btnValveMiddle1->setText(QApplication::translate("DataTestDlgClass", "\344\270\255\n"
"\346\265\201\n"
"\351\207\217\n"
"\351\230\200\n"
"1", 0, QApplication::UnicodeUTF8));
        btnValveSmall->setText(QApplication::translate("DataTestDlgClass", "\345\260\217\n"
"\346\265\201\n"
"\351\207\217\n"
"\351\230\200", 0, QApplication::UnicodeUTF8));
        btnValveMiddle2->setText(QApplication::translate("DataTestDlgClass", "\344\270\255\n"
"\346\265\201\n"
"\351\207\217\n"
"\351\230\200\n"
"2", 0, QApplication::UnicodeUTF8));
        btnWaterOut->setText(QApplication::translate("DataTestDlgClass", "\346\224\276\n"
"\346\260\264\n"
"\351\230\200", 0, QApplication::UnicodeUTF8));
        btnWaterPump->setText(QApplication::translate("DataTestDlgClass", "\346\260\264\n"
"\346\263\265", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("DataTestDlgClass", "\351\242\221\347\216\207", 0, QApplication::UnicodeUTF8));
        btnRegulate1->setText(QApplication::translate("DataTestDlgClass", "\350\260\203\350\212\202\351\230\2001", 0, QApplication::UnicodeUTF8));
        btnQueryStatus->setText(QApplication::translate("DataTestDlgClass", "\346\237\245\350\257\242\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("DataTestDlgClass", "\346\225\260\346\215\256\351\207\207\351\233\206", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("DataTestDlgClass", "\345\244\247\345\244\251\345\271\263  ", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("DataTestDlgClass", "kg", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("DataTestDlgClass", "\345\260\217\345\244\251\345\271\263  ", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("DataTestDlgClass", "kg", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("DataTestDlgClass", "\347\236\254\346\227\266\346\265\201\351\207\217", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("DataTestDlgClass", "m\302\263/h", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("DataTestDlgClass", "\345\205\245\345\217\243\346\270\251\345\272\246", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("DataTestDlgClass", "\342\204\203", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("DataTestDlgClass", "\345\207\272\345\217\243\346\270\251\345\272\246", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("DataTestDlgClass", "\342\204\203", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("DataTestDlgClass", "\346\223\215\344\275\234\346\255\245\351\252\244", 0, QApplication::UnicodeUTF8));
        btnParaSet->setText(QApplication::translate("DataTestDlgClass", "\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("DataTestDlgClass", "\346\216\222\346\260\224", 0, QApplication::UnicodeUTF8));
        btnStart->setText(QApplication::translate("DataTestDlgClass", "\345\274\200\345\247\213", 0, QApplication::UnicodeUTF8));
        btnExit->setText(QApplication::translate("DataTestDlgClass", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DataTestDlgClass: public Ui_DataTestDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATATESTDLG_H