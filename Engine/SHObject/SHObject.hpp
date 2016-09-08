#pragma once 
#include<string>
#include<map>
#include"tinyxml2.h"
#include"../Core/interfaces.h"

typedef std::string ActorType;

class SHObject
{
	friend class SHObjectFactory;

public:

	typedef std::map<ComponentId, StrongObjectComponentPtr> ObjectComponents;

private:
	ObjectId m_id;					// unique id for the object, made by object factory
	ObjectComponents m_components;	// all components this actor has
	ActorType m_type;				//this should be used to chose renderer

	std::string m_resource;		//file path for xml	

public:
	explicit SHObject(ObjectId id);
	~SHObject(void);

	bool Init(tinyxml2::XMLElement* pData);
	void PostInit(void);
	void Destroy(void);
	void Update(int deltaMs);



	// accessors
	ObjectId GetId(void) const { return m_id; }
	ActorType GetType(void) const { return m_type; }

	// template function for retrieving components
	template <class ComponentType>
	weak_ptr<ComponentType> GetComponent(ComponentId id)
	{
		ActorComponents::iterator findIt = m_components.find(id);
		if (findIt != m_components.end())
		{
			StrongActorComponentPtr pBase(findIt->second);
			shared_ptr<ComponentType> pSub(static_pointer_cast<ComponentType>(pBase));  // cast to subclass version of the pointer
			weak_ptr<ComponentType> pWeakSub(pSub);  // convert strong pointer to weak pointer
			return pWeakSub;  // return the weak pointer
		}
		else
		{
			return weak_ptr<ComponentType>();
		}
	}

	template <class ComponentType>
	weak_ptr<ComponentType> GetComponent(const char *name)
	{
		ComponentId id = ActorComponent::GetIdFromName(name);
		ActorComponents::iterator findIt = m_components.find(id);
		if (findIt != m_components.end())
		{
			StrongActorComponentPtr pBase(findIt->second);
			shared_ptr<ComponentType> pSub(static_pointer_cast<ComponentType>(pBase));  // cast to subclass version of the pointer
			weak_ptr<ComponentType> pWeakSub(pSub);  // convert strong pointer to weak pointer
			return pWeakSub;  // return the weak pointer
		}
		else
		{
			return weak_ptr<ComponentType>();
		}
	}

	const ObjectComponents* GetComponents() { return &m_components; }

	void AddComponent(StrongObjectComponentPtr pComponent);
};