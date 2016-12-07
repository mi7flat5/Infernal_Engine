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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "EditWindow.h"

QT_BEGIN_NAMESPACE

class Ui_InfernalEditorClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    EditWindow *openGLWidget;
    QTextBrowser *textBrowser;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *InfernalEditorClass)
    {
        if (InfernalEditorClass->objectName().isEmpty())
            InfernalEditorClass->setObjectName(QStringLiteral("InfernalEditorClass"));
        InfernalEditorClass->resize(600, 618);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(InfernalEditorClass->sizePolicy().hasHeightForWidth());
        InfernalEditorClass->setSizePolicy(sizePolicy);
        InfernalEditorClass->setAutoFillBackground(true);
        centralWidget = new QWidget(InfernalEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        openGLWidget = new EditWindow(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        openGLWidget->setMouseTracking(true);
        openGLWidget->setFocusPolicy(Qt::ClickFocus);
        openGLWidget->setAutoFillBackground(true);

        gridLayout->addWidget(openGLWidget, 0, 0, 1, 1);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy1);
        textBrowser->setReadOnly(false);

        gridLayout->addWidget(textBrowser, 1, 0, 1, 1);

        InfernalEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(InfernalEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
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
    } // retranslateUi

};

namespace Ui {
    class InfernalEditorClass: public Ui_InfernalEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFERNALEDITOR_H
