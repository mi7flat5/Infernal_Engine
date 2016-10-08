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
struct Sphere {
	vec3 position;
	GLfloat radius;

};
class Plane 
{
	
	vec3 m_Normal, m_EdgeAB, m_EdgeAC;
	GLfloat Project(const vec3 & spherePos, const Plane * p) const;
	bool const Collision(const Sphere & s, const Plane* p)const;
public:
	
	Plane() {}
	
	inline void Plane::Normalize();

	// normal faces away from you if you send in verts in counter clockwise order....
	inline void Init(const vec3 &p0, const vec3 &p1, const vec3 &p2);
	bool Inside(const Sphere &sphere) const;
	
	//bool Inside(const vec3 &point) const;
	vec3 GetNorm()const { return glm::normalize(m_Normal); }
	float ScalerNorm() const {
		return sqrt(a*a + b*b + c*c);
	}
	GLfloat a, b, c, d;
};



inline void Plane::Init(const vec3 &p0, const vec3 &p1, const vec3 &p2)
{
	vec3 AB, AC;
	m_EdgeAB = p1 - p0;
	m_EdgeAC = p2 - p0;
	m_Normal = glm::cross(m_EdgeAB,m_EdgeAC);	
	d = glm::dot(m_Normal, -p0);
	a = m_Normal.x;
	b = m_Normal.y;
	c = m_Normal.z;
	Normalize();
}
inline bool Plane::Inside(const Sphere &sphere) const
{
	
	return Collision(sphere, this);
	
}
inline GLfloat Plane::Project(const vec3 & spherePos, const Plane * p)const {

	return spherePos.x*p->a + spherePos.y*p->b + spherePos.z*p->c + p->d;
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
inline bool const Plane::Collision(const Sphere & s, const Plane*  p) const{
	
	return Project(s.position, p) / p->ScalerNorm() > s.radius;
}

class Frustum {
public:
	enum Side { Near, Far, Top, Right, Bottom, Left, NumPlanes };

	Plane m_Planes[NumPlanes];	// planes of the frusum in camera space
	vec3 m_NearClip[4];			// verts of the near clip plane in camera space
	vec3 m_FarClip[4];			// verts of the far clip plane in camera space

	float m_Fov;				// field of view in radians
	float m_Aspect;				// aspect ratio - width divided by height
	float m_Near;				// near clipping distance
	float m_Far;				// far clipping distance
	Frustum();

	//bool Inside(const vec3 &point) const;
	bool Inside(const Sphere &sphere) const;
	const Plane &Get(Side side) { return m_Planes[side]; }
	void SetFOV(float fov) { m_Fov = fov; Init(m_Fov, m_Aspect, m_Near, m_Far); }
	void SetAspect(float aspect) { m_Aspect = aspect; Init(m_Fov, m_Aspect, m_Near, m_Far); }
	void SetNear(float nearClip) { m_Near = nearClip; Init(m_Fov, m_Aspect, m_Near, m_Far); }
	void SetFar(float farClip) { m_Far = farClip; Init(m_Fov, m_Aspect, m_Near, m_Far); }
	void Init(const float fov, const float aspect, const float near, const float far);

	void Render();

};