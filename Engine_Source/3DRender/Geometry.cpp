#include "Engine.h"
#include "Geometry.h"
#include"..//3DRender//GraphicsDebug.h"
#include"..//3DRender/SceneNode.h"
mat4 InvTrps(mat4 m) { return glm::transpose(glm::inverse(m)); }
mat4 RmvTrans(mat4 m) {return mat4(mat3(m));}
Geometry::Geometry()
{
}
Geometry::~Geometry()
{
}
Frustum::Frustum()
{
	m_Fov = 90 * pi / 180;//glm::radians(90);		// default field of view is 90 degrees
	m_Aspect = WIDTH/HEIGHT;			// default aspect ratio is 1:1
	m_Near = 0.10f;				// default near clip plane is 1m away from the camera
	m_Far = 1800.0f;
}

bool Frustum::Inside(const BVSphere & sphere) const
{
		for (int i = 2; i < NumPlanes; ++i)
		{
			if (!m_Planes[i].Inside(sphere))
				return false;
		}
	return(true);
}


void Frustum::Init(const float fov, const float aspect, const float nearClip, const float farClip)
{
	m_Fov = fov;
	m_Aspect = aspect;
	m_Near = nearClip;
	m_Far = farClip;

	vec3 right(1, 0, 0);

	float tanFovOver2 = (float)tan(m_Fov / 2.0f);
	vec3 nearRight = (m_Near * tanFovOver2)  *m_Aspect* right;
	vec3 farRight = (m_Far * tanFovOver2)  *m_Aspect* right;
	vec3 nearUp = (m_Near * tanFovOver2)*m_Aspect* g_Up;
	vec3 farUp = (m_Far * tanFovOver2)  *m_Aspect* g_Up;
	vec3 forward(0, 0, 1);
	
	m_NearClip[0] = (m_Near *forward) - nearRight + nearUp;
	m_NearClip[1] = (m_Near * forward) + nearRight + nearUp;
	m_NearClip[2] = (m_Near * forward) + nearRight - nearUp;
	m_NearClip[3] = (m_Near * forward) - nearRight - nearUp;

	m_FarClip[0] = (m_Far * forward) - farRight + farUp;
	m_FarClip[1] = (m_Far * forward) + farRight + farUp;
	m_FarClip[2] = (m_Far * forward) + farRight - farUp;
	m_FarClip[3] = (m_Far * forward) - farRight - farUp;

	vec3 origin(0,0,0);
	m_Planes[Near].Init(m_NearClip[0], m_NearClip[1], m_NearClip[2]);
	m_Planes[Far].Init(m_FarClip[2], m_FarClip[1], m_FarClip[0]);
	m_Planes[Top].Init(origin, m_FarClip[0], m_FarClip[1]);
	m_Planes[Bottom].Init(origin, m_FarClip[2], m_FarClip[3]);
	m_Planes[Right].Init(origin, m_FarClip[1], m_FarClip[2]);
	m_Planes[Left].Init(origin, m_FarClip[3], m_FarClip[0]);
	
}

void Frustum::Render()
{
	if (!dbg)
		RenderInit();
	dbg->Draw(mat4(), mat4(), mat4());
}

void Frustum::RenderInit()
{
	vec3 right = vec3(1, 0, 0);

	float tanFovOver2 = (float)tan(m_Fov / 2.0f);
	vec3 nearRight = (m_Near * tanFovOver2)  *m_Aspect* right;
	vec3 farRight = (m_Far * tanFovOver2)  *m_Aspect* right;
	vec3 nearUp = (m_Near * tanFovOver2)*m_Aspect*  g_Up;
	vec3 farUp = (m_Far * tanFovOver2)  *m_Aspect* g_Up;
	vec3 forward(0, 0, -1);
	m_NearClip[0] = (m_Near *forward) - nearRight + nearUp;
	m_NearClip[1] = (m_Near * forward) + nearRight + nearUp;
	m_NearClip[2] = (m_Near * forward) + nearRight - nearUp;
	m_NearClip[3] = (m_Near * forward) - nearRight - nearUp;

	m_FarClip[0] = (m_Far * forward) - farRight + farUp;
	m_FarClip[1] = (m_Far * forward) + farRight + farUp;
	m_FarClip[2] = (m_Far * forward) + farRight - farUp;
	m_FarClip[3] = (m_Far * forward) - farRight - farUp;
	vec3 Origin(0, 0, 0);

	worldVerts.push_back(Origin);
	worldVerts.push_back(m_NearClip[1]);

	worldVerts.push_back(Origin);
	worldVerts.push_back(m_NearClip[2]);

	worldVerts.push_back(Origin);
	worldVerts.push_back(m_NearClip[3]);

	worldVerts.push_back(Origin);
	worldVerts.push_back(m_NearClip[0]);

	worldVerts.push_back(m_NearClip[0]);
	worldVerts.push_back(m_NearClip[1]);

	worldVerts.push_back(m_NearClip[1]);
	worldVerts.push_back(m_NearClip[2]);

	worldVerts.push_back(m_NearClip[2]);
	worldVerts.push_back(m_NearClip[3]);

	worldVerts.push_back(m_NearClip[3]);
	worldVerts.push_back(m_NearClip[0]);

	worldVerts.push_back(Origin);
	worldVerts.push_back(m_NearClip[1]);

	worldVerts.push_back(Origin);
	worldVerts.push_back(m_NearClip[2]);

	worldVerts.push_back(Origin);
	worldVerts.push_back(m_NearClip[3]);

	worldVerts.push_back(Origin);
	worldVerts.push_back(m_NearClip[0]);

	worldVerts.push_back(m_NearClip[0]);
	worldVerts.push_back(m_NearClip[1]);

	worldVerts.push_back(m_NearClip[1]);
	worldVerts.push_back(m_NearClip[2]);

	worldVerts.push_back(m_NearClip[2]);
	worldVerts.push_back(m_NearClip[3]);

	worldVerts.push_back(m_NearClip[3]);
	worldVerts.push_back(m_NearClip[0]);


	worldVerts.push_back(Origin);
	worldVerts.push_back(m_FarClip[1]);

	worldVerts.push_back(Origin);
	worldVerts.push_back(m_FarClip[2]);

	worldVerts.push_back(Origin);
	worldVerts.push_back(m_FarClip[3]);

	worldVerts.push_back(Origin);
	worldVerts.push_back(m_FarClip[0]);

	worldVerts.push_back(m_FarClip[0]);
	worldVerts.push_back(m_FarClip[1]);

	worldVerts.push_back(m_FarClip[1]);
	worldVerts.push_back(m_FarClip[2]);

	worldVerts.push_back(m_FarClip[2]);
	worldVerts.push_back(m_FarClip[3]);

	worldVerts.push_back(m_FarClip[3]);
	worldVerts.push_back(m_FarClip[0]);

	dbg.reset(INFERNAL_NEW GraphicsDebug(worldVerts, dbgType::LINE));
}
