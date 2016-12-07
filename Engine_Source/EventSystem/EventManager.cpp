#include"Engine.h"
#include "EventManager.h"


static IEventManager* g_pEventMgr = NULL;
GenericObjectFactory<IEventData, EventType> g_eventFactory;

//GCC_MEMORY_WATCHER_DEFINITION(IEventData);

IEventManager* IEventManager::Get(void)
{
	assert(g_pEventMgr);
	return g_pEventMgr;
}

IEventManager::IEventManager(const char* pName, bool setAsGlobal)
{
	if (setAsGlobal)
	{
		if (g_pEventMgr)
		{
			std::cout<<"Attempting to create two global event managers! The old one will be destroyed and overwritten with this one."<<'\n';
			delete g_pEventMgr;
		}

		g_pEventMgr = this;
	}
}

IEventManager::~IEventManager(void)
{
	if (g_pEventMgr == this)
		g_pEventMgr = NULL;
}

