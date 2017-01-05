#include"stdafx.h"

#include "EditWindow.h"

#include <QMouseEvent>

#include <QCoreApplication>
#include"InfernalEditor.h"
#include"..//Engine_Source/SHObject/Object3D.h"
void EditWindow::resizeGL(int w, int h)
{
	m_pCamera->SetProjection(w,h);
	
}

EditWindow::EditWindow(QWidget *parent)
	: QOpenGLWidget(parent)
{
	m_pCamera = nullptr;
	m_pScene = nullptr;
	m_pEventManager = nullptr;
	maker = new ObjectFactory();
	//MainWindow = parent;
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	

	timer->start();
	lastX = lastY = 0;
	
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



unsigned int EditWindow::AddObjectToScene(const char* resource) 
{
	makeCurrent();
	StrongObjectPtr newObject(maker->CreateActor(INVALID_OBJECT_ID,resource));
	m_ObjectTable.emplace(newObject->GetId(),newObject);
	EDITOR_LOG("added object to scene!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
	return newObject->GetId();

}

void EditWindow::RemoveFromScene(int ObjectId)
{

	
		
	glClearColor(0.0f, 0.2f, 0.9f, 1.0f);
	
		m_ObjectTable.erase(ObjectId);
		std::shared_ptr<EvtData_Destroy_Actor> pEvent(INFERNAL_NEW EvtData_Destroy_Actor(ObjectId));
		
		IEventManager::Get()->VQueueEvent(pEvent);

}

//void EditWindow::RemoveFromScene()
//{
//
//	
//	
//}

void EditWindow::init()
{
	makeCurrent();
	//assert(m_pEventManager);
	if(!m_pEventManager)
	m_pEventManager = new EventManager("Infernal Event Mgr", true);
	if(!m_pScene)
	m_pScene = new Scene();
	if (!m_pCamera) {
		InfernalEditor* properOwnerPointer = dynamic_cast<InfernalEditor*>(owner);
		properOwnerPointer->registerDelegate();
		m_pCamera = new CameraNode(INVALID_OBJECT_ID,
			WeakBaseRenderComponentPtr(), (RenderPass)0);
		std::shared_ptr<CameraNode> cam(m_pCamera);
		m_pScene->AddChild(m_pCamera->GetObjectId(), cam);
		m_pScene->SetCamera(cam);
		
		
		
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
	m_pEventManager->VUpdate(1);
	
	
}



void EditWindow::wheelEvent(QWheelEvent *event) 
{
	m_pCamera->SetCamRadius(event->delta());
}

void EditWindow::mousePressEvent(QMouseEvent *event)
{
	
}

void EditWindow::mouseReleaseEvent(QMouseEvent *event) 
{
	
}

void EditWindow::mouseMoveEvent(QMouseEvent *event)
{
	double xpos, ypos;
	xpos = event->x();
	ypos = event->y();

	if (event->buttons() & Qt::LeftButton)
	{

		GLfloat xoffset = xpos - lastX;
		GLfloat yoffset = ypos - lastY;
		/*lastX = xpos;
		lastY = ypos;*/

		GLfloat sensitivity = 0.3;	// TODO make variable for sensitivity
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		m_pCamera->SetYaw(xoffset);
		m_pCamera->SetPitch(yoffset);
	}
	if (event->buttons() & Qt::RightButton)
	{

		GLfloat xoffset = lastX - xpos;
		GLfloat yoffset = ypos - lastY;
		/*lastX = xpos;
		lastY = ypos;*/

		GLfloat sensitivity = 0.3;	// TODO make variable for sensitivity
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		m_pCamera->SetYaw(xoffset);
		m_pCamera->SetPitch(yoffset);

	}


	lastX = xpos;
	lastY = ypos;
}


