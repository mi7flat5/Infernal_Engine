#pragma once
typedef std::string ObjectType;
typedef std::map<ComponentId, StrongObjectComponentPtr> ObjectComponents;
class Object3D
{
	friend class ObjectFactory;
public:
	
private:
	ObjectId m_Id;
	std::string m_resource;
	ObjectType m_Type;
	ObjectComponents m_components;
public:
	
	
	explicit Object3D(ObjectId id);
	~Object3D();

	bool Init(tinyxml2::XMLElement* pData);
	void PostInit(void);
	void Destroy(void) { m_components.clear(); }
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
		ComponentId id = ObjectComponent::GetIdFromName(name);
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

