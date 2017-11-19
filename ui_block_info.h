/********************************************************************************
** Form generated from reading UI file 'block_info.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLOCK_INFO_H
#define UI_BLOCK_INFO_H

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

class Ui_blockInfoDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *cancelButton;
    QPushButton *okButton;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *nameLineEdit;
    QTextEdit *descriptionTextEdit;
    QTextEdit *usageTextEdit;
    QLineEdit *authorsLineEdit;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *blockInfoDialog)
    {
        if (blockInfoDialog->objectName().isEmpty())
            blockInfoDialog->setObjectName(QString::fromUtf8("blockInfoDialog"));
        blockInfoDialog->resize(475, 401);
        blockInfoDialog->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(blockInfoDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cancelButton = new QPushButton(blockInfoDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(cancelButton, 4, 4, 1, 1);

        okButton = new QPushButton(blockInfoDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setStyleSheet(QString::fromUtf8(""));
        okButton->setDefault(true);

        gridLayout->addWidget(okButton, 4, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 4, 0, 1, 1);

        nameLineEdit = new QLineEdit(blockInfoDialog);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));
        nameLineEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(nameLineEdit, 0, 1, 1, 4);

        descriptionTextEdit = new QTextEdit(blockInfoDialog);
        descriptionTextEdit->setObjectName(QString::fromUtf8("descriptionTextEdit"));
        descriptionTextEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(descriptionTextEdit, 1, 1, 1, 4);

        usageTextEdit = new QTextEdit(blockInfoDialog);
        usageTextEdit->setObjectName(QString::fromUtf8("usageTextEdit"));
        usageTextEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(usageTextEdit, 2, 1, 1, 4);

        authorsLineEdit = new QLineEdit(blockInfoDialog);
        authorsLineEdit->setObjectName(QString::fromUtf8("authorsLineEdit"));
        authorsLineEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(authorsLineEdit, 3, 1, 1, 4);

        label = new QLabel(blockInfoDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(blockInfoDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(blockInfoDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_4 = new QLabel(blockInfoDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 4, 1, 1, 1);

        QWidget::setTabOrder(nameLineEdit, descriptionTextEdit);
        QWidget::setTabOrder(descriptionTextEdit, usageTextEdit);
        QWidget::setTabOrder(usageTextEdit, authorsLineEdit);
        QWidget::setTabOrder(authorsLineEdit, okButton);
        QWidget::setTabOrder(okButton, cancelButton);

        retranslateUi(blockInfoDialog);

        QMetaObject::connectSlotsByName(blockInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *blockInfoDialog)
    {
        blockInfoDialog->setWindowTitle(QApplication::translate("blockInfoDialog", "Block Info", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("blockInfoDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("blockInfoDialog", "OK", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("blockInfoDialog", "Name", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("blockInfoDialog", "Description", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("blockInfoDialog", "Usage", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("blockInfoDialog", "Authors", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class blockInfoDialog: public Ui_blockInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLOCK_INFO_H
