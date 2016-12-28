#include "Engine.h"
#include "MovementController.hpp"


void MovementController::Scroll_Callback(GLFWwindow * window, double xoffset, double yoffset)
{
}

void MovementController::Key_Callback(GLFWwindow *window, int, int, int, int)
{
}

MovementController::MovementController()
{
	
}

MovementController::MovementController(GLFWwindow * InWin, std::shared_ptr<CameraNode> InCam)
{
	m_pWindowController = InWin;
	m_pCamera = InCam;
	glfwSetScrollCallback(m_pWindowController, MovementController::Scroll_Callback);
	glfwSetKeyCallback(m_pWindowController, MovementController::Key_Callback);
	(m_pWindowController, GLFW_STICKY_KEYS, 1);
}
void MovementController::UpdateControls() 
{
	GLfloat currentFrame = glfwGetTime();
	g_DeltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	rate = g_DeltaTime * 200;
	
	if (glfwGetKey(m_pWindowController, GLFW_KEY_D))
	{
		MovementController::m_pCamera->SetYaw(-rate * 2);
	}
	if (glfwGetKey(m_pWindowController, GLFW_KEY_A))
	{
		MovementController::m_pCamera->SetYaw(rate * 2);
		
	}

	double xpos, ypos;
	glfwGetCursorPos(m_pWindowController, &xpos, &ypos);

	if (glfwGetMouseButton(m_pWindowController, GLFW_MOUSE_BUTTON_LEFT))
	{

		GLfloat xoffset = lastX - xpos;
		GLfloat yoffset = ypos - lastY;
		lastX = xpos;
		lastY = ypos;

		GLfloat sensitivity = 0.7;	// TODO make variable for sensitivity
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		m_pCamera->SetYaw(xoffset);
		m_pCamera->SetPitch(yoffset);
	}
	if (glfwGetMouseButton(m_pWindowController, GLFW_MOUSE_BUTTON_RIGHT))
	{

		GLfloat xoffset = lastX - xpos;
		GLfloat yoffset = ypos - lastY;
		lastX = xpos;
		lastY = ypos;

		GLfloat sensitivity = 0.7;	// TODO make variable for sensitivity
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		m_pCamera->SetYaw(xoffset);
		m_pCamera->SetPitch(yoffset);
		
	}
	

	lastX = xpos;
	lastY = ypos;
}

MovementController::~MovementController()
{
}
