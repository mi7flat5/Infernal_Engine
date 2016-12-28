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
		const char* GetRenderCompnentType();
private slots:
	void CreatObject();
	
	
	void SetFragShader();
	void SetVertexShader();
	void SetMeshAsset();
	

public:
	ActorCreationWindow(QWidget *parent = Q_NULLPTR);
	~ActorCreationWindow();

private:
	Ui::ActorCreationWindow ui;
};
