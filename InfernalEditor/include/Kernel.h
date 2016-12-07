
#ifndef KERNEL_H
#define KERNEL_H
#include"MovementController.hpp"
extern GLuint HEIGHT, WIDTH;
class Kernel
{
	std::shared_ptr<GLFWwindow> SharedContext;
	GLFWwindow* pContext;
	std::shared_ptr<EventManager> m_pEventManager;
	std::shared_ptr<Scene> m_pScene;
	std::shared_ptr<CameraNode> m_pCamera;
	
	std::shared_ptr<Scene> pScene;
	std::shared_ptr<MovementController> m_pController;
	void init();
	void update();

public:

	
	Kernel();
	void runApp();
	~Kernel();

	GLFWwindow * Kernel::getContext()const;
}; 





#endif // !KERNEL_H


