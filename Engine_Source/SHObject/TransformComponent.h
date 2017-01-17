#pragma once
#include"ObjectComponent.h"
     
class TransformComponent : public ObjectComponent
{
	mat4 m_Transform;
	vec3 m_Scale, m_RotDegrees, m_Position;
	void BuildTransform();
public:
	TransformComponent(void) : m_Transform(mat4(1.0f)) { }


	mat4 GetTransform(void) const { return m_Transform; }
	void SetTransform(const mat4& newTransform) { m_Transform = newTransform; }
	vec3 GetPosition(void) const { return vec3(m_Transform[3]); }
	void SetPosition(const vec3& pos) 
	{
		m_Transform = m_Transform * Transform::translate(pos.x,pos.y,pos.z);
		m_Position = pos;
	}
	vec3 GetVecScale() { return m_Scale; }
	static const char * g_Name;
	virtual bool VInit(tinyxml2::XMLElement* pData)override;
	
	virtual const char *VGetName() const override { return g_Name; }
	virtual tinyxml2::XMLElement* VGenerateXml(void)override { return nullptr; };
};