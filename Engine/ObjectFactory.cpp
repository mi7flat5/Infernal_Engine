#include"Engine.h"
#include "ObjectFactory.h"
#include"RenderComponent.h"
#include"Object3D.h"

ObjectFactory::ObjectFactory()
{
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
	std::cout << "\nObject created in factory.";
	StrongObjectComponentPtr a = VCreateComponent(pObject);
	a->SetOwner(pObject);
	pObject->AddComponent(a);
	
	
	
	
	
	std::cout<<"\nsize "<<pObject->GetComponents()->size();
	

	pObject->PostInit();
	
	return pObject;
}

void ObjectFactory::ModifyActor(StrongObjectPtr pActor, tinyxml2::XMLElement * overrides)
{
}

StrongObjectComponentPtr ObjectFactory::VCreateComponent(tinyxml2::XMLElement * pData)
{
	StrongObjectComponentPtr pComponent(m_componentFactory.Create(ObjectComponent::GetIdFromName("MeshRenderComponent")));
	return pComponent;
}
StrongObjectComponentPtr ObjectFactory::VCreateComponent(StrongObjectPtr pObject)
{
	
	
	StrongObjectComponentPtr pComponent(m_componentFactory.Create(ObjectComponent::GetIdFromName("MeshRenderComponent")));
		
	std::cout<<"\nMesh render component added";
	return pComponent;
}