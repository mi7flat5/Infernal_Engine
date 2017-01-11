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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
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
    QGridLayout *gridLayout_2;
    EditWindow *openGLWidget;
    QSplitter *splitter;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_4;
    QDoubleSpinBox *ylpos;
    QDoubleSpinBox *zlpos;
    QDoubleSpinBox *xlpos;
    QTabWidget *tabWidget;
    QWidget *tab;
    QFormLayout *formLayout;
    QTreeView *treeView;
    QWidget *tab_2;
    QGridLayout *gridLayout_5;
    QTextBrowser *textBrowser;
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
        InfernalEditorClass->resize(875, 571);
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
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        openGLWidget = new EditWindow(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        openGLWidget->setMinimumSize(QSize(650, 9));
        openGLWidget->setSizeIncrement(QSize(16, 10));
        openGLWidget->setBaseSize(QSize(16, 10));
        openGLWidget->setCursor(QCursor(Qt::CrossCursor));
        openGLWidget->setMouseTracking(true);
        openGLWidget->setFocusPolicy(Qt::StrongFocus);
        openGLWidget->setContextMenuPolicy(Qt::PreventContextMenu);
        openGLWidget->setAcceptDrops(true);
        openGLWidget->setAutoFillBackground(true);
        openGLWidget->setInputMethodHints(Qt::ImhHiddenText);

        gridLayout_2->addWidget(openGLWidget, 0, 0, 1, 1);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(50, 9));
        groupBox->setMaximumSize(QSize(300, 16777215));
        groupBox->setSizeIncrement(QSize(16, 9));
        groupBox->setBaseSize(QSize(16, 9));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        ylpos = new QDoubleSpinBox(groupBox);
        ylpos->setObjectName(QStringLiteral("ylpos"));
        ylpos->setMinimum(-999);
        ylpos->setMaximum(999);
        ylpos->setSingleStep(10);

        gridLayout_4->addWidget(ylpos, 2, 0, 1, 1);

        zlpos = new QDoubleSpinBox(groupBox);
        zlpos->setObjectName(QStringLiteral("zlpos"));
        zlpos->setMinimum(-999);
        zlpos->setMaximum(999);
        zlpos->setSingleStep(10);

        gridLayout_4->addWidget(zlpos, 1, 0, 1, 1);

        xlpos = new QDoubleSpinBox(groupBox);
        xlpos->setObjectName(QStringLiteral("xlpos"));
        xlpos->setMinimum(-999);
        xlpos->setMaximum(999.99);
        xlpos->setSingleStep(10);

        gridLayout_4->addWidget(xlpos, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_4, 1, 1, 1, 1);

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

        formLayout->setWidget(0, QFormLayout::FieldRole, treeView);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_5 = new QGridLayout(tab_2);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        textBrowser = new QTextBrowser(tab_2);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        sizePolicy.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy);
        textBrowser->setMinimumSize(QSize(700, 10));
        textBrowser->setMaximumSize(QSize(16777215, 1677215));
        textBrowser->setReadOnly(false);

        gridLayout_5->addWidget(textBrowser, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);

        splitter->addWidget(groupBox);

        gridLayout_2->addWidget(splitter, 0, 1, 1, 1);

        InfernalEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(InfernalEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 875, 21));
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

        tabWidget->setCurrentIndex(1);


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
