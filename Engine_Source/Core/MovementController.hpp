#pragma once
//extern GLdouble g_DeltaTime;

class MovementController
{
	GLFWwindow* m_pWindowController;
	std::shared_ptr<CameraNode> m_pCamera;
	
	GLfloat lastX, lastY, lastFrame, rate, g_DeltaTime;
public:
	static void Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset);
	static void Key_Callback(GLFWwindow*, int, int, int, int);
	MovementController();
	MovementController(GLFWwindow * InWin,std::shared_ptr<CameraNode> InCam);

	void UpdateControls();

	~MovementController();
};

