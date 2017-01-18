#pragma once
class ObjectFactory
{
	ObjectId m_lastActorId;
	ObjectId GetNextActorId(void) { ++m_lastActorId; return m_lastActorId; }
	void ModifyActor(StrongObjectPtr pObject, tinyxml2::XMLElement* overrides);
	//May return NULL
	virtual StrongObjectComponentPtr VCreateComponent(tinyxml2::XMLElement* pData);
protected:
	GenericObjectFactory<ObjectComponent, ComponentId> m_componentFactory;
public:
	ObjectFactory();
	~ObjectFactory();
	void init();
	StrongObjectPtr CreateActor(ObjectId serversActorId,const char* resourcePath);
};

