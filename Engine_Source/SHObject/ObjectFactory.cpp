#include"Engine.h"
#include "ObjectFactory.h"
#include"RenderComponent.h"
#include"Object3D.h"

ObjectFactory::ObjectFactory()
{
	m_lastActorId = 0;
	m_componentFactory.Register<CubeMapRenderComponent>(ObjectComponent::GetIdFromName(CubeMapRenderComponent::g_Name));
	m_componentFactory.Register<MeshRenderComponent>(ObjectComponent::GetIdFromName(MeshRenderComponent::g_Name));
}


ObjectFactory::~ObjectFactory()
{
}
StrongObjectPtr ObjectFactory::CreateActor(ObjectId serversActorId)
{
	ObjectId nextObjectId = serversActorId;
	if (nextObjectId == INVALID_OBJECT_ID)
	{
		nextObjectId = GetNextActorId();
	}
	StrongObjectPtr pObject;
	
	pObject.reset(INFERNAL_NEW Object3D(nextObjectId));
	if (!pObject)
		system("pause");
	
	StrongObjectComponentPtr a = VCreateComponent(std::string("CubeMapRenderComponent"));
	

	a->SetOwner(pObject);
	

	pObject->AddComponent(a);
	
	
	pObject->PostInit();
	

	ObjectId nextObjectId2 = serversActorId;
	if (nextObjectId2 == INVALID_OBJECT_ID)
	{
		nextObjectId2 = GetNextActorId();
	}
	StrongObjectPtr pObject2;

	pObject2.reset(INFERNAL_NEW Object3D(nextObjectId2));
	if (!pObject2)
		system("pause");
	
	StrongObjectComponentPtr a2 = VCreateComponent(std::string("MeshRenderComponent"));


	a2->SetOwner(pObject2);


	pObject2->AddComponent(a2);


	pObject2->PostInit();
	return pObject2;
}

void ObjectFactory::ModifyActor(StrongObjectPtr pActor, tinyxml2::XMLElement * overrides)
{
}

StrongObjectComponentPtr ObjectFactory::VCreateComponent(tinyxml2::XMLElement * pData)
{
	StrongObjectComponentPtr pComponent(m_componentFactory.Create(ObjectComponent::GetIdFromName("CubeMapRenderComponent")));
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