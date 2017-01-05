#include "Engine.h"
#include "Geometry.h"
//#include"..//3DRender//GraphicsDebug.h"
#include"..//3DRender/SceneNode.h"
mat4 InvTrps(mat4 m) { return glm::transpose(glm::inverse(m)); }
mat4 RmvTrans(mat4 m) {return mat4(mat3(m));}
Geometry::Geometry()
{
}


Geometry::~Geometry()
{
}
 void Plane::PlaneTransform(mat4 InvMVmat) 
 {
	 vec4 planevec(a, b, c, d);
	 d = glm::dot(m_Normal,vec3(InvMVmat[3]));
	 /* a = planevec.x;
	  b = planevec.y;
	  c = planevec.z;*/
	// d = planevec.w;
	
	 return ;
 }



Frustum::Frustum()
{
	m_Fov = pi / 4.0f;		// default field of view is 90 degrees
	m_Aspect = 1.0f;			// default aspect ratio is 1:1
	m_Near = 1.0f;				// default near clip plane is 1m away from the camera
	m_Far = 1000.0f;
}

bool Frustum::Inside(const BVSphere & sphere) const
{
	
		for (int i = 2; i < NumPlanes; ++i)
		{
			if (!m_Planes[i].Inside(sphere))
				return false;
		}
		
	
	// otherwise we are fully in view
	return(true);
	return m_Planes[Bottom].Inside(sphere);
}
void Frustum::ApplyTransform(mat4 InvMVmat) 
{
	for (int i = 0; i < NumPlanes; ++i)
	{
		m_Planes[i].PlaneTransform(InvMVmat);
	}
}
vec3 toworld(vec3 a, mat4 b)
{
	return vec3(mat4()*vec4(a,1));
}
void Frustum::Init(const float fov, const float aspect, const float nearClip, const float farClip)
{
	m_Fov = fov;
	m_Aspect = aspect;
	m_Near = nearClip;
	m_Far = farClip;
	mat4 proj;// = Transform::translate(0, -15, 0);
	vec3 right(1, 0, 0);

	float tanFovOver2 = (float)tan(m_Fov / 2.0f);
	vec3 nearRight = (m_Near * tanFovOver2)  *m_Aspect* right;
	vec3 farRight = (m_Far * tanFovOver2)  *m_Aspect* right;
	vec3 nearUp = (m_Near * tanFovOver2)*m_Aspect* g_Up;
	vec3 farUp = (m_Far * tanFovOver2)  *m_Aspect* g_Up;
	vec3 forward(0, 0, 1);
	
	m_NearClip[0] = toworld((m_Near *forward) - nearRight + nearUp,proj);
	m_NearClip[1] = toworld((m_Near * forward) + nearRight + nearUp, proj);
	m_NearClip[2] = toworld((m_Near * forward) + nearRight - nearUp, proj);
	m_NearClip[3] = toworld((m_Near * forward) - nearRight - nearUp, proj);

	m_FarClip[0] = toworld((m_Far * forward) - farRight + farUp, proj);
	m_FarClip[1] = toworld((m_Far * forward) + farRight + farUp, proj);
	m_FarClip[2] = toworld((m_Far * forward) + farRight - farUp, proj);
	m_FarClip[3] = toworld((m_Far * forward) - farRight - farUp, proj);

	vec3 origin(0,0,0);
	m_Planes[Near].Init(m_NearClip[0], m_NearClip[1], m_NearClip[2]);
	m_Planes[Far].Init(m_FarClip[2], m_FarClip[1], m_FarClip[0]);
	m_Planes[Top].Init(origin, m_FarClip[0], m_FarClip[1]);
	m_Planes[Bottom].Init(origin, m_FarClip[2], m_FarClip[3]);
	m_Planes[Right].Init(origin, m_FarClip[1], m_FarClip[2]);
	m_Planes[Left].Init(origin, m_FarClip[3], m_FarClip[0]);
	m_Fov = fov;
	m_Aspect = aspect;
	m_Near = nearClip;
	m_Far = farClip;




	//VECCONSOLEOUT(vec3(m_FarClip[1]), "\n ")
}
void Frustum::render() {}
void Frustum::Init(const float fov, const float aspect, const float nearClip, const float farClip, CameraNode* cam,mat4 InMat)
{

	m_Fov = fov;
	m_Aspect = aspect;
	m_Near = nearClip;
	m_Far = .3;



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
	vec3 Origin(0,0,0);
	//VECCONSOLEOUT(vec3(Origin), "\n ")
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

	//worldVerts.push_back(m_FarClip[1]);
	//worldVerts.push_back(m_FarClip[0]);
	//worldVerts.push_back(m_FarClip[3]);
	//worldVerts.push_back(m_FarClip[2]);
	
	//right
	//worldVerts.push_back(Origin);
	//worldVerts.push_back(m_FarClip[1]);
	//worldVerts.push_back(m_FarClip[2]);
	//worldVerts.push_back(Origin);

	//////top
	//worldVerts.push_back(Origin);
	//worldVerts.push_back(m_FarClip[0]);
	//worldVerts.push_back(m_FarClip[1]);
	//worldVerts.push_back(Origin);
	////
	////left
	//worldVerts.push_back(Origin);
	//worldVerts.push_back(m_FarClip[3]);
	//worldVerts.push_back(m_FarClip[0]);
	//worldVerts.push_back(Origin);

	////bottom
	//worldVerts.push_back(Origin);
	//worldVerts.push_back(m_FarClip[2]);
	//worldVerts.push_back(m_FarClip[3]);
	//worldVerts.push_back(Origin);

	//dbg = new GraphicsDebug(worldVerts, dbgType::LINE);
}

void Frustum::Render()
{
}
