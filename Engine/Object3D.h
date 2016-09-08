#pragma once

class Object3D
{
	friend class ObjectFactory;
public:
	typedef std::map<ComponentId, StrongObjectComponentPtr> ObjectComponents;
private:
	ObjectId m_Id;
	ObjectComponents m_components;
public:
	
	
	explicit Object3D(ObjectId id);
	~Object3D();

	bool Init(tinyxml2::XMLElement* pData);
	void PostInit(void);
	void Destroy(void);
	void Update(int deltaMs);

	ObjectId GetId() const { return m_Id; }

	const ObjectComponents* GetComponents() { return &m_components; }

	void AddComponent(StrongObjectComponentPtr pComponent);

	 //template function for retrieving components
	template <class ComponentType>
	std::weak_ptr<ComponentType> GetComponent(ComponentId id)
	{
		ObjectComponents::iterator findIt = m_components.find(id);
		if (findIt != m_components.end())
		{
			StrongObjectComponentPtr pBase(findIt->second);
			std::shared_ptr<ComponentType> pSub(std::static_pointer_cast<ComponentType>(pBase));  // cast to subclass version of the pointer
			std::weak_ptr<ComponentType> pWeakSub(pSub);  // convert strong pointer to weak pointer
			return pWeakSub;  // return the weak pointer
		}
		else
		{
			return std::weak_ptr<ComponentType>();
		}
	}

	template <class ComponentType>
	std::weak_ptr<ComponentType> GetComponent(const char *name)
	{
		ComponentId id = ActorComponent::GetIdFromName(name);
		ObjectComponents::iterator findIt = m_components.find(id);
		if (findIt != m_components.end())
		{
			StrongObjectComponentPtr pBase(findIt->second);
			std::shared_ptr<ComponentType> pSub(std::static_pointer_cast<ComponentType>(pBase));  // cast to subclass version of the pointer
			std::weak_ptr<ComponentType> pWeakSub(pSub);  // convert strong pointer to weak pointer
			return pWeakSub;  // return the weak pointer
		}
		else
		{
			return std::weak_ptr<ComponentType>();
		}
	}


};

