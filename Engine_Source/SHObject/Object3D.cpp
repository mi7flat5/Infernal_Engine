#include"Engine.h"
#include "Object3D.h"
#include"ObjectComponent.h"


Object3D::Object3D(ObjectId id)
{
	m_Id = id;
}


Object3D::~Object3D()
{
}

bool Object3D::Init(tinyxml2::XMLElement * pData)
{
	m_Type = pData->Attribute("type"); 
	m_resource = pData->Attribute("resource");
	return true;
}

void Object3D::PostInit(void)
{
	for (ObjectComponents::iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		it->second->VPostInit();
	}
}



void Object3D::Update(int deltaMs)
{
}

void Object3D::AddComponent(StrongObjectComponentPtr pComponent)
{
	std::pair<ObjectComponents::iterator, bool> success = m_components.insert(std::make_pair(pComponent->VGetId(), pComponent));
	
}
