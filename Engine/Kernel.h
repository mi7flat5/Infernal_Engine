
#ifndef KERNEL_H
#define KERNEL_H


class Kernel
{
	std::shared_ptr<GLFWwindow> SharedContext;
	GLFWwindow* pContext;
	std::shared_ptr<EventManager> m_pEventManager;
	std::shared_ptr<Scene> m_pScene;
	std::shared_ptr<CameraNode> m_pCamera;
	GLuint HEIGHT, WIDTH;
	std::shared_ptr<Scene> pScene;
	void init();
	void update();

public:

	
	Kernel();
	void runApp();
	~Kernel();

	std::shared_ptr<GLFWwindow> Kernel::getContext()const;
}; 





#endif // !KERNEL_H


