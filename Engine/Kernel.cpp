#include"Engine.h"
#include"Kernel.h"
#include"ObjectFactory.h"



Kernel::Kernel()
{
	init();
}

void Kernel::runApp()
{
	ObjectFactory maker;
	maker.CreateActor(INVALID_OBJECT_ID);
	
	
	
	
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
		m_pScene->OnUpdate(g_DeltaTime);//g_deltatime is handled in movementcontroller.cpp currently TODO move out to kernal update loop


		m_pScene->OnRender();

		glfwSwapBuffers(pContext);

	


}

Kernel::~Kernel()
{
}
GLFWwindow * Kernel::getContext() const
{
	return pContext;
}
void Kernel::init()
{
	
		glfwInit();
		pContext = glfwCreateWindow(WIDTH, HEIGHT, "Loader", nullptr, nullptr);
	
		
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
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		

		glViewport(0, 0, WIDTH, HEIGHT);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		
		m_pEventManager.reset( INFERNAL_NEW EventManager("Infernal Event Mgr", true));
		m_pScene.reset( INFERNAL_NEW Scene());
		m_pCamera.reset(INFERNAL_NEW CameraNode(INVALID_OBJECT_ID,
			WeakBaseRenderComponentPtr(),(RenderPass)0));
		m_pScene->AddChild(m_pCamera->GetObjectId(),m_pCamera);
		m_pScene->SetCamera(m_pCamera);
		m_pController.reset(INFERNAL_NEW MovementController(pContext,m_pCamera));

}