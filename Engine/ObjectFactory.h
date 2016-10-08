#pragma once
class ObjectFactory
{
	ObjectId m_lastActorId;
	ObjectId GetNextActorId(void) { ++m_lastActorId; return m_lastActorId; }
protected:
	GenericObjectFactory<ObjectComponent, ComponentId> m_componentFactory;
public:
	ObjectFactory();
	~ObjectFactory();

	StrongObjectPtr CreateActor(ObjectId serversActorId);



	void ModifyActor(StrongObjectPtr pObject, tinyxml2::XMLElement* overrides);

	StrongObjectComponentPtr VCreateComponent(StrongObjectPtr pObject);

	StrongObjectComponentPtr VCreateComponent(std::string ComponentName);

	//May return NULL
	virtual StrongObjectComponentPtr VCreateComponent(tinyxml2::XMLElement* pData);
};

