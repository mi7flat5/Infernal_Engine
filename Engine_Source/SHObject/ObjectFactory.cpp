#include"Engine.h"
#include "ObjectFactory.h"
#include"RenderComponent.h"
#include"Object3D.h"
//#include"..\EventSystem\Event.h"
using namespace tinyxml2;
ObjectFactory::ObjectFactory()
{
	m_lastActorId = 0;
	m_componentFactory.Register<CubeMapRenderComponent>(ObjectComponent::GetIdFromName(CubeMapRenderComponent::g_Name));
	m_componentFactory.Register<MeshRenderComponent>(ObjectComponent::GetIdFromName(MeshRenderComponent::g_Name));
}


ObjectFactory::~ObjectFactory()
{
}
StrongObjectPtr ObjectFactory::CreateActor(ObjectId serversActorId,const char* resourcePath)
{
	XMLDocument doc;
	if (doc.LoadFile(resourcePath))
	{
		EDITOR_LOG("FileLoaded")
	}
	
	XMLElement* pRoot = doc.FirstChildElement();
	if (!pRoot)
	{
		EDITOR_LOG(std::string(std::string("No root element found, returning nullptr failed to load: ")+ std::string(resourcePath)).c_str());
		
		return StrongObjectPtr();
	}

	
	ObjectId nextObjectId = serversActorId;
	if (nextObjectId == INVALID_OBJECT_ID)
	{
		nextObjectId = GetNextActorId();
	}
	StrongObjectPtr pObject;
	
	pObject.reset(INFERNAL_NEW Object3D(nextObjectId));
	if (!pObject->Init(pRoot))
	{
		EDITOR_LOG("Failed to initialize object returning nullptr")
		return StrongObjectPtr();
	}
	
	//StrongObjectComponentPtr a = VCreateComponent(std::string("CubeMapRenderComponent"));
	for (XMLElement* pNode = pRoot->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
	{
		StrongObjectComponentPtr pComponent(VCreateComponent(pNode));
		if (pComponent)
		{
			pObject->AddComponent(pComponent);
			pComponent->SetOwner(pObject);
			pObject->PostInit();
		}
		else
		{
			return StrongObjectPtr();
		}
	}
	EDITOR_LOG("apparently successfully added object to scene")
	return pObject;
}

void ObjectFactory::ModifyActor(StrongObjectPtr pActor, tinyxml2::XMLElement * overrides)
{
}

StrongObjectComponentPtr ObjectFactory::VCreateComponent(tinyxml2::XMLElement * pData)
{
	const char* name = pData->Value();
	StrongObjectComponentPtr pComponent(m_componentFactory.Create(ObjectComponent::GetIdFromName(name)));

	if (pComponent)
	{
		if (!pComponent->VInit(pData))
		{
			EDITOR_LOG(std::string("Component failed to initialize: " + std::string(name)).c_str());
			return StrongObjectComponentPtr();
		}
	}
	else
	{
		EDITOR_LOG(std::string("Couldn't find ActorComponent named " + std::string(name)).c_str());
		return StrongObjectComponentPtr();  // fail
	}



	return pComponent;
}
StrongObjectComponentPtr ObjectFactory::VCreateComponent(StrongObjectPtr pObject)
{
	
	
	StrongObjectComponentPtr pComponent(m_componentFactory.Create(ObjectComponent::GetIdFromName("CubeMapRenderComponent")));
		
	
	return pComponent;
}
StrongObjectComponentPtr ObjectFactory::VCreateComponent(std::string ComponentName)
{


	StrongObjectComponentPtr pComponent(m_componentFactory.Create(ObjectComponent::GetIdFromName(ComponentName.c_str())));

	
	return pComponent;
}