#pragma once
#include"Object3D.h"
class ObjectComponent
{
	friend class ObjectFactory;
	
protected:
	StrongObjectPtr m_pOwner;

public:
	
	
	virtual ~ObjectComponent() { m_pOwner.reset(); }
	virtual bool VInit(tinyxml2::XMLElement* pData) = 0;
	virtual void VPostInit(void) { }
	virtual void VUpdate(int deltaMs) { }
	virtual void VOnChanged(void) { }
	virtual ComponentId VGetId(void) const { return GetIdFromName(VGetName()); }
	virtual const char *VGetName() const = 0;
	static ComponentId GetIdFromName(const char* componentStr)
	{
		void* rawId = HashedString::hash_name(componentStr);
		return reinterpret_cast<ComponentId>(rawId);
	}

	virtual tinyxml2::XMLElement* VGenerateXml(void) = 0;
	WeakObjectPtr GetOwner()const { return WeakObjectPtr(m_pOwner); }
	ObjectId GetOwnerId()const {return	m_pOwner->GetId();	}
	
private:
	void SetOwner(StrongObjectPtr pOwner) { m_pOwner = pOwner; }

};

