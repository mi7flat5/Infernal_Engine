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
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
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
    QGridLayout *gridLayout;
    QTextBrowser *textBrowser;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QFormLayout *formLayout;
    QTreeView *treeView;
    QWidget *tab_2;
    EditWindow *openGLWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_3;

    void setupUi(QMainWindow *InfernalEditorClass)
    {
        if (InfernalEditorClass->objectName().isEmpty())
            InfernalEditorClass->setObjectName(QStringLiteral("InfernalEditorClass"));
        InfernalEditorClass->resize(855, 565);
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
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy1);
        textBrowser->setMinimumSize(QSize(0, 20));
        textBrowser->setMaximumSize(QSize(16777215, 150));
        textBrowser->setReadOnly(false);

        gridLayout->addWidget(textBrowser, 1, 0, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(16, 9));
        groupBox->setSizeIncrement(QSize(16, 9));
        groupBox->setBaseSize(QSize(16, 9));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tabWidget = new QTabWidget(groupBox);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        formLayout = new QFormLayout(tab);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        treeView = new QTreeView(tab);
        treeView->setObjectName(QStringLiteral("treeView"));

        formLayout->setWidget(0, QFormLayout::LabelRole, treeView);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 1, 1, 1);

        openGLWidget = new EditWindow(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy2);
        openGLWidget->setMinimumSize(QSize(16, 9));
        openGLWidget->setSizeIncrement(QSize(16, 10));
        openGLWidget->setBaseSize(QSize(16, 10));
        openGLWidget->setMouseTracking(true);
        openGLWidget->setFocusPolicy(Qt::NoFocus);
        openGLWidget->setContextMenuPolicy(Qt::PreventContextMenu);
        openGLWidget->setAutoFillBackground(true);

        gridLayout->addWidget(openGLWidget, 0, 0, 1, 1);

        InfernalEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(InfernalEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 855, 21));
        InfernalEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(InfernalEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        InfernalEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(InfernalEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        InfernalEditorClass->setStatusBar(statusBar);
        dockWidget = new QDockWidget(InfernalEditorClass);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidget->setContextMenuPolicy(Qt::PreventContextMenu);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout_3 = new QGridLayout(dockWidgetContents);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        dockWidget->setWidget(dockWidgetContents);
        InfernalEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockWidget);

        retranslateUi(InfernalEditorClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(InfernalEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *InfernalEditorClass)
    {
        InfernalEditorClass->setWindowTitle(QApplication::translate("InfernalEditorClass", "InfernalEditor", 0));
        action_Open->setText(QApplication::translate("InfernalEditorClass", "&Open", 0));
        actionOpen->setText(QApplication::translate("InfernalEditorClass", "Open", 0));
        action_Open_2->setText(QApplication::translate("InfernalEditorClass", "&Open", 0));
        groupBox->setTitle(QApplication::translate("InfernalEditorClass", "GroupBox", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("InfernalEditorClass", "Tab 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("InfernalEditorClass", "Tab 2", 0));
    } // retranslateUi

};

namespace Ui {
    class InfernalEditorClass: public Ui_InfernalEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFERNALEDITOR_H
