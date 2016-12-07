#include"stdafx.h"

#include "EditWindow.h"

#include <QMouseEvent>

#include <QCoreApplication>


void EditWindow::resizeGL(int w, int h)
{
	m_pCamera->SetProjection(this->width(),this->height());
}

EditWindow::EditWindow(QWidget *parent)
	: QOpenGLWidget(parent)
{
	m_pCamera = nullptr;
	m_pScene = nullptr;
	m_pEventManager = nullptr;
	//MainWindow = parent;
	
	
}

EditWindow::~EditWindow()
{
	delete m_pCamera;
	m_pCamera = nullptr;
	delete m_pScene;
	m_pScene = nullptr;
	delete m_pEventManager;
	m_pEventManager = nullptr;
	
}



void EditWindow::init()
{
	makeCurrent();
	//assert(m_pEventManager);
	if(!m_pEventManager)
	m_pEventManager = new EventManager("Infernal Event Mgr", true);
	if(!m_pScene)
	m_pScene = new Scene();
	if (!m_pCamera) {
		m_pCamera = new CameraNode(INVALID_OBJECT_ID,
			WeakBaseRenderComponentPtr(), (RenderPass)0);
		std::shared_ptr<CameraNode> cam(m_pCamera);
		m_pScene->AddChild(m_pCamera->GetObjectId(), cam);
		m_pScene->SetCamera(cam);
		maker = new ObjectFactory();
		maker->CreateActor(INVALID_OBJECT_ID);
	}
	
	
	glClearColor(0.7f, 0.2f, 0.2f, 1.0f);
	
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
	
	
	
	
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	

	
	
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	
	init();
}

void EditWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	m_pScene->OnUpdate(g_DeltaTime);//g_deltatime in Engine.h, will need to be managed somewhere in the editor


	m_pScene->OnRender();
	
	
	
}



void EditWindow::mousePressEvent(QMouseEvent *event)
{
	
}

void EditWindow::mouseMoveEvent(QMouseEvent *event)
{

}


