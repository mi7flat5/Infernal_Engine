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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
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
    QGridLayout *gridLayout_2;
    EditWindow *openGLWidget;
    QTextBrowser *textBrowser;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox;
    QTreeView *treeView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *InfernalEditorClass)
    {
        if (InfernalEditorClass->objectName().isEmpty())
            InfernalEditorClass->setObjectName(QStringLiteral("InfernalEditorClass"));
        InfernalEditorClass->resize(1290, 904);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(InfernalEditorClass->sizePolicy().hasHeightForWidth());
        InfernalEditorClass->setSizePolicy(sizePolicy);
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
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        openGLWidget = new EditWindow(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy1);
        openGLWidget->setMinimumSize(QSize(16, 9));
        openGLWidget->setSizeIncrement(QSize(16, 9));
        openGLWidget->setBaseSize(QSize(0, 0));
        openGLWidget->setMouseTracking(false);
        openGLWidget->setFocusPolicy(Qt::NoFocus);
        openGLWidget->setAutoFillBackground(true);

        gridLayout_2->addWidget(openGLWidget, 0, 0, 1, 1);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy2);
        textBrowser->setReadOnly(false);

        gridLayout_2->addWidget(textBrowser, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));

        gridLayout_2->addWidget(groupBox_2, 1, 1, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(16, 9));
        groupBox->setSizeIncrement(QSize(16, 9));
        groupBox->setBaseSize(QSize(16, 9));
        treeView = new QTreeView(groupBox);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(20, 40, 256, 192));

        gridLayout_2->addWidget(groupBox, 0, 1, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 1, 2, 1);

        InfernalEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(InfernalEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1290, 21));
        InfernalEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(InfernalEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        InfernalEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(InfernalEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        InfernalEditorClass->setStatusBar(statusBar);

        retranslateUi(InfernalEditorClass);

        QMetaObject::connectSlotsByName(InfernalEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *InfernalEditorClass)
    {
        InfernalEditorClass->setWindowTitle(QApplication::translate("InfernalEditorClass", "InfernalEditor", 0));
        action_Open->setText(QApplication::translate("InfernalEditorClass", "&Open", 0));
        actionOpen->setText(QApplication::translate("InfernalEditorClass", "Open", 0));
        action_Open_2->setText(QApplication::translate("InfernalEditorClass", "&Open", 0));
        groupBox_2->setTitle(QApplication::translate("InfernalEditorClass", "GroupBox", 0));
        groupBox->setTitle(QApplication::translate("InfernalEditorClass", "GroupBox", 0));
    } // retranslateUi

};

namespace Ui {
    class InfernalEditorClass: public Ui_InfernalEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFERNALEDITOR_H
