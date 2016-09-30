#pragma once
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
	// normal faces away from you if you send in verts in counter clockwise order....
	inline void Init(const vec3 &p0, const vec3 &p1, const vec3 &p2);
	bool Inside(const Sphere &sphere) const;
	
	bool Inside(const vec3 &point) const;
	vec3 GetNorm()const { return m_Normal; }
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
}
inline bool Plane::Inside(const Sphere &sphere) const
{
	return Collision(sphere, this);
	
}
inline GLfloat Plane::Project(const vec3 & spherePos, const Plane * p)const {
	return std::abs(spherePos.x*p->a + spherePos.y*p->b + spherePos.z*p->c + p->d);
}

inline bool const Plane::Collision(const Sphere & s, const Plane*  p) const{
	return Project(s.position, p) / p->ScalerNorm() < s.radius;
}