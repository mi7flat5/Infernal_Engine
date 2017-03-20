#include"Engine.h"
#include"Kernel.h"
#include<future>
#include<thread>
#
#include "..//SHObject/RenderComponent.h"
#include"..//SHObject/Object3D.h"
#include "../SHObject/ObjectComponent.h"

Kernel::Kernel()
{
	initContext();

}

void Kernel::runApp()
{
	
	
	LoadScene(std::string("Scene.rsc"));
	
	while (!glfwWindowShouldClose(pContext))
	{
	
		update();
	
	}
	
	
	glfwTerminate();
	
}

void Kernel::update() 
{

	

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_pController->UpdateControls();
		glfwPollEvents();
		
		
		m_pGame->GetScene()->OnUpdate(g_DeltaTime);//


		m_pGame->GetScene()->OnRender();
		IEventManager::Get()->VUpdate();
		glfwSwapBuffers(pContext);

	


}


Kernel::~Kernel()
{
}
GLFWwindow * Kernel::getContext() const
{
	return pContext;
}
void Kernel::LoadScene(std::string sceneFile)
{	
	tinyxml2::XMLDocument inDoc;
	if (inDoc.LoadFile(std::string("..//XML//" + sceneFile).c_str()))
	{
		EDITOR_LOG("Failed to load scene file  " + std::string("..//XML//" + sceneFile))
			return;
	}


	tinyxml2::XMLElement* pRoot = inDoc.FirstChildElement();

	for (tinyxml2::XMLElement* pNode = pRoot->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
	{
		
		StrongObjectPtr pObject = g_pApp->GetGameLogic()->VCreateActor(pNode->Attribute("resource"), INVALID_OBJECT_ID);
	
	}

}
void Kernel::initContext()
{
	
		glfwInit();
		Init();
		VCreateGameAndView();
		pContext = glfwCreateWindow(WIDTH, HEIGHT, "PROTO", nullptr, nullptr);
	
		
		if (pContext == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			system("pause");
			
		}
		glfwMakeContextCurrent(pContext);
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW" << std::endl;

		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		

		glViewport(0, 0, WIDTH, HEIGHT);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		
	
		m_pController.reset(INFERNAL_NEW MovementController(pContext,m_pGame->GetCamera()));

}