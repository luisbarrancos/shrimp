/********************************************************************************
** Form generated from reading UI file 'block_code.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLOCK_CODE_H
#define UI_BLOCK_CODE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_blockCodeDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QPlainTextEdit *ioTextEdit;
    QPlainTextEdit *codeTextEdit;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *blockCodeDialog)
    {
        if (blockCodeDialog->objectName().isEmpty())
            blockCodeDialog->setObjectName(QString::fromUtf8("blockCodeDialog"));
        blockCodeDialog->resize(600, 400);
        blockCodeDialog->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(blockCodeDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cancelButton = new QPushButton(blockCodeDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(cancelButton, 2, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 3, 1, 1);

        okButton = new QPushButton(blockCodeDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setStyleSheet(QString::fromUtf8(""));
        okButton->setDefault(true);

        gridLayout->addWidget(okButton, 2, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 0, 1, 1);

        ioTextEdit = new QPlainTextEdit(blockCodeDialog);
        ioTextEdit->setObjectName(QString::fromUtf8("ioTextEdit"));
        ioTextEdit->setFocusPolicy(Qt::NoFocus);
        ioTextEdit->setStyleSheet(QString::fromUtf8("color: white;"));
        ioTextEdit->setReadOnly(true);

        gridLayout->addWidget(ioTextEdit, 0, 1, 1, 4);

        codeTextEdit = new QPlainTextEdit(blockCodeDialog);
        codeTextEdit->setObjectName(QString::fromUtf8("codeTextEdit"));
        codeTextEdit->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(codeTextEdit, 1, 1, 1, 4);

        label = new QLabel(blockCodeDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(blockCodeDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 4);
        gridLayout->setColumnStretch(1, 3);
        gridLayout->setColumnStretch(2, 1);
        gridLayout->setColumnStretch(4, 1);
        QWidget::setTabOrder(codeTextEdit, okButton);
        QWidget::setTabOrder(okButton, cancelButton);

        retranslateUi(blockCodeDialog);

        QMetaObject::connectSlotsByName(blockCodeDialog);
    } // setupUi

    void retranslateUi(QDialog *blockCodeDialog)
    {
        blockCodeDialog->setWindowTitle(QApplication::translate("blockCodeDialog", "Block Code", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("blockCodeDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("blockCodeDialog", "OK", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("blockCodeDialog", "I/O", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("blockCodeDialog", "Code", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class blockCodeDialog: public Ui_blockCodeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLOCK_CODE_H
