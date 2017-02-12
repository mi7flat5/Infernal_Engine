#pragma once
//
#include "qopenglwidget.h"
#include"qopenglfunctions.h"

class QOpenGLFramebufferObject;
using ObjectMap = std::map< unsigned int, StrongObjectPtr>;
class EditWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
	bool Fmove, Bmove, Lmove, Rmove, UpMove, DownMove;
public:
	EditWindow(QWidget *parent);
	~EditWindow();
	void UpdateContext();
	void setOwner(QMainWindow* inOwn) { owner = inOwn; }

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

	void MoveUp(float rate);
private:




	QTimer* timer;
	QTime AnotherTimerBecausQtIsntSoCute;;
	GLenum glewCheck;


	GLfloat lastX, lastY, lastFrame;
	void init();
	QMainWindow* owner;
	GLfloat rate;

	QOpenGLFramebufferObject* Fbo = nullptr;
	int hackX, hackY;
	bool picking = false;
	//move to main window
	void SetSelectedDelegate(IEventDataPtr pEventData);



	//move to library side application layer
	GLuint FBO, PickingTexture, DepthTexture;
	Scene* m_pScene;
	CameraNode* m_pCamera;


};



