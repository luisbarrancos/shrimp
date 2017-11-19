/********************************************************************************
** Form generated from reading UI file 'block_name.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLOCK_NAME_H
#define UI_BLOCK_NAME_H

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

QT_BEGIN_NAMESPACE

class Ui_blockNameDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *cancelButton;
    QPushButton *okButton;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *blockNameLineEdit;
    QLabel *label;

    void setupUi(QDialog *blockNameDialog)
    {
        if (blockNameDialog->objectName().isEmpty())
            blockNameDialog->setObjectName(QString::fromUtf8("blockNameDialog"));
        blockNameDialog->resize(400, 106);
        blockNameDialog->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(blockNameDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cancelButton = new QPushButton(blockNameDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setStyleSheet(QString::fromUtf8(""));
        cancelButton->setAutoDefault(true);

        gridLayout->addWidget(cancelButton, 1, 4, 1, 1);

        okButton = new QPushButton(blockNameDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setStyleSheet(QString::fromUtf8(""));
        okButton->setDefault(true);

        gridLayout->addWidget(okButton, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 1, 1, 1);

        blockNameLineEdit = new QLineEdit(blockNameDialog);
        blockNameLineEdit->setObjectName(QString::fromUtf8("blockNameLineEdit"));
        blockNameLineEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(blockNameLineEdit, 0, 1, 1, 4);

        label = new QLabel(blockNameDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        QWidget::setTabOrder(blockNameLineEdit, okButton);
        QWidget::setTabOrder(okButton, cancelButton);

        retranslateUi(blockNameDialog);

        QMetaObject::connectSlotsByName(blockNameDialog);
    } // setupUi

    void retranslateUi(QDialog *blockNameDialog)
    {
        blockNameDialog->setWindowTitle(QApplication::translate("blockNameDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("blockNameDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("blockNameDialog", "OK", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("blockNameDialog", "Name", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class blockNameDialog: public Ui_blockNameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLOCK_NAME_H
