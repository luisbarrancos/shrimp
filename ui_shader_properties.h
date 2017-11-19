/********************************************************************************
** Form generated from reading UI file 'shader_properties.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHADER_PROPERTIES_H
#define UI_SHADER_PROPERTIES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_shaderPropertiesDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *okButton;
    QLineEdit *nameLineEdit;
    QTextEdit *descriptionTextEdit;
    QLineEdit *authorsLineEdit;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *shaderPropertiesDialog)
    {
        if (shaderPropertiesDialog->objectName().isEmpty())
            shaderPropertiesDialog->setObjectName(QString::fromUtf8("shaderPropertiesDialog"));
        shaderPropertiesDialog->resize(600, 400);
        shaderPropertiesDialog->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(shaderPropertiesDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        okButton = new QPushButton(shaderPropertiesDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(okButton, 3, 2, 1, 1);

        nameLineEdit = new QLineEdit(shaderPropertiesDialog);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));
        nameLineEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(nameLineEdit, 0, 1, 1, 4);

        descriptionTextEdit = new QTextEdit(shaderPropertiesDialog);
        descriptionTextEdit->setObjectName(QString::fromUtf8("descriptionTextEdit"));
        descriptionTextEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(descriptionTextEdit, 1, 1, 1, 4);

        authorsLineEdit = new QLineEdit(shaderPropertiesDialog);
        authorsLineEdit->setObjectName(QString::fromUtf8("authorsLineEdit"));
        authorsLineEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(authorsLineEdit, 2, 1, 1, 4);

        label = new QLabel(shaderPropertiesDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(shaderPropertiesDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(shaderPropertiesDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        cancelButton = new QPushButton(shaderPropertiesDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(cancelButton, 3, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 3, 3, 1, 1);

        gridLayout->setColumnStretch(1, 5);
        gridLayout->setColumnStretch(3, 1);

        retranslateUi(shaderPropertiesDialog);

        QMetaObject::connectSlotsByName(shaderPropertiesDialog);
    } // setupUi

    void retranslateUi(QDialog *shaderPropertiesDialog)
    {
        shaderPropertiesDialog->setWindowTitle(QApplication::translate("shaderPropertiesDialog", "Shader Properties", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("shaderPropertiesDialog", "OK", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("shaderPropertiesDialog", "Name", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("shaderPropertiesDialog", "Description", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("shaderPropertiesDialog", "Authors", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("shaderPropertiesDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class shaderPropertiesDialog: public Ui_shaderPropertiesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHADER_PROPERTIES_H
