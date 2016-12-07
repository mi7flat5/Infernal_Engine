#pragma once
//
#include "qopenglwidget.h"
#include"qopenglfunctions.h"
//#include "InfernalEditor.h"

class EditWindow :	public QOpenGLWidget, protected QOpenGLFunctions
{
public:
	 EditWindow(QWidget *parent);
	~EditWindow();

	
public slots:
	
	void cleanup();

signals:


protected:
	void initializeGL() Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;
	// void resizeGL(int width, int height) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void resizeGL(int w, int h);
	

private:
	
	EventManager* m_pEventManager;
	Scene* m_pScene;
	CameraNode* m_pCamera;
	ObjectFactory* maker;
	GLenum glewCheck;
	void init();
	//InfernalEditor* MainWindow;
	
	
};

