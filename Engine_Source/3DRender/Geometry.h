#pragma once
extern vec3 g_Up;
extern vec3 g_Right;
extern vec3 g_Forward;

extern vec4 g_Up4;
extern vec4 g_Right4;
extern vec4 g_Forward4;



class Geometry
{
public:
	Geometry();
	~Geometry();
};
class AABB {
	vec3 min;
	vec3 max;
	std::vector<vec3> axis;
public:
	AABB(const std::vector<vec3>& Verts) {
		axis.push_back(vec3(-1, 0, 0));
		axis.push_back(vec3(1, 0, 0));
		axis.push_back(vec3(0, -1, 0));
		axis.push_back(vec3(0, 1, 0));
		axis.push_back(vec3(0, 0, -1));
		axis.push_back(vec3(0, 0, 1));
		CalcAABB(Verts);
	}
	void CalcAABB(const std::vector<vec3>& Verts)
	{
		for (auto& dir : axis) {
			CalcExtremePoints(Verts, dir);
		}
	}
	void CalcExtremePoints(const std::vector<vec3>& Verts,vec3 Direction)
	{
		float minProj = FLT_MAX, maxProj = -FLT_MAX;
		for (auto& point : Verts)
		{
			float proj = glm::dot(point,Direction);
			if (proj < minProj) 
			{
				minProj = proj;
				min = point;
			}
			if (proj > maxProj) 
			{
				maxProj = proj;
				max = point;
			}
		}
	}
	
};
class BVSphere {
	

	
	void MostSeperatedPoints(const std::vector<vec3>& Verts, vec3& MinExtent, vec3& MAxExtent)
	{
		int minx = 0, miny = 0, minz = 0, maxx = 0, maxy = 0, maxz = 0;
		for (int i = 1;i < Verts.size(); ++i)
		{
			if (Verts[i].x < Verts[minx].x) minx = i;
			if (Verts[i].x > Verts[maxx].x) maxx = i;

			if (Verts[i].y < Verts[miny].y) miny = i;
			if (Verts[i].y > Verts[maxy].y) maxy = i;

			if (Verts[i].z < Verts[minz].z) minz = i;
			if (Verts[i].z > Verts[maxz].z) maxz = i;

		}

		float DistXSqr = glm::dot(Verts[maxx] - Verts[minx], Verts[maxx] - Verts[minx]);
		float DistYSqr = glm::dot(Verts[maxy] - Verts[miny], Verts[maxy] - Verts[miny]);
		float DistZSqr = glm::dot(Verts[maxz] - Verts[minz], Verts[maxz] - Verts[minz]);

		MinExtent = Verts[minx];
		MAxExtent = Verts[maxx];

		if (DistYSqr > DistXSqr && DistYSqr > DistZSqr)
		{
			MinExtent = Verts[miny];
			MAxExtent = Verts[maxy];
		}
		if (DistZSqr > DistXSqr && DistZSqr > DistYSqr)
		{
			MinExtent = Verts[minz];
			MAxExtent = Verts[maxz];
		}

	}
public:
	BVSphere() {}
	vec3 position;
	GLfloat radius;
	void SphereFromDistantPoints(const std::vector<vec3>& Verts)
	{
		vec3 minEx, maxEx;
		MostSeperatedPoints(Verts, minEx, maxEx);
		position = (minEx + maxEx)*0.5f;
		radius = glm::dot(maxEx-position, maxEx - position);
		radius = sqrt(radius);
	
	}
	

	
};
class Plane 
{
	
	vec3 m_Normal, m_EdgeAB, m_EdgeAC;
	GLfloat Project(const vec3 & spherePos, const Plane * p) const;
	bool const Collision(const BVSphere & s, const Plane* p)const;
public:
	
	Plane() {}
	
	inline void Plane::Normalize();

	// normal faces away from you if you send in verts in counter clockwise order....
	inline void Init(const vec3 &p0, const vec3 &p1, const vec3 &p2);
	bool Inside(const BVSphere &sphere) const;
	
	//bool Inside(const vec3 &point) const;
	vec3 GetNorm()const { return glm::normalize(m_Normal); }
	float ScalerNorm() const {
		return sqrt(a*a + b*b + c*c);
	}
	
	GLfloat a, b, c, d;
private:
	bool TestSphereHalfSpace(BVSphere s) const;
};
inline void Plane::Init(const vec3 &p0, const vec3 &p1, const vec3 &p2)
{
	vec3 AB, AC;
	m_EdgeAB = p1 - p0;
	m_EdgeAC = p2 - p0;
	m_Normal = glm::normalize(glm::cross(m_EdgeAB,m_EdgeAC));	
	d = glm::dot(-p0, m_Normal);
	a = m_Normal.x;
	b = m_Normal.y;
	c = m_Normal.z;
	//Normalize();
}
inline bool Plane::Inside(const BVSphere &sphere) const
{
	if (Collision(sphere, this))
		return true;
	
	return TestSphereHalfSpace(sphere);
}
inline bool const Plane::Collision(const BVSphere & s, const Plane*  p) const {
	
	float dist = glm::dot(s.position, m_Normal)-d;
	return abs(dist) <= s.radius;
}
inline bool Plane::TestSphereHalfSpace(BVSphere s)const
{
	float dist = glm::dot(s.position, m_Normal)-d;
	return dist < -s.radius;
}
inline GLfloat Plane::Project(const vec3 & spherePos, const Plane * p)const {

	return glm::dot(vec4(a, b, c, d), vec4(spherePos, 1));
}
inline void Plane::Normalize()
{
	float mag;
	mag = sqrt(a * a + b * b + c * c);
	a = a / mag;
	b = b / mag;
	c = c / mag;
	d = d / mag;
	
}
class GraphicsDebug;

class Frustum {
public:
	enum Side { Near, Far, Top, Right, Bottom, Left, NumPlanes };
	std::shared_ptr<GraphicsDebug> dbg;
	Plane m_Planes[NumPlanes];	// planes of the frustum in camera space
	vec3 m_NearClip[4];			// verts of the near clip plane in camera space
	vec3 m_FarClip[4];			// verts of the far clip plane in camera space
	std::vector<vec3>worldVerts;
	float m_Fov;				// field of view in radians
	float m_Aspect;				// aspect ratio - width divided by height
	float m_Near;				// near clipping distance
	float m_Far;				// far clipping distance
	Frustum();

	//bool Inside(const vec3 &point) const;
	bool Inside(const BVSphere &sphere) const;
	
	const Plane &Get(Side side) { return m_Planes[side]; }
	/*void SetFOV(float fov) { m_Fov = fov; Init(m_Fov, m_Aspect, m_Near, m_Far); }
	void SetAspect(float aspect) { m_Aspect = aspect; Init(m_Fov, m_Aspect, m_Near, m_Far); }
	void SetNear(float nearClip) { m_Near = nearClip; Init(m_Fov, m_Aspect, m_Near, m_Far); }
	void SetFar(float farClip) { m_Far = farClip; Init(m_Fov, m_Aspect, m_Near, m_Far); }*/
	void Init(const float fov, const float aspect, const float near, const float far);
	
	void RenderInit();
	
	void Render();

};