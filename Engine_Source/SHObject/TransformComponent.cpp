#include "Engine.h"
#include "TransformComponent.h"


const char* TransformComponent::g_Name = "TransformComponent";

bool TransformComponent::VInit(tinyxml2::XMLElement* pData)
{
	
	tinyxml2::XMLElement* pPositionElement = pData->FirstChildElement("Position");
	if (pPositionElement)
	{
		double x = 0;
		double y = 0;
		double z = 0;
		pPositionElement->QueryDoubleAttribute("x", &x);
		pPositionElement->QueryDoubleAttribute("y", &y);
		pPositionElement->QueryDoubleAttribute("z", &z);
		m_Position = vec3(x, y, z);
		
	}
	else
	{
		return false;
	}
	tinyxml2::XMLElement* pRotationElement = pData->FirstChildElement("Rotation");
	if (pRotationElement)
	{
		double x = 0;
		double y = 0;
		double z = 0;
		pRotationElement->QueryDoubleAttribute("pitch", &x);
		pRotationElement->QueryDoubleAttribute("yaw", &y);
		pRotationElement->QueryDoubleAttribute("roll", &z);
		m_RotDegrees = vec3(x, y, z);

	}
	else
	{
		return false;
	}
	tinyxml2::XMLElement* pScaleElement = pData->FirstChildElement("Scale");
	if (pScaleElement)
	{
		double x = 0;
		double y = 0;
		double z = 0;
		pScaleElement->QueryDoubleAttribute("x", &x);
		pScaleElement->QueryDoubleAttribute("y", &y);
		pScaleElement->QueryDoubleAttribute("z", &z);
		m_Scale = vec3(x, y, z);

	}
	else
	{
		return false;
	}
	BuildTransform();
	return true;
}
void TransformComponent::BuildTransform() 
{

	mat4 PosMat = Transform::translate(m_Position.x, m_Position.y, m_Position.z);
	mat4 RotMAt = Transform::RotateMat4(m_RotDegrees.x, vec3(1, 0, 0))* Transform::RotateMat4(m_RotDegrees.y, vec3(0, 1, 0))* Transform::RotateMat4(m_RotDegrees.z, vec3(0, 0, 1));
	mat4 ScaleMat = Transform::scale(m_Scale.x, m_Scale.y, m_Scale.z);
	m_Transform = PosMat*RotMAt*ScaleMat;

}