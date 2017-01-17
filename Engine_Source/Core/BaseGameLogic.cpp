#include "Engine.h"
#include "BaseGameLogic.h"
#include "SHObject/ObjectFactory.h"
#include "EventSystem/Event.h"
#include"SHObject/Object3D.h"
BaseGameLogic::BaseGameLogic()
{
	m_LastActorId = 0;
	m_Lifetime = 0;
}

BaseGameLogic::~BaseGameLogic()
{
	for (auto it = m_objects.begin(); it != m_objects.end(); ++it)
		it->second->Destroy();
	m_objects.clear();

	delete m_pObjectFactory;
}

bool BaseGameLogic::Init(void)
{
	m_pObjectFactory = VCreateActorFactory();
	return true;
}

StrongObjectPtr BaseGameLogic::VCreateActor(const std::string &actorResource, const ObjectId serversActorId)
{
	if(m_pObjectFactory)
	{
		
		StrongObjectPtr pObject = m_pObjectFactory->CreateActor(serversActorId, actorResource.c_str());
		if (pObject)
			return pObject;
	}
	 
	return StrongObjectPtr();
}

void BaseGameLogic::VDestroyActor(const ObjectId actorId)
{
	std::shared_ptr<EvtData_Destroy_Actor> pEvent(INFERNAL_NEW EvtData_Destroy_Actor(actorId));
	IEventManager::Get()->VTriggerEvent(pEvent);

	auto findIt = m_objects.find(actorId);
	if (findIt != m_objects.end())
	{
		findIt->second->Destroy();
		m_objects.erase(findIt);
	}
}

WeakObjectPtr BaseGameLogic::VGetActor(const ObjectId actorId)
{
	ObjectMap::iterator findIt = m_objects.find(actorId);
	if (findIt != m_objects.end())
		return findIt->second;

	return WeakObjectPtr();
}

void BaseGameLogic::VModifyActor(const ObjectId actorId, tinyxml2::XMLElement *overrides)
{

}

std::string BaseGameLogic::GetActorXml(const ObjectId id)
{
	return std::string();
}

bool BaseGameLogic::VLoadGame(const char* levelResource)
{
	return true;
}

void BaseGameLogic::VOnUpdate(float time, float elapsedTime)
{

}

void BaseGameLogic::VChangeState(BaseGameState newState)
{

}



ObjectFactory* BaseGameLogic::VCreateActorFactory(void)
{
	return INFERNAL_NEW ObjectFactory;
}

void BaseGameLogic::MoveActorDelegate(IEventDataPtr pEventData)
{

}

void BaseGameLogic::RequestNewActorDelegate(IEventDataPtr pEventData)
{

}
void BaseGameLogic::RequestDestroyActorDelegate(IEventDataPtr pEventData)
{

}