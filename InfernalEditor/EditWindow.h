#pragma once
//
#include "qopenglwidget.h"
#include"qopenglfunctions.h"


class EditWindow :	public QOpenGLWidget, protected QOpenGLFunctions
{
public:
	 EditWindow(QWidget *parent);
	~EditWindow();
	bool AddObjectToScene(const char* resource);
	void setOwner(QMainWindow* inOwn) { owner = inOwn; }
	
public slots:
	
	void cleanup();

signals:


protected:
	void initializeGL() Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;
	
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void resizeGL(int w, int h)Q_DECL_OVERRIDE;
	

private:
	
	EventManager* m_pEventManager;
	Scene* m_pScene;
	CameraNode* m_pCamera;
	ObjectFactory* maker;
	
	GLenum glewCheck;
	void init();
	QMainWindow* owner;
	
	
};

