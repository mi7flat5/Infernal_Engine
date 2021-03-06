#include"stdafx.h"
#include "EditWindow.h"
#include <QMouseEvent>
#include <QCoreApplication>
#include"InfernalEditor.h"
#include"..//Engine_Source/SHObject/Object3D.h"


#include <QOffscreenSurface>
void EditWindow::resizeGL(int w, int h)
{
		GetCamera()->SetProjection(w, h);
	if (Fbo)
	{
		delete Fbo;
		
	}
	
	QSize s;
	s.setHeight(height());
	s.setWidth(width());
	Fbo = new QOpenGLFramebufferObject(s);
}
EditWindow::EditWindow(QWidget *parent)
	: QOpenGLWidget(parent)
{

	timer = new QTimer(this);


	connect(timer, SIGNAL(timeout()), this, SLOT(update()));

	AnotherTimerBecausQtIsntSoCute.start();
	timer->start();
	lastX = lastY = 0;
	Fmove = Bmove = Lmove = Rmove = UpMove = DownMove = false;
	cursorX = INVALID_OBJECT_ID;
	cursorY = INVALID_OBJECT_ID;
	cursorZ = INVALID_OBJECT_ID;
}
EditWindow::~EditWindow()
{
}

void EditWindow::UpdateContext()
{
	makeCurrent();
}

void EditWindow::init()
{
	makeCurrent();
	
}

void EditWindow::cleanup()
{

	//makeCurrent();
	//doneCurrent();

}
void EditWindow::initializeGL()
{
	glewCheck = glewInit();
	glewExperimental = GL_TRUE;
	initializeOpenGLFunctions();


	QSurfaceFormat glFormat;
	glFormat.setVersion(4, 3);
	glFormat.setProfile(QSurfaceFormat::CoreProfile); // Requires >=Qt-4.8.0

	context()->setFormat(glFormat);

	connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &EditWindow::cleanup);
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	init();
}

void EditWindow::paintGL()
{

	GLfloat currentFrame = AnotherTimerBecausQtIsntSoCute.elapsed();

	g_DeltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	rate = g_DeltaTime * 0.00700;

	if (Rmove) {
		MoveRight(rate);
	}
	if (Lmove) {
		MoveRight(-rate);
	}
	if (Fmove) {
		MoveForward(rate);
	}
	if (Bmove) {
		MoveForward(-rate);
	}
	if (UpMove) {
		MoveUp(rate);
	}
	if (DownMove) {
		MoveUp(-rate);
	}
	

	GetScene()->OnUpdate(g_DeltaTime);
	if (picking) {

			picking = false;
	}
	
	GetScene()->OnRender();
	
	IEventManager::Get()->VUpdate();
}

void EditWindow::wheelEvent(QWheelEvent *event)
{
	GetCamera()->SetCamRadius(event->delta());
}

void EditWindow::mousePressEvent(QMouseEvent *event)
{
	//std::shared_ptr<EvtData_RayCast> pEvent(INFERNAL_NEW EvtData_RayCast(width(), height(), event->x(), event->y()));
	//
	//IEventManager::Get()->VQueueEvent(pEvent);
		
	makeCurrent();
	Fbo->bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GetScene()->SetPicking(true);
	GetScene()->OnRender();
	GetScene()->SetPicking(false);
	
	Fbo->bindDefault();

	float IdColor[4];
		
	QImage  fboimage( Fbo->toImage());
	QImage image(fboimage.constBits(), fboimage.width(), fboimage.height(), QImage::Format_ARGB32);
	QPoint pixel = event->pos();

	
	QColor  color = image.pixelColor(event->pos());

	EDITOR_LOG(ToStr(color.red()))
	
			InfernalEditor*	pCastOwner = dynamic_cast<InfernalEditor *>(owner);
			pCastOwner->SetSelectedNode(color.red());
	
	
}

void EditWindow::mouseReleaseEvent(QMouseEvent *event)
{

}

void EditWindow::keyReleaseEvent(QKeyEvent *event)
{
	if (!event->isAutoRepeat()) {
		if (event->key() == Qt::Key_W)
		{
			Fmove = false;
		}
		if (event->key() == Qt::Key_S)
		{
			Bmove = false;
		}
		if (event->key() == Qt::Key_D)
		{
			Rmove = false;
		}
		if (event->key() == Qt::Key_A)
		{
			Lmove = false;
		}
		if (!(event->modifiers()& Qt::ShiftModifier) && event->key() == Qt::Key_Space)
		{
			UpMove = false;
		}
		if (event->modifiers()& Qt::ShiftModifier && event->key() == Qt::Key_Space)
		{
			DownMove = false;
		}
	}
}

void EditWindow::keyPressEvent(QKeyEvent *event)
{


	if (!event->isAutoRepeat()) {
		if (event->key() == Qt::Key_W)
		{
			Fmove = true;
		}
		if (event->key() == Qt::Key_S)
		{
			Bmove = true;
		}

		if (event->key() == Qt::Key_A)
		{
			Lmove = true;
		}
		if (event->key() == Qt::Key_D)
		{
			Rmove = true;
		}
		if (!(event->modifiers()& Qt::ShiftModifier) && event->key() == Qt::Key_Space)
		{
			UpMove = true;
		}
		if ((event->modifiers()& Qt::ShiftModifier) && (event->key() == Qt::Key_Space))
		{
			DownMove = true;
		}
	}
}
void EditWindow::MoveForward(float rate) { GetCamera()->MoveForward(3.5f*rate); }

void EditWindow::MoveRight(float rate) { GetCamera()->MoveRight(3.5f*rate); }
void EditWindow::MoveUp(float rate) { GetCamera()->MoveUp(3.5*rate); }
void EditWindow::mouseMoveEvent(QMouseEvent *event)
{
	double xpos, ypos;
	xpos = event->x();
	ypos = event->y();


	if (event->buttons() & Qt::RightButton)
	{

		GLfloat xoffset = lastX - xpos;
		GLfloat yoffset = ypos - lastY;
		/*lastX = xpos;
		lastY = ypos;*/

		GLfloat sensitivity = 0.3;	// TODO make variable for sensitivity
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		GetCamera()->SetYaw(xoffset);
		GetCamera()->SetPitch(yoffset);

	}


	lastX = xpos;
	lastY = ypos;

}