#pragma once

#include <QWidget>
#include "ui_ActorCreationWindow.h"

class ActorCreationWindow : public QWidget
{
	friend class InfernalEditor;
	Q_OBJECT
		void SetOwner(QMainWindow* pMainWindow) { Owner = pMainWindow; }
		QMainWindow* Owner;
		void loadfile(const QString &fileName);
private slots:
	void CreatObject();
	
	void open();
public:
	ActorCreationWindow(QWidget *parent = Q_NULLPTR);
	~ActorCreationWindow();

private:
	Ui::ActorCreationWindow ui;
};
