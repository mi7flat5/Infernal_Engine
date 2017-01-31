/********************************************************************************
** Form generated from reading UI file 'InfernalEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFERNALEDITOR_H
#define UI_INFERNALEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>
#include "EditWindow.h"

QT_BEGIN_NAMESPACE

class Ui_InfernalEditorClass
{
public:
    QAction *action_Open;
    QAction *actionOpen;
    QAction *action_Open_2;
    QWidget *centralWidget;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout;
    EditWindow *openGLWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QTreeView *treeView;
    QWidget *tab_2;
    QGridLayout *gridLayout_4;
    QTextBrowser *textBrowser;
    QWidget *tab_3;
    QGridLayout *gridLayout_7;
    QToolBox *toolBox;
    QWidget *page;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_5;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label;
    QDoubleSpinBox *pX;
    QDoubleSpinBox *pY;
    QDoubleSpinBox *pZ;
    QLabel *label_2;
    QDoubleSpinBox *rX;
    QDoubleSpinBox *rY;
    QDoubleSpinBox *rZ;
    QLabel *label_3;
    QDoubleSpinBox *sX;
    QDoubleSpinBox *sY;
    QDoubleSpinBox *sZ;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QWidget *page_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *InfernalEditorClass)
    {
        if (InfernalEditorClass->objectName().isEmpty())
            InfernalEditorClass->setObjectName(QStringLiteral("InfernalEditorClass"));
        InfernalEditorClass->resize(819, 711);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(InfernalEditorClass->sizePolicy().hasHeightForWidth());
        InfernalEditorClass->setSizePolicy(sizePolicy);
        InfernalEditorClass->setMouseTracking(true);
        InfernalEditorClass->setFocusPolicy(Qt::StrongFocus);
        InfernalEditorClass->setAutoFillBackground(true);
        action_Open = new QAction(InfernalEditorClass);
        action_Open->setObjectName(QStringLiteral("action_Open"));
        actionOpen = new QAction(InfernalEditorClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        action_Open_2 = new QAction(InfernalEditorClass);
        action_Open_2->setObjectName(QStringLiteral("action_Open_2"));
        centralWidget = new QWidget(InfernalEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout_6 = new QGridLayout(centralWidget);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        openGLWidget = new EditWindow(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        openGLWidget->setMinimumSize(QSize(16, 9));
        openGLWidget->setSizeIncrement(QSize(16, 10));
        openGLWidget->setBaseSize(QSize(16, 10));
        openGLWidget->setCursor(QCursor(Qt::CrossCursor));
        openGLWidget->setMouseTracking(true);
        openGLWidget->setFocusPolicy(Qt::StrongFocus);
        openGLWidget->setContextMenuPolicy(Qt::NoContextMenu);
        openGLWidget->setAcceptDrops(true);
        openGLWidget->setAutoFillBackground(true);
        openGLWidget->setInputMethodHints(Qt::ImhHiddenText);

        gridLayout->addWidget(openGLWidget, 0, 0, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setContextMenuPolicy(Qt::NoContextMenu);
        tabWidget->setTabShape(QTabWidget::Triangular);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        treeView = new QTreeView(tab);
        treeView->setObjectName(QStringLiteral("treeView"));
        sizePolicy.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(treeView, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_4 = new QGridLayout(tab_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        textBrowser = new QTextBrowser(tab_2);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        sizePolicy.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy);
        textBrowser->setMinimumSize(QSize(0, 10));
        textBrowser->setMaximumSize(QSize(16777215, 1677215));
        textBrowser->setReadOnly(false);

        gridLayout_4->addWidget(textBrowser, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_7 = new QGridLayout(tab_3);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        toolBox = new QToolBox(tab_3);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setContextMenuPolicy(Qt::NoContextMenu);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 372, 558));
        gridLayout_8 = new QGridLayout(page);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_4 = new QLabel(page);
        label_4->setObjectName(QStringLiteral("label_4"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(label_4, 0, 1, 1, 1);

        label_5 = new QLabel(page);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(label_5, 0, 2, 1, 1);

        label_6 = new QLabel(page);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(label_6, 0, 3, 1, 1);

        label = new QLabel(page);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(50, 16777215));

        gridLayout_5->addWidget(label, 1, 0, 1, 1);

        pX = new QDoubleSpinBox(page);
        pX->setObjectName(QStringLiteral("pX"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pX->sizePolicy().hasHeightForWidth());
        pX->setSizePolicy(sizePolicy2);
        pX->setMinimumSize(QSize(20, 0));
        pX->setMinimum(-2048);
        pX->setMaximum(2048);

        gridLayout_5->addWidget(pX, 1, 1, 1, 1);

        pY = new QDoubleSpinBox(page);
        pY->setObjectName(QStringLiteral("pY"));
        pY->setMinimum(-2048);
        pY->setMaximum(2048);

        gridLayout_5->addWidget(pY, 1, 2, 1, 1);

        pZ = new QDoubleSpinBox(page);
        pZ->setObjectName(QStringLiteral("pZ"));
        pZ->setMinimum(-2048);
        pZ->setMaximum(2048);

        gridLayout_5->addWidget(pZ, 1, 3, 1, 1);

        label_2 = new QLabel(page);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_5->addWidget(label_2, 2, 0, 1, 1);

        rX = new QDoubleSpinBox(page);
        rX->setObjectName(QStringLiteral("rX"));
        rX->setMinimum(-180);
        rX->setMaximum(180);

        gridLayout_5->addWidget(rX, 2, 1, 1, 1);

        rY = new QDoubleSpinBox(page);
        rY->setObjectName(QStringLiteral("rY"));
        rY->setMinimum(-180);
        rY->setMaximum(180);

        gridLayout_5->addWidget(rY, 2, 2, 1, 1);

        rZ = new QDoubleSpinBox(page);
        rZ->setObjectName(QStringLiteral("rZ"));
        rZ->setMinimum(-180);
        rZ->setMaximum(180);

        gridLayout_5->addWidget(rZ, 2, 3, 1, 1);

        label_3 = new QLabel(page);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_5->addWidget(label_3, 3, 0, 1, 1);

        sX = new QDoubleSpinBox(page);
        sX->setObjectName(QStringLiteral("sX"));
        sX->setDecimals(3);
        sX->setMinimum(0.001);
        sX->setMaximum(20);
        sX->setSingleStep(0.01);

        gridLayout_5->addWidget(sX, 3, 1, 1, 1);

        sY = new QDoubleSpinBox(page);
        sY->setObjectName(QStringLiteral("sY"));
        sY->setDecimals(3);
        sY->setMinimum(0.001);
        sY->setMaximum(20);
        sY->setSingleStep(0.01);

        gridLayout_5->addWidget(sY, 3, 2, 1, 1);

        sZ = new QDoubleSpinBox(page);
        sZ->setObjectName(QStringLiteral("sZ"));
        sZ->setDecimals(3);
        sZ->setMinimum(0.001);
        sZ->setMaximum(20);
        sZ->setSingleStep(0.01);

        gridLayout_5->addWidget(sZ, 3, 3, 1, 1);


        gridLayout_8->addLayout(gridLayout_5, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 438, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_8->addItem(verticalSpacer, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer, 0, 1, 1, 1);

        toolBox->addItem(page, QStringLiteral("Transform"));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 98, 28));
        toolBox->addItem(page_2, QStringLiteral("Page 2"));

        gridLayout_7->addWidget(toolBox, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout, 0, 0, 1, 1);

        InfernalEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(InfernalEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 819, 21));
        InfernalEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(InfernalEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setContextMenuPolicy(Qt::NoContextMenu);
        InfernalEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(InfernalEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        InfernalEditorClass->setStatusBar(statusBar);

        retranslateUi(InfernalEditorClass);

        tabWidget->setCurrentIndex(0);
        toolBox->setCurrentIndex(0);
        toolBox->layout()->setSpacing(0);


        QMetaObject::connectSlotsByName(InfernalEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *InfernalEditorClass)
    {
        InfernalEditorClass->setWindowTitle(QApplication::translate("InfernalEditorClass", "InfernalEditor", 0));
        action_Open->setText(QApplication::translate("InfernalEditorClass", "&Open", 0));
        actionOpen->setText(QApplication::translate("InfernalEditorClass", "Open", 0));
        action_Open_2->setText(QApplication::translate("InfernalEditorClass", "&Open", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("InfernalEditorClass", "Scene", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("InfernalEditorClass", "Log", 0));
        label_4->setText(QApplication::translate("InfernalEditorClass", "X", 0));
        label_5->setText(QApplication::translate("InfernalEditorClass", "Y", 0));
        label_6->setText(QApplication::translate("InfernalEditorClass", "Z", 0));
        label->setText(QApplication::translate("InfernalEditorClass", "Position", 0));
        label_2->setText(QApplication::translate("InfernalEditorClass", "Rotation", 0));
        label_3->setText(QApplication::translate("InfernalEditorClass", "Scale", 0));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("InfernalEditorClass", "Transform", 0));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("InfernalEditorClass", "Page 2", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("InfernalEditorClass", "Page", 0));
    } // retranslateUi

};

namespace Ui {
    class InfernalEditorClass: public Ui_InfernalEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFERNALEDITOR_H
