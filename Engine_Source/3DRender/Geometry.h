#pragma once
extern vec3 g_Up;
extern vec3 g_Right;
extern vec3 g_Forward;

extern vec4 g_Up4;
extern vec4 g_Right4;
extern vec4 g_Forward4;

class CameraNode;

class Geometry
{
public:
	Geometry();
	~Geometry();
};

class BVSphere {
public:
	Shaders * dbgShader;
	vec3 position;
	GLfloat radius;
	GLuint          program;
	GLuint          vao,u_Pos,VBO, ProjectionMatrixID, ModelMatrixID,ViewMatrixID;
	mat4 ProjectionMat, ModelMatrix, ViewMat;
	
	BVSphere(){}
	~BVSphere(){}		 
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
	void ApplyTransform(mat4 InvMVmat);
	const Plane &Get(Side side) { return m_Planes[side]; }
	/*void SetFOV(float fov) { m_Fov = fov; Init(m_Fov, m_Aspect, m_Near, m_Far); }
	void SetAspect(float aspect) { m_Aspect = aspect; Init(m_Fov, m_Aspect, m_Near, m_Far); }
	void SetNear(float nearClip) { m_Near = nearClip; Init(m_Fov, m_Aspect, m_Near, m_Far); }
	void SetFar(float farClip) { m_Far = farClip; Init(m_Fov, m_Aspect, m_Near, m_Far); }*/
	void Init(const float fov, const float aspect, const float near, const float far);
	
	void RenderInit();
	
	void Render();

};