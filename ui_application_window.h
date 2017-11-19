/********************************************************************************
** Form generated from reading UI file 'application_window.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPLICATION_WINDOW_H
#define UI_APPLICATION_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_application_window
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionShaderProperties;
    QAction *actionCodePreview;
    QAction *actionExportScene;
    QAction *actionOptions;
    QAction *actionQuit;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionCut;
    QAction *actionGroup;
    QAction *actionUngroup;
    QAction *actionEditBlock;
    QAction *actionDeleteBlocks;
    QAction *actionShowGrid;
    QAction *actionSnapBlocks;
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionCredits;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QPushButton *addBlockButton;
    QLabel *label;
    QComboBox *displayCombo;
    QLabel *label_3;
    QPushButton *renderButton;
    QLabel *label_4;
    QSlider *zoomSlider;
    QPushButton *fitSceneButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *sceneCombo;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QComboBox *rendererCombo;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuAbout;

    void setupUi(QMainWindow *application_window)
    {
        if (application_window->objectName().isEmpty())
            application_window->setObjectName(QString::fromUtf8("application_window"));
        application_window->resize(935, 602);
        QPalette palette;
        QBrush brush(QColor(50, 50, 50, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        application_window->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("Liberation Sans"));
        font.setPointSize(10);
        application_window->setFont(font);
        application_window->setAutoFillBackground(false);
        application_window->setStyleSheet(QString::fromUtf8(""));
        application_window->setDocumentMode(false);
        actionNew = new QAction(application_window);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionNew->setFont(font);
        actionOpen = new QAction(application_window);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionOpen->setFont(font);
        actionSave = new QAction(application_window);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setFont(font);
        actionSaveAs = new QAction(application_window);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        actionSaveAs->setFont(font);
        actionShaderProperties = new QAction(application_window);
        actionShaderProperties->setObjectName(QString::fromUtf8("actionShaderProperties"));
        actionShaderProperties->setFont(font);
        actionCodePreview = new QAction(application_window);
        actionCodePreview->setObjectName(QString::fromUtf8("actionCodePreview"));
        actionCodePreview->setFont(font);
        actionExportScene = new QAction(application_window);
        actionExportScene->setObjectName(QString::fromUtf8("actionExportScene"));
        actionExportScene->setFont(font);
        actionOptions = new QAction(application_window);
        actionOptions->setObjectName(QString::fromUtf8("actionOptions"));
        actionOptions->setFont(font);
        actionQuit = new QAction(application_window);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionQuit->setFont(font);
        actionCopy = new QAction(application_window);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionCopy->setFont(font);
        actionPaste = new QAction(application_window);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        actionPaste->setFont(font);
        actionCut = new QAction(application_window);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        actionCut->setFont(font);
        actionGroup = new QAction(application_window);
        actionGroup->setObjectName(QString::fromUtf8("actionGroup"));
        actionGroup->setFont(font);
        actionUngroup = new QAction(application_window);
        actionUngroup->setObjectName(QString::fromUtf8("actionUngroup"));
        actionUngroup->setFont(font);
        actionEditBlock = new QAction(application_window);
        actionEditBlock->setObjectName(QString::fromUtf8("actionEditBlock"));
        actionEditBlock->setFont(font);
        actionDeleteBlocks = new QAction(application_window);
        actionDeleteBlocks->setObjectName(QString::fromUtf8("actionDeleteBlocks"));
        actionDeleteBlocks->setFont(font);
        actionShowGrid = new QAction(application_window);
        actionShowGrid->setObjectName(QString::fromUtf8("actionShowGrid"));
        actionShowGrid->setCheckable(true);
        actionShowGrid->setFont(font);
        actionSnapBlocks = new QAction(application_window);
        actionSnapBlocks->setObjectName(QString::fromUtf8("actionSnapBlocks"));
        actionSnapBlocks->setCheckable(true);
        actionSnapBlocks->setFont(font);
        actionHelp = new QAction(application_window);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionHelp->setFont(font);
        actionAbout = new QAction(application_window);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout->setFont(font);
        actionCredits = new QAction(application_window);
        actionCredits->setObjectName(QString::fromUtf8("actionCredits"));
        actionCredits->setFont(font);
        centralWidget = new QWidget(application_window);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush);
        QBrush brush2(QColor(20, 55, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Highlight, brush2);
        QBrush brush3(QColor(35, 51, 71, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush3);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush);
        QBrush brush4(QColor(0, 0, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush);
        QBrush brush5(QColor(145, 141, 126, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Inactive, QPalette::Highlight, brush5);
        QBrush brush6(QColor(121, 121, 121, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush6);
        QBrush brush7(QColor(30, 30, 30, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush);
        QBrush brush8(QColor(190, 190, 190, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Highlight, brush5);
        QBrush brush9(QColor(40, 40, 40, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush4);
        centralWidget->setPalette(palette1);
        centralWidget->setFont(font);
        centralWidget->setAutoFillBackground(false);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 2, 2);
        addBlockButton = new QPushButton(centralWidget);
        addBlockButton->setObjectName(QString::fromUtf8("addBlockButton"));
        addBlockButton->setEnabled(true);
        addBlockButton->setFont(font);
        addBlockButton->setMouseTracking(false);
        addBlockButton->setAcceptDrops(false);
        addBlockButton->setAutoFillBackground(false);
        addBlockButton->setStyleSheet(QString::fromUtf8(""));
        addBlockButton->setCheckable(true);
        addBlockButton->setDefault(false);
        addBlockButton->setFlat(true);

        gridLayout->addWidget(addBlockButton, 0, 0, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label, 0, 2, 1, 1);

        displayCombo = new QComboBox(centralWidget);
        displayCombo->setObjectName(QString::fromUtf8("displayCombo"));
        displayCombo->setFont(font);
        displayCombo->setAutoFillBackground(false);
        displayCombo->setStyleSheet(QString::fromUtf8("QComboBox\n"
"{\n"
"    color:white;\n"
"    background-color: rgba(40,40,40,100);\n"
"    padding: 1px 0px 1px 3px; /*This makes text colour work*/\n"
"}"));
        displayCombo->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        displayCombo->setMinimumContentsLength(16);
        displayCombo->setFrame(false);
        displayCombo->setModelColumn(0);

        gridLayout->addWidget(displayCombo, 0, 6, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label_3, 0, 8, 1, 1);

        renderButton = new QPushButton(centralWidget);
        renderButton->setObjectName(QString::fromUtf8("renderButton"));
        renderButton->setFont(font);
        renderButton->setAutoFillBackground(false);
        renderButton->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(renderButton, 0, 11, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label_4, 2, 1, 1, 1);

        zoomSlider = new QSlider(centralWidget);
        zoomSlider->setObjectName(QString::fromUtf8("zoomSlider"));
        zoomSlider->setFont(font);
        zoomSlider->setAutoFillBackground(false);
        zoomSlider->setStyleSheet(QString::fromUtf8(""));
        zoomSlider->setMinimum(1);
        zoomSlider->setMaximum(100);
        zoomSlider->setPageStep(10);
        zoomSlider->setValue(50);
        zoomSlider->setSliderPosition(50);
        zoomSlider->setOrientation(Qt::Horizontal);
        zoomSlider->setInvertedControls(false);
        zoomSlider->setTickPosition(QSlider::NoTicks);

        gridLayout->addWidget(zoomSlider, 2, 2, 1, 5);

        fitSceneButton = new QPushButton(centralWidget);
        fitSceneButton->setObjectName(QString::fromUtf8("fitSceneButton"));
        fitSceneButton->setFont(font);
        fitSceneButton->setAutoFillBackground(false);
        fitSceneButton->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(fitSceneButton, 2, 8, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 7, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 10, 1, 1);

        sceneCombo = new QComboBox(centralWidget);
        sceneCombo->setObjectName(QString::fromUtf8("sceneCombo"));
        sceneCombo->setFont(font);
        sceneCombo->setStyleSheet(QString::fromUtf8("QComboBox\n"
"{\n"
"    color:white;\n"
"    background-color: rgba(40,40,40,100);\n"
"    padding: 1px 0px 1px 3px; /*This makes text colour work*/\n"
"}\n"
"\n"
"\n"
"\n"
""));
        sceneCombo->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        sceneCombo->setMinimumContentsLength(16);
        sceneCombo->setFrame(false);

        gridLayout->addWidget(sceneCombo, 0, 9, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label_2, 0, 5, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 4, 1, 1);

        rendererCombo = new QComboBox(centralWidget);
        rendererCombo->setObjectName(QString::fromUtf8("rendererCombo"));
        rendererCombo->setFont(font);
        rendererCombo->setAutoFillBackground(false);
        rendererCombo->setStyleSheet(QString::fromUtf8("QComboBox\n"
"{\n"
"    color:white;\n"
"    background-color: rgba(40,40,40,100);\n"
"    padding: 1px 0px 1px 3px; /*This makes text colour work*/\n"
"}"));
        rendererCombo->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        rendererCombo->setMinimumContentsLength(16);
        rendererCombo->setFrame(false);

        gridLayout->addWidget(rendererCombo, 0, 3, 1, 1);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setFont(font);
        widget->setAutoFillBackground(false);
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        horizontalLayout_2->addLayout(verticalLayout);


        gridLayout->addWidget(widget, 1, 0, 1, 12);


        horizontalLayout->addLayout(gridLayout);

        application_window->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(application_window);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 935, 17));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush9);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush9);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush9);
        QBrush brush10(QColor(255, 119, 0, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Highlight, brush10);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipBase, brush);
        QBrush brush11(QColor(200, 200, 200, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipText, brush11);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush9);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush9);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush9);
        palette2.setBrush(QPalette::Inactive, QPalette::Highlight, brush10);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush11);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush9);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush9);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush9);
        palette2.setBrush(QPalette::Disabled, QPalette::Highlight, brush5);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush11);
        menuBar->setPalette(palette2);
        menuBar->setFont(font);
        menuBar->setAutoFillBackground(false);
        menuBar->setStyleSheet(QString::fromUtf8("QMenuBar {\n"
"    background-color: rgb(40,40,40);\n"
"	color: rgb(255,255,255);\n"
"}\n"
"\n"
"QMenuBar::item {\n"
"    spacing: 3px; /* spacing between menu bar items */\n"
"    padding: 1px 4px;\n"
"    background: transparent;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QMenuBar::item:selected { /* when selected using mouse or keyboard */\n"
"    background: #a8a8a8;\n"
"}\n"
"\n"
"QMenuBar::item:pressed {\n"
"    background: #888888;\n"
"}"));
        menuBar->setDefaultUp(false);
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush9);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush9);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush9);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush9);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush9);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush9);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush9);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush9);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush9);
        menuFile->setPalette(palette3);
        menuFile->setFont(font);
        menuFile->setAutoFillBackground(false);
        menuFile->setStyleSheet(QString::fromUtf8("QMenu {\n"
"  background-color: rgb(40,40,40);\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QMenu::item:selected {\n"
"  background: orange;\n"
"	color: rgb(255, 255, 255);\n"
" }\n"
"\n"
"QMenu::item:pressed {\n"
"	color: rgb(200, 200, 200);\n"
"  background: orange;\n"
" }"));
        menuFile->setSeparatorsCollapsible(false);
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Button, brush9);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush9);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush9);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush9);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush9);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush9);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush9);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush9);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush9);
        menuEdit->setPalette(palette4);
        menuEdit->setFont(font);
        menuEdit->setAutoFillBackground(false);
        menuEdit->setStyleSheet(QString::fromUtf8("QMenu {\n"
"  background-color: rgb(40,40,40);\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QMenu::item:selected {\n"
"  background: orange;\n"
"	color: rgb(255, 255, 255);\n"
" }\n"
"\n"
"QMenu::item:pressed {\n"
"	color: rgb(200, 200, 200);\n"
"  background: orange;\n"
" }"));
        menuEdit->setSeparatorsCollapsible(false);
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuView->setFont(font);
        menuView->setAutoFillBackground(false);
        menuView->setStyleSheet(QString::fromUtf8("QMenu {\n"
"  background-color: rgb(40,40,40);\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QMenu::item:selected {\n"
"  background: orange;\n"
"	color: rgb(255, 255, 255);\n"
" }\n"
"\n"
"QMenu::item:pressed {\n"
"	color: rgb(200, 200, 200);\n"
"  background: orange;\n"
" }"));
        menuView->setSeparatorsCollapsible(false);
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        menuAbout->setFont(font);
        menuAbout->setAutoFillBackground(false);
        menuAbout->setStyleSheet(QString::fromUtf8("QMenu {\n"
"  background-color: rgb(40,40,40);\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QMenu::item:selected {\n"
"  background: orange;\n"
"	color: rgb(255, 255, 255);\n"
" }\n"
"\n"
"QMenu::item:pressed {\n"
"	color: rgb(200, 200, 200);\n"
"  background: orange;\n"
" }"));
        application_window->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSaveAs);
        menuFile->addSeparator();
        menuFile->addAction(actionShaderProperties);
        menuFile->addAction(actionCodePreview);
        menuFile->addAction(actionExportScene);
        menuFile->addSeparator();
        menuFile->addAction(actionOptions);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addAction(actionCut);
        menuEdit->addSeparator();
        menuEdit->addAction(actionGroup);
        menuEdit->addAction(actionUngroup);
        menuEdit->addSeparator();
        menuEdit->addAction(actionEditBlock);
        menuEdit->addAction(actionDeleteBlocks);
        menuView->addAction(actionShowGrid);
        menuView->addSeparator();
        menuView->addAction(actionSnapBlocks);
        menuAbout->addAction(actionHelp);
        menuAbout->addSeparator();
        menuAbout->addAction(actionAbout);
        menuAbout->addAction(actionCredits);

        retranslateUi(application_window);

        QMetaObject::connectSlotsByName(application_window);
    } // setupUi

    void retranslateUi(QMainWindow *application_window)
    {
        application_window->setWindowTitle(QApplication::translate("application_window", "application_window", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("application_window", "New", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionNew->setToolTip(QApplication::translate("application_window", "New Scene", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionNew->setShortcut(QApplication::translate("application_window", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("application_window", "Open", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("application_window", "Open Scene", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOpen->setShortcut(QApplication::translate("application_window", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("application_window", "Save", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("application_window", "Save Scene", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSave->setShortcut(QApplication::translate("application_window", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionSaveAs->setText(QApplication::translate("application_window", "Save As...", 0, QApplication::UnicodeUTF8));
        actionSaveAs->setShortcut(QApplication::translate("application_window", "Ctrl+Shift+S", 0, QApplication::UnicodeUTF8));
        actionShaderProperties->setText(QApplication::translate("application_window", "Shader Properties", 0, QApplication::UnicodeUTF8));
        actionCodePreview->setText(QApplication::translate("application_window", "Code Preview", 0, QApplication::UnicodeUTF8));
        actionExportScene->setText(QApplication::translate("application_window", "Export Scene", 0, QApplication::UnicodeUTF8));
        actionExportScene->setShortcut(QApplication::translate("application_window", "Ctrl+E", 0, QApplication::UnicodeUTF8));
        actionOptions->setText(QApplication::translate("application_window", "Options", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("application_window", "Quit", 0, QApplication::UnicodeUTF8));
        actionCopy->setText(QApplication::translate("application_window", "Copy", 0, QApplication::UnicodeUTF8));
        actionCopy->setShortcut(QApplication::translate("application_window", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        actionPaste->setText(QApplication::translate("application_window", "Paste", 0, QApplication::UnicodeUTF8));
        actionPaste->setShortcut(QApplication::translate("application_window", "Ctrl+V", 0, QApplication::UnicodeUTF8));
        actionCut->setText(QApplication::translate("application_window", "Cut", 0, QApplication::UnicodeUTF8));
        actionCut->setShortcut(QApplication::translate("application_window", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        actionGroup->setText(QApplication::translate("application_window", "Group", 0, QApplication::UnicodeUTF8));
        actionGroup->setShortcut(QApplication::translate("application_window", "Ctrl+G", 0, QApplication::UnicodeUTF8));
        actionUngroup->setText(QApplication::translate("application_window", "Ungroup", 0, QApplication::UnicodeUTF8));
        actionUngroup->setShortcut(QApplication::translate("application_window", "Ctrl+U", 0, QApplication::UnicodeUTF8));
        actionEditBlock->setText(QApplication::translate("application_window", "Edit Block", 0, QApplication::UnicodeUTF8));
        actionEditBlock->setShortcut(QApplication::translate("application_window", "Shift+E", 0, QApplication::UnicodeUTF8));
        actionDeleteBlocks->setText(QApplication::translate("application_window", "Delete Blocks", 0, QApplication::UnicodeUTF8));
        actionDeleteBlocks->setShortcut(QApplication::translate("application_window", "Del", 0, QApplication::UnicodeUTF8));
        actionShowGrid->setText(QApplication::translate("application_window", "Show Grid", 0, QApplication::UnicodeUTF8));
        actionShowGrid->setShortcut(QApplication::translate("application_window", "G", 0, QApplication::UnicodeUTF8));
        actionSnapBlocks->setText(QApplication::translate("application_window", "Snap Blocks", 0, QApplication::UnicodeUTF8));
        actionSnapBlocks->setShortcut(QApplication::translate("application_window", "S", 0, QApplication::UnicodeUTF8));
        actionHelp->setText(QApplication::translate("application_window", "Help", 0, QApplication::UnicodeUTF8));
        actionHelp->setShortcut(QApplication::translate("application_window", "F1", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("application_window", "About", 0, QApplication::UnicodeUTF8));
        actionCredits->setText(QApplication::translate("application_window", "Credits", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        addBlockButton->setToolTip(QApplication::translate("application_window", "Add a predefined block to the scene", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        addBlockButton->setText(QApplication::translate("application_window", "Add Block", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("application_window", "Renderer", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        displayCombo->setToolTip(QApplication::translate("application_window", "Select one of the renderer's displays", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("application_window", "Scene", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        renderButton->setToolTip(QApplication::translate("application_window", "Click to preview the shader using selected renderer and display", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        renderButton->setText(QApplication::translate("application_window", "Render", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("application_window", "Zoom", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        zoomSlider->setToolTip(QApplication::translate("application_window", "Drag to zoom in or out", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        fitSceneButton->setToolTip(QApplication::translate("application_window", "Click to fit the block scene to the current view", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        fitSceneButton->setText(QApplication::translate("application_window", "Fit Scene", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sceneCombo->setToolTip(QApplication::translate("application_window", "Choose a 3D scene for preview", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("application_window", "Display", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        rendererCombo->setToolTip(QApplication::translate("application_window", "Choose an installed RenderMan engine", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        menuFile->setTitle(QApplication::translate("application_window", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("application_window", "Edit", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("application_window", "View", 0, QApplication::UnicodeUTF8));
        menuAbout->setTitle(QApplication::translate("application_window", "About", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class application_window: public Ui_application_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLICATION_WINDOW_H
