/********************************************************************************
** Form generated from reading UI file 'code_preview.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CODE_PREVIEW_H
#define UI_CODE_PREVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_codePreviewDialog
{
public:
    QGridLayout *gridLayout_2;
    QPushButton *okButton;
    QTextEdit *surfaceTextEdit;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *codePreviewDialog)
    {
        if (codePreviewDialog->objectName().isEmpty())
            codePreviewDialog->setObjectName(QString::fromUtf8("codePreviewDialog"));
        codePreviewDialog->resize(600, 400);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(codePreviewDialog->sizePolicy().hasHeightForWidth());
        codePreviewDialog->setSizePolicy(sizePolicy);
        codePreviewDialog->setStyleSheet(QString::fromUtf8(""));
        gridLayout_2 = new QGridLayout(codePreviewDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        okButton = new QPushButton(codePreviewDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(okButton, 1, 2, 1, 1);

        surfaceTextEdit = new QTextEdit(codePreviewDialog);
        surfaceTextEdit->setObjectName(QString::fromUtf8("surfaceTextEdit"));
        surfaceTextEdit->setStyleSheet(QString::fromUtf8(""));
        surfaceTextEdit->setAcceptRichText(false);
        surfaceTextEdit->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_2->addWidget(surfaceTextEdit, 0, 1, 1, 2);

        label = new QLabel(codePreviewDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        gridLayout_2->setColumnStretch(1, 1);

        retranslateUi(codePreviewDialog);

        QMetaObject::connectSlotsByName(codePreviewDialog);
    } // setupUi

    void retranslateUi(QDialog *codePreviewDialog)
    {
        codePreviewDialog->setWindowTitle(QApplication::translate("codePreviewDialog", "Code Preview", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("codePreviewDialog", "OK", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("codePreviewDialog", "Surface", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class codePreviewDialog: public Ui_codePreviewDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CODE_PREVIEW_H
