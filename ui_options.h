/********************************************************************************
** Form generated from reading UI file 'options.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONS_H
#define UI_OPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_optionsDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *cancelButton;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QComboBox *rendererComboBox;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *okButton;
    QLineEdit *renderWidthLineEdit;
    QLineEdit *shadingRateLineEdit;
    QLineEdit *pixelSamplesXLineEdit;
    QLineEdit *pixelSamplesYLineEdit;
    QComboBox *pixelFilterComboBox;
    QLineEdit *filterWidthSLineEdit;
    QLineEdit *filterWidthTLineEdit;
    QLineEdit *helpReaderLineEdit;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *renderHeightLineEdit;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit;
    QLabel *label_17;
    QLabel *label_2;
    QLabel *label_5;
    QComboBox *displayComboBox;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_7;
    QComboBox *sceneComboBox;
    QLineEdit *rendererCodeLineEdit;
    QLineEdit *shaderCompilationLineEdit;
    QLineEdit *shaderExtensionLineEdit;
    QLineEdit *renderingCommandLineEdit;
    QSpacerItem *verticalSpacer_4;
    QCheckBox *splashScreenCheckBox;

    void setupUi(QDialog *optionsDialog)
    {
        if (optionsDialog->objectName().isEmpty())
            optionsDialog->setObjectName(QString::fromUtf8("optionsDialog"));
        optionsDialog->resize(565, 531);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(optionsDialog->sizePolicy().hasHeightForWidth());
        optionsDialog->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(50, 50, 50, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush2(QColor(20, 55, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush2);
        QBrush brush3(QColor(106, 104, 100, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        QBrush brush4(QColor(190, 190, 190, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QBrush brush5(QColor(145, 141, 126, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush5);
        optionsDialog->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("Liberation Sans"));
        font.setPointSize(10);
        optionsDialog->setFont(font);
        optionsDialog->setStyleSheet(QString::fromUtf8(""));
        optionsDialog->setModal(false);
        gridLayout = new QGridLayout(optionsDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(12, 10, 32, 12);
        cancelButton = new QPushButton(optionsDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setFont(font);
        cancelButton->setAutoFillBackground(false);
        cancelButton->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(cancelButton, 23, 7, 1, 1);

        label = new QLabel(optionsDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8(""));
        label->setFrameShape(QFrame::StyledPanel);

        gridLayout->addWidget(label, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 23, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 23, 6, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 23, 2, 1, 1);

        rendererComboBox = new QComboBox(optionsDialog);
        rendererComboBox->setObjectName(QString::fromUtf8("rendererComboBox"));
        rendererComboBox->setFont(font);
        rendererComboBox->setStyleSheet(QString::fromUtf8("QComboBox\n"
"{\n"
"    color:white;\n"
"    background-color: rgba(40,40,40,100);\n"
"    padding: 1px 0px 1px 3px; /*This makes text colour work*/\n"
"}"));

        gridLayout->addWidget(rendererComboBox, 1, 2, 1, 2);

        label_3 = new QLabel(optionsDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8(""));
        label_3->setFrameShape(QFrame::StyledPanel);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 8, 3, 1, 1);

        label_4 = new QLabel(optionsDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8(""));
        label_4->setFrameShape(QFrame::StyledPanel);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 10, 3, 1, 1);

        label_6 = new QLabel(optionsDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);
        label_6->setStyleSheet(QString::fromUtf8(""));
        label_6->setFrameShape(QFrame::StyledPanel);
        label_6->setFrameShadow(QFrame::Plain);
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_6, 6, 3, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 23, 4, 1, 1);

        okButton = new QPushButton(optionsDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setFont(font);
        okButton->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(okButton, 23, 5, 1, 1);

        renderWidthLineEdit = new QLineEdit(optionsDialog);
        renderWidthLineEdit->setObjectName(QString::fromUtf8("renderWidthLineEdit"));
        renderWidthLineEdit->setFont(font);
        renderWidthLineEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(renderWidthLineEdit, 15, 3, 1, 1);

        shadingRateLineEdit = new QLineEdit(optionsDialog);
        shadingRateLineEdit->setObjectName(QString::fromUtf8("shadingRateLineEdit"));
        shadingRateLineEdit->setFont(font);
        shadingRateLineEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(shadingRateLineEdit, 16, 3, 1, 1);

        pixelSamplesXLineEdit = new QLineEdit(optionsDialog);
        pixelSamplesXLineEdit->setObjectName(QString::fromUtf8("pixelSamplesXLineEdit"));
        pixelSamplesXLineEdit->setFont(font);
        pixelSamplesXLineEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(pixelSamplesXLineEdit, 17, 3, 1, 1);

        pixelSamplesYLineEdit = new QLineEdit(optionsDialog);
        pixelSamplesYLineEdit->setObjectName(QString::fromUtf8("pixelSamplesYLineEdit"));
        pixelSamplesYLineEdit->setFont(font);
        pixelSamplesYLineEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(pixelSamplesYLineEdit, 17, 6, 1, 2);

        pixelFilterComboBox = new QComboBox(optionsDialog);
        pixelFilterComboBox->setObjectName(QString::fromUtf8("pixelFilterComboBox"));
        pixelFilterComboBox->setFont(font);
        pixelFilterComboBox->setStyleSheet(QString::fromUtf8("QComboBox\n"
"{\n"
"    color:white;\n"
"    background-color: rgba(40,40,40,100);\n"
"    padding: 1px 0px 1px 3px; /*This makes text colour work*/\n"
"}"));

        gridLayout->addWidget(pixelFilterComboBox, 18, 3, 1, 1);

        filterWidthSLineEdit = new QLineEdit(optionsDialog);
        filterWidthSLineEdit->setObjectName(QString::fromUtf8("filterWidthSLineEdit"));
        filterWidthSLineEdit->setFont(font);
        filterWidthSLineEdit->setStyleSheet(QString::fromUtf8(";"));

        gridLayout->addWidget(filterWidthSLineEdit, 19, 3, 1, 1);

        filterWidthTLineEdit = new QLineEdit(optionsDialog);
        filterWidthTLineEdit->setObjectName(QString::fromUtf8("filterWidthTLineEdit"));
        filterWidthTLineEdit->setFont(font);
        filterWidthTLineEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(filterWidthTLineEdit, 19, 6, 1, 2);

        helpReaderLineEdit = new QLineEdit(optionsDialog);
        helpReaderLineEdit->setObjectName(QString::fromUtf8("helpReaderLineEdit"));
        helpReaderLineEdit->setFont(font);
        helpReaderLineEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(helpReaderLineEdit, 21, 5, 1, 3);

        label_8 = new QLabel(optionsDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);
        label_8->setStyleSheet(QString::fromUtf8(""));
        label_8->setFrameShape(QFrame::StyledPanel);
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_8, 15, 1, 1, 2);

        label_9 = new QLabel(optionsDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font);
        label_9->setStyleSheet(QString::fromUtf8(""));
        label_9->setFrameShape(QFrame::StyledPanel);
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_9, 16, 1, 1, 2);

        label_10 = new QLabel(optionsDialog);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font);
        label_10->setStyleSheet(QString::fromUtf8(""));
        label_10->setFrameShape(QFrame::StyledPanel);
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_10, 15, 5, 1, 1);

        label_11 = new QLabel(optionsDialog);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font);
        label_11->setStyleSheet(QString::fromUtf8(""));
        label_11->setFrameShape(QFrame::StyledPanel);
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_11, 17, 5, 1, 1);

        label_12 = new QLabel(optionsDialog);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font);
        label_12->setStyleSheet(QString::fromUtf8(""));
        label_12->setFrameShape(QFrame::StyledPanel);
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_12, 19, 5, 1, 1);

        label_13 = new QLabel(optionsDialog);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font);
        label_13->setStyleSheet(QString::fromUtf8(""));
        label_13->setFrameShape(QFrame::StyledPanel);
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_13, 17, 1, 1, 2);

        label_14 = new QLabel(optionsDialog);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font);
        label_14->setStyleSheet(QString::fromUtf8(""));
        label_14->setFrameShape(QFrame::StyledPanel);
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_14, 18, 1, 1, 2);

        label_15 = new QLabel(optionsDialog);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font);
        label_15->setStyleSheet(QString::fromUtf8(""));
        label_15->setFrameShape(QFrame::StyledPanel);
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_15, 19, 1, 1, 2);

        label_16 = new QLabel(optionsDialog);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font);
        label_16->setStyleSheet(QString::fromUtf8(""));
        label_16->setFrameShape(QFrame::StyledPanel);
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_16, 21, 3, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 13, 3, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 20, 3, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 22, 4, 1, 1);

        renderHeightLineEdit = new QLineEdit(optionsDialog);
        renderHeightLineEdit->setObjectName(QString::fromUtf8("renderHeightLineEdit"));
        renderHeightLineEdit->setFont(font);
        renderHeightLineEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(renderHeightLineEdit, 15, 6, 1, 2);

        horizontalSpacer = new QSpacerItem(30, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 5);

        lineEdit = new QLineEdit(optionsDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 16, 6, 1, 2);

        label_17 = new QLabel(optionsDialog);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font);
        label_17->setStyleSheet(QString::fromUtf8(";"));
        label_17->setFrameShape(QFrame::StyledPanel);
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_17, 16, 5, 1, 1);

        label_2 = new QLabel(optionsDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setStyleSheet(QString::fromUtf8(""));
        label_2->setFrameShape(QFrame::StyledPanel);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 12, 3, 1, 1);

        label_5 = new QLabel(optionsDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8(""));
        label_5->setFrameShape(QFrame::StyledPanel);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 3, 1, 1, 1);

        displayComboBox = new QComboBox(optionsDialog);
        displayComboBox->setObjectName(QString::fromUtf8("displayComboBox"));
        displayComboBox->setFont(font);
        displayComboBox->setAutoFillBackground(false);
        displayComboBox->setStyleSheet(QString::fromUtf8("QComboBox\n"
"{\n"
"    color:white;\n"
"    background-color: rgba(40,40,40,100);\n"
"    padding: 1px 0px 1px 3px; /*This makes text colour work*/\n"
"}"));

        gridLayout->addWidget(displayComboBox, 3, 2, 1, 2);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 6, 1, 1, 2);

        label_7 = new QLabel(optionsDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);
        label_7->setStyleSheet(QString::fromUtf8(""));
        label_7->setFrameShape(QFrame::StyledPanel);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 4, 1, 1, 1);

        sceneComboBox = new QComboBox(optionsDialog);
        sceneComboBox->setObjectName(QString::fromUtf8("sceneComboBox"));
        sceneComboBox->setFont(font);
        sceneComboBox->setStyleSheet(QString::fromUtf8("QComboBox\n"
"{\n"
"    color:white;\n"
"    background-color: rgba(40,40,40,100);\n"
"    padding: 1px 0px 1px 3px; /*This makes text colour work*/\n"
"}"));

        gridLayout->addWidget(sceneComboBox, 4, 2, 1, 2);

        rendererCodeLineEdit = new QLineEdit(optionsDialog);
        rendererCodeLineEdit->setObjectName(QString::fromUtf8("rendererCodeLineEdit"));
        rendererCodeLineEdit->setFont(font);
        rendererCodeLineEdit->setCursor(QCursor(Qt::BlankCursor));
        rendererCodeLineEdit->setMouseTracking(false);
        rendererCodeLineEdit->setFocusPolicy(Qt::NoFocus);
        rendererCodeLineEdit->setAcceptDrops(false);
        rendererCodeLineEdit->setStyleSheet(QString::fromUtf8(""));
        rendererCodeLineEdit->setReadOnly(true);

        gridLayout->addWidget(rendererCodeLineEdit, 12, 5, 1, 2);

        shaderCompilationLineEdit = new QLineEdit(optionsDialog);
        shaderCompilationLineEdit->setObjectName(QString::fromUtf8("shaderCompilationLineEdit"));
        shaderCompilationLineEdit->setFont(font);
        shaderCompilationLineEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(shaderCompilationLineEdit, 6, 5, 1, 3);

        shaderExtensionLineEdit = new QLineEdit(optionsDialog);
        shaderExtensionLineEdit->setObjectName(QString::fromUtf8("shaderExtensionLineEdit"));
        shaderExtensionLineEdit->setFont(font);
        shaderExtensionLineEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(shaderExtensionLineEdit, 8, 5, 1, 2);

        renderingCommandLineEdit = new QLineEdit(optionsDialog);
        renderingCommandLineEdit->setObjectName(QString::fromUtf8("renderingCommandLineEdit"));
        renderingCommandLineEdit->setFont(font);
        renderingCommandLineEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(renderingCommandLineEdit, 10, 5, 1, 3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 5, 3, 1, 1);

        splashScreenCheckBox = new QCheckBox(optionsDialog);
        splashScreenCheckBox->setObjectName(QString::fromUtf8("splashScreenCheckBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(splashScreenCheckBox->sizePolicy().hasHeightForWidth());
        splashScreenCheckBox->setSizePolicy(sizePolicy1);
        splashScreenCheckBox->setMinimumSize(QSize(72, 0));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Liberation Sans Narrow"));
        font1.setPointSize(10);
        splashScreenCheckBox->setFont(font1);
        splashScreenCheckBox->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(splashScreenCheckBox, 0, 6, 1, 2);


        retranslateUi(optionsDialog);

        QMetaObject::connectSlotsByName(optionsDialog);
    } // setupUi

    void retranslateUi(QDialog *optionsDialog)
    {
        optionsDialog->setWindowTitle(QApplication::translate("optionsDialog", "Options", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("optionsDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("optionsDialog", "Renderer", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_3->setToolTip(QApplication::translate("optionsDialog", "Compiled shader extension", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("optionsDialog", "shader extension", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_4->setToolTip(QApplication::translate("optionsDialog", "Rendering command and options", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("optionsDialog", "rendering command", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_6->setToolTip(QApplication::translate("optionsDialog", "Shader compiler command, flags and definitions", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_6->setText(QApplication::translate("optionsDialog", "shader compilation", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("optionsDialog", "OK", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_8->setToolTip(QApplication::translate("optionsDialog", "Render width in pixels", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_8->setText(QApplication::translate("optionsDialog", "Render width", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_9->setToolTip(QApplication::translate("optionsDialog", "Shading rate", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_9->setText(QApplication::translate("optionsDialog", "Shading rate", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_10->setToolTip(QApplication::translate("optionsDialog", "Render height in pixels", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_10->setText(QApplication::translate("optionsDialog", "Render height", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_11->setToolTip(QApplication::translate("optionsDialog", "Pixel samples along Y", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_11->setText(QApplication::translate("optionsDialog", "Pixels samples y", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_12->setToolTip(QApplication::translate("optionsDialog", "Pixel filter along Y", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_12->setText(QApplication::translate("optionsDialog", "Filter width t", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_13->setToolTip(QApplication::translate("optionsDialog", "Pixel samples along X", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_13->setText(QApplication::translate("optionsDialog", "Pixel samples x", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_14->setToolTip(QApplication::translate("optionsDialog", "Pixel filter", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_14->setText(QApplication::translate("optionsDialog", "Pixel filter", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_15->setToolTip(QApplication::translate("optionsDialog", "Pixel filter along X", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_15->setText(QApplication::translate("optionsDialog", "Filter width s", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_16->setToolTip(QApplication::translate("optionsDialog", "Browser command for HTML reference", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_16->setText(QApplication::translate("optionsDialog", "Help reader command", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_17->setToolTip(QApplication::translate("optionsDialog", "Hider", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_17->setText(QApplication::translate("optionsDialog", "Hider", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_2->setToolTip(QApplication::translate("optionsDialog", "Renderer definition", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("optionsDialog", "renderer code", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("optionsDialog", "display", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("optionsDialog", "Scene", 0, QApplication::UnicodeUTF8));
        splashScreenCheckBox->setText(QApplication::translate("optionsDialog", "Splash Screen", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class optionsDialog: public Ui_optionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONS_H
