#include"Engine.h"
#include "ObjectFactory.h"
#include"RenderComponent.h"
#include"Object3D.h"
#include"TransformComponent.h"
#include "SHObject/ObjectComponent.h"
#include"..\EventSystem\Event.h"
using namespace tinyxml2;
ObjectFactory::ObjectFactory()
{
	m_lastActorId = 0;

	m_componentFactory.Register<CubeMapRenderComponent>(ObjectComponent::GetIdFromName(CubeMapRenderComponent::g_Name));
	m_componentFactory.Register<MeshRenderComponent>(ObjectComponent::GetIdFromName(MeshRenderComponent::g_Name));
	m_componentFactory.Register<AlphaMeshRenderComponent>(ObjectComponent::GetIdFromName(AlphaMeshRenderComponent::g_Name));
	m_componentFactory.Register<TerrainRenderComponent>(ObjectComponent::GetIdFromName(TerrainRenderComponent::g_Name));
	m_componentFactory.Register<TransformComponent>(ObjectComponent::GetIdFromName(TransformComponent::g_Name));
}


ObjectFactory::~ObjectFactory()
{
}
void ObjectFactory::init()
{
	
}
StrongObjectPtr ObjectFactory::CreateActor(ObjectId serversActorId,const char* resourcePath)
{
	
	//LOG_TO_FILE("I.m at least in the function")
	ObjectId nextObjectId = serversActorId;
	if (nextObjectId == INVALID_OBJECT_ID)
	{
		nextObjectId = GetNextActorId();
	}

	StrongObjectPtr pObject;
	StrongObjectComponentPtr pComponent;
	XMLDocument doc;
	if (!doc.LoadFile(resourcePath))
	{
		
		EDITOR_LOG("FileLoaded")
	}
	//
	XMLElement* pRoot = doc.FirstChildElement();
	if (!pRoot)
	{
		EDITOR_LOG(std::string(std::string("No root element found, returning nullptr failed to load: ")+ std::string(resourcePath)).c_str());
		
		return StrongObjectPtr();
	}
	pObject.reset(new Object3D(nextObjectId));
	//
	//
	//
	
	if (!pObject->Init(pRoot))
	{
		EDITOR_LOG("Failed to initialize object returning nullptr")
		return StrongObjectPtr();
	}
	
	
	for (XMLElement* pNode = pRoot->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
	{
	
		 pComponent = std::shared_ptr<ObjectComponent>(VCreateComponent(pNode));
		if (pComponent)
		{
			pComponent->SetOwner(pObject);
			pObject->AddComponent(pComponent);
			
			pObject->PostInit();
		}
		else
		{
			return StrongObjectPtr();
		}
	}
	doc.Clear();
	
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
		EDITOR_LOG(std::string("Component Loaded: " + std::string(name)).c_str());
	}
	else
	{
		EDITOR_LOG(std::string("Couldn't find Component named " + std::string(name)).c_str());
		return StrongObjectComponentPtr();  // fail
	}



	return pComponent;
}
