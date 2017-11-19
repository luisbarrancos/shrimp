/********************************************************************************
** Form generated from reading UI file 'block_input_output.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLOCK_INPUT_OUTPUT_H
#define UI_BLOCK_INPUT_OUTPUT_H

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
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_blockInputOutputDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *okButton;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *nameLineEdit;
    QComboBox *storageTypeComboBox;
    QComboBox *typeComboBox;
    QSpinBox *arraySizeSpinBox;
    QComboBox *arrayTypeComboBox;
    QCheckBox *shaderParameterCheckBox;
    QPlainTextEdit *descriptionTextEdit;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QLineEdit *defaultValueLineEdit;
    QLabel *defaultValueLabel;
    QPushButton *colorButton;
    QPushButton *fileButton;

    void setupUi(QDialog *blockInputOutputDialog)
    {
        if (blockInputOutputDialog->objectName().isEmpty())
            blockInputOutputDialog->setObjectName(QString::fromUtf8("blockInputOutputDialog"));
        blockInputOutputDialog->resize(600, 400);
        blockInputOutputDialog->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(blockInputOutputDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cancelButton = new QPushButton(blockInputOutputDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(cancelButton, 6, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 6, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 6, 1, 1, 1);

        okButton = new QPushButton(blockInputOutputDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(okButton, 6, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 6, 0, 1, 1);

        nameLineEdit = new QLineEdit(blockInputOutputDialog);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));
        nameLineEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(nameLineEdit, 0, 1, 1, 4);

        storageTypeComboBox = new QComboBox(blockInputOutputDialog);
        storageTypeComboBox->setObjectName(QString::fromUtf8("storageTypeComboBox"));
        storageTypeComboBox->setStyleSheet(QString::fromUtf8("QComboBox\n"
"{\n"
"    color:white;\n"
"    background-color: rgba(40,40,40,100);\n"
"    padding: 1px 0px 1px 3px; /*This makes text colour work*/\n"
"}"));
        storageTypeComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        storageTypeComboBox->setMinimumContentsLength(6);

        gridLayout->addWidget(storageTypeComboBox, 2, 1, 1, 1);

        typeComboBox = new QComboBox(blockInputOutputDialog);
        typeComboBox->setObjectName(QString::fromUtf8("typeComboBox"));
        typeComboBox->setStyleSheet(QString::fromUtf8("QComboBox\n"
"{\n"
"    color:white;\n"
"    background-color: rgba(40,40,40,100);\n"
"    padding: 1px 0px 1px 3px; /*This makes text colour work*/\n"
"}"));
        typeComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        typeComboBox->setMinimumContentsLength(10);

        gridLayout->addWidget(typeComboBox, 2, 2, 1, 1);

        arraySizeSpinBox = new QSpinBox(blockInputOutputDialog);
        arraySizeSpinBox->setObjectName(QString::fromUtf8("arraySizeSpinBox"));

        gridLayout->addWidget(arraySizeSpinBox, 2, 3, 1, 1);

        arrayTypeComboBox = new QComboBox(blockInputOutputDialog);
        arrayTypeComboBox->setObjectName(QString::fromUtf8("arrayTypeComboBox"));
        arrayTypeComboBox->setStyleSheet(QString::fromUtf8("QComboBox\n"
"{\n"
"    color:white;\n"
"    background-color: rgba(40,40,40,100);\n"
"    padding: 1px 0px 1px 3px; /*This makes text colour work*/\n"
"}"));

        gridLayout->addWidget(arrayTypeComboBox, 2, 4, 1, 1);

        shaderParameterCheckBox = new QCheckBox(blockInputOutputDialog);
        shaderParameterCheckBox->setObjectName(QString::fromUtf8("shaderParameterCheckBox"));
        shaderParameterCheckBox->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(shaderParameterCheckBox, 4, 1, 1, 2);

        descriptionTextEdit = new QPlainTextEdit(blockInputOutputDialog);
        descriptionTextEdit->setObjectName(QString::fromUtf8("descriptionTextEdit"));
        descriptionTextEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(descriptionTextEdit, 5, 1, 1, 4);

        label = new QLabel(blockInputOutputDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(blockInputOutputDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_4 = new QLabel(blockInputOutputDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label_4, 5, 0, 1, 1);

        defaultValueLineEdit = new QLineEdit(blockInputOutputDialog);
        defaultValueLineEdit->setObjectName(QString::fromUtf8("defaultValueLineEdit"));
        defaultValueLineEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(defaultValueLineEdit, 1, 1, 1, 1);

        defaultValueLabel = new QLabel(blockInputOutputDialog);
        defaultValueLabel->setObjectName(QString::fromUtf8("defaultValueLabel"));
        defaultValueLabel->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(defaultValueLabel, 1, 0, 1, 1);

        colorButton = new QPushButton(blockInputOutputDialog);
        colorButton->setObjectName(QString::fromUtf8("colorButton"));
        colorButton->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(colorButton, 1, 3, 1, 1);

        fileButton = new QPushButton(blockInputOutputDialog);
        fileButton->setObjectName(QString::fromUtf8("fileButton"));
        fileButton->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(fileButton, 1, 4, 1, 1);

        QWidget::setTabOrder(nameLineEdit, storageTypeComboBox);
        QWidget::setTabOrder(storageTypeComboBox, typeComboBox);
        QWidget::setTabOrder(typeComboBox, arraySizeSpinBox);
        QWidget::setTabOrder(arraySizeSpinBox, arrayTypeComboBox);
        QWidget::setTabOrder(arrayTypeComboBox, shaderParameterCheckBox);
        QWidget::setTabOrder(shaderParameterCheckBox, descriptionTextEdit);
        QWidget::setTabOrder(descriptionTextEdit, okButton);
        QWidget::setTabOrder(okButton, cancelButton);

        retranslateUi(blockInputOutputDialog);

        QMetaObject::connectSlotsByName(blockInputOutputDialog);
    } // setupUi

    void retranslateUi(QDialog *blockInputOutputDialog)
    {
        blockInputOutputDialog->setWindowTitle(QApplication::translate("blockInputOutputDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("blockInputOutputDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("blockInputOutputDialog", "Add", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        nameLineEdit->setToolTip(QApplication::translate("blockInputOutputDialog", "Input name", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        storageTypeComboBox->setToolTip(QApplication::translate("blockInputOutputDialog", "Input variable storage type", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        typeComboBox->setToolTip(QApplication::translate("blockInputOutputDialog", "Input type", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        arraySizeSpinBox->setToolTip(QApplication::translate("blockInputOutputDialog", "Array size", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        arrayTypeComboBox->setToolTip(QApplication::translate("blockInputOutputDialog", "Array type", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        shaderParameterCheckBox->setToolTip(QApplication::translate("blockInputOutputDialog", "Makes the input a shader parameter", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        shaderParameterCheckBox->setText(QApplication::translate("blockInputOutputDialog", "Shader parameter", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        descriptionTextEdit->setToolTip(QApplication::translate("blockInputOutputDialog", "Input description", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("blockInputOutputDialog", "Name", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("blockInputOutputDialog", "Type", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("blockInputOutputDialog", "Description", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        defaultValueLineEdit->setToolTip(QApplication::translate("blockInputOutputDialog", "Input default value", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        defaultValueLabel->setText(QApplication::translate("blockInputOutputDialog", "Default value", 0, QApplication::UnicodeUTF8));
        colorButton->setText(QApplication::translate("blockInputOutputDialog", "Color", 0, QApplication::UnicodeUTF8));
        fileButton->setText(QApplication::translate("blockInputOutputDialog", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class blockInputOutputDialog: public Ui_blockInputOutputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLOCK_INPUT_OUTPUT_H
