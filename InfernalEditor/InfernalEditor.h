#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_InfernalEditor.h"

class InfernalEditor : public QMainWindow
{
    Q_OBJECT

public:
    InfernalEditor(QWidget *parent = Q_NULLPTR);
public slots:


private slots:

	void stdLogOut();

private:
    Ui::InfernalEditorClass ui;
	
	QTimer* timer;
};
