#pragma once
class BaseGameLogic;
class EventManager;

class InfernalKernel
{


public:

	InfernalKernel();
	bool Init();
	~InfernalKernel();
	

	virtual BaseGameLogic *VCreateGameAndView() = 0;
	EventManager *m_pEventManager;

	BaseGameLogic* GetGameLogic(void) const { return m_pGame; }

protected:
	BaseGameLogic *m_pGame;
	virtual void VRegisterGameEvents(void) {}
private:
	void RegisterEngineEvents(void);

};

extern InfernalKernel *g_pApp;