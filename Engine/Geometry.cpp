#include "Engine.h"
#include "Geometry.h"


Geometry::Geometry()
{
}


Geometry::~Geometry()
{
}

bool Frustum::Inside(const Sphere & sphere) const
{
	for (int i = 0; i < NumPlanes; ++i)
	{
		if (!m_Planes[i].Inside(sphere))
			return false;
	}

	// otherwise we are fully in view
	return(true);
}
void Frustum::Init(const float fov, const float aspect, const float nearClip, const float farClip)
{
	m_Fov = fov;
	m_Aspect = aspect;
	m_Near = nearClip;
	m_Far = farClip;

	float tanFovOver2 = (float)tan(m_Fov / 2.0f);
	vec3 nearRight = (m_Near * tanFovOver2) * m_Aspect * g_Right;
	vec3 farRight = (m_Far * tanFovOver2) * m_Aspect * g_Right;
	vec3 nearUp = (m_Near * tanFovOver2) * g_Up;
	vec3 farUp = (m_Far * tanFovOver2)  * g_Up;
}