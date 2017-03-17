

#include"..\Core\MovementController.hpp"
extern GLuint HEIGHT, WIDTH;
class Kernel : public InfernalKernel
{
	std::shared_ptr<GLFWwindow> SharedContext;
	GLFWwindow* pContext;

	std::shared_ptr<Scene> m_pScene;
	std::shared_ptr<CameraNode> m_pCamera;
	
	std::shared_ptr<Scene> pScene;
	std::shared_ptr<MovementController> m_pController;
	void initContext();
	void update();
	ObjectFactory maker;
	virtual BaseGameLogic *VCreateGameAndView() override { m_pGame = new BaseGameLogic; m_pGame->Init(); return m_pGame; }
public:

	
	Kernel();
	void runApp();
	~Kernel();

	GLFWwindow * Kernel::getContext()const;
	void LoadScene(std::string);
}; 








