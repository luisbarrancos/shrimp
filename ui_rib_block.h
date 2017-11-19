/********************************************************************************
** Form generated from reading UI file 'rib_block.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RIB_BLOCK_H
#define UI_RIB_BLOCK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_ribBlockDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *aovCheckBox;
    QLineEdit *imagerLineEdit;
    QPlainTextEdit *declarationsTextEdit;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *ribBlockDialog)
    {
        if (ribBlockDialog->objectName().isEmpty())
            ribBlockDialog->setObjectName(QString::fromUtf8("ribBlockDialog"));
        ribBlockDialog->resize(600, 400);
        ribBlockDialog->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(ribBlockDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cancelButton = new QPushButton(ribBlockDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(cancelButton, 3, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 3, 1, 1);

        okButton = new QPushButton(ribBlockDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(okButton, 3, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 3, 0, 1, 1);

        aovCheckBox = new QCheckBox(ribBlockDialog);
        aovCheckBox->setObjectName(QString::fromUtf8("aovCheckBox"));
        aovCheckBox->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(aovCheckBox, 2, 1, 1, 3);

        imagerLineEdit = new QLineEdit(ribBlockDialog);
        imagerLineEdit->setObjectName(QString::fromUtf8("imagerLineEdit"));
        imagerLineEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(imagerLineEdit, 1, 1, 1, 4);

        declarationsTextEdit = new QPlainTextEdit(ribBlockDialog);
        declarationsTextEdit->setObjectName(QString::fromUtf8("declarationsTextEdit"));
        declarationsTextEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(declarationsTextEdit, 0, 1, 1, 4);

        label = new QLabel(ribBlockDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(ribBlockDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);


        retranslateUi(ribBlockDialog);

        QMetaObject::connectSlotsByName(ribBlockDialog);
    } // setupUi

    void retranslateUi(QDialog *ribBlockDialog)
    {
        ribBlockDialog->setWindowTitle(QApplication::translate("ribBlockDialog", "Edit RIB", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("ribBlockDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("ribBlockDialog", "OK", 0, QApplication::UnicodeUTF8));
        aovCheckBox->setText(QApplication::translate("ribBlockDialog", "AOV", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ribBlockDialog", "Declarations", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ribBlockDialog", "Imager", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ribBlockDialog: public Ui_ribBlockDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RIB_BLOCK_H
