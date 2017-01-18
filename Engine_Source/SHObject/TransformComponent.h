#pragma once
#include"ObjectComponent.h"
     
class TransformComponent : public ObjectComponent
{
	mat4 m_Transform;
	vec3 m_Scale, m_RotDegrees, m_Position;
	
public:
	TransformComponent(void) : m_Transform(mat4(1.0f)) { }
	void BuildTransform();

	mat4 GetTransform(void) const { return m_Transform; }
	void SetTransform(const mat4& newTransform) { m_Transform = newTransform; }
	void SetVecPosition(vec3 inPos) { m_Position = inPos; }
	void SetVecRotation(vec3 inRot) { m_RotDegrees = inRot; }
	void SetVecScaler(vec3 inScale) { m_Scale = inScale; }
	vec3 GetPosition(void) const { return vec3(m_Transform[3]); }
	vec3 GetVecScale() const{return m_Scale; }
	vec3 GetVecRotation()const {return m_RotDegrees;}
	static const char * g_Name;
	virtual bool VInit(tinyxml2::XMLElement* pData)override;
	
	virtual const char *VGetName() const override { return g_Name; }
	virtual tinyxml2::XMLElement* VGenerateXml(void)override { return nullptr; };
};