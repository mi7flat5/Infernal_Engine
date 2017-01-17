#include"Engine.h"
#include"InfernalKernel.h"
#include"Core\BaseGameLogic.h"

InfernalKernel *g_pApp = NULL;

InfernalKernel::InfernalKernel()
{
	g_pApp = this;
	m_pGame = nullptr;

}
bool InfernalKernel::Init() 
{
	m_pEventManager = INFERNAL_NEW EventManager("Infernal Event Mgr", true);
	if (!m_pEventManager)
	{
		LOG_TO_FILE("Failed to create EventManager.");
		return false;
	}
}
InfernalKernel::~InfernalKernel()
{

}

void InfernalKernel::RegisterEngineEvents(void)
{

}

