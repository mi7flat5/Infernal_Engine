#pragma once
//
#include "qopenglwidget.h"
#include"qopenglfunctions.h"

using ObjectMap  = std::map< unsigned int, StrongObjectPtr>;
class EditWindow :	public QOpenGLWidget, protected QOpenGLFunctions
{	
	bool Fmove, Bmove, Lmove, Rmove;
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
	void resizeGL(int w, int h);
	void keyReleaseEvent(QKeyEvent *event)Q_DECL_OVERRIDE;
	void keyPressEvent(QKeyEvent *event)Q_DECL_OVERRIDE;

	void MoveForward(float);
	void MoveBackward(float);
	void MoveLeft(float);
	void MoveRight(float);
	
private:
	ObjectMap m_ObjectTable;
	EventManager* m_pEventManager;
	Scene* m_pScene;
	CameraNode* m_pCamera;
	ObjectFactory* maker;
	QTimer* timer;
	QTime AnotherTimerBecausQtIsntSoCute;;
	GLenum glewCheck;
	GLfloat lastX, lastY, lastFrame;
	void init();
	QMainWindow* owner;
	GLfloat rate;
	void SetSelectedDelegate(IEventDataPtr pEventData);
	std::shared_ptr<SceneNode> m_pSelectedNode;
	std::string m_SelectedObjectName;
	
};

