#pragma once
//
#include "qopenglwidget.h"
#include"qopenglfunctions.h"

using ObjectMap  = std::map< unsigned int, StrongObjectPtr>;
class EditWindow :	public QOpenGLWidget, protected QOpenGLFunctions
{
public:
	 EditWindow(QWidget *parent);
	~EditWindow();
	unsigned int AddObjectToScene(const char* resource);
	void setOwner(QMainWindow* inOwn) { owner = inOwn; }
	void RemoveFromScene(int );
public slots:
	
	void cleanup();

signals:


protected:
	void initializeGL() Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;
	void wheelEvent(QWheelEvent *event)Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void resizeGL(int w, int h)Q_DECL_OVERRIDE;
	

private:
	ObjectMap m_ObjectTable;
	EventManager* m_pEventManager;
	Scene* m_pScene;
	CameraNode* m_pCamera;
	ObjectFactory* maker;
	
	GLenum glewCheck;
	GLfloat lastX, lastY;
	void init();
	QMainWindow* owner;
	
	
};

