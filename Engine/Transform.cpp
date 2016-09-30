#include"Engine.h"
#include "Transform.h"

mat3 Transform::RotateMat3(const float degrees, const vec3& axis1) {
	vec3 axis = glm::normalize(axis1);
	mat3 R;
	mat3 I(1.0f);
	mat3 second(
		axis.x*axis.x, axis.x*axis.y, axis.x*axis.z,
		axis.x*axis.y, axis.y*axis.y, axis.y*axis.z,
		axis.x*axis.z, axis.y*axis.z, axis.z*axis.z);
	glm::transpose(second);
	mat3 third(
		0, -axis.z, axis.y,
		axis.z, 0, -axis.x,
		-axis.y, axis.x, 0);
	glm::transpose(third);
	R = cos(glm::radians(degrees))*I + (1 - cos(glm::radians(degrees)))*second + sin(glm::radians(degrees))*third;
	return R;
}
//Returns a 4X4 rotation matrix with no translations. 
mat4 Transform::RotateMat4(const float degrees, const vec3& axis1) {
	vec3 axis = glm::normalize(axis1);
	mat3 R;
	mat3 I(1.0f);
	mat3 second(
		axis.x*axis.x, axis.x*axis.y, axis.x*axis.z,
		axis.x*axis.y, axis.y*axis.y, axis.y*axis.z,
		axis.x*axis.z, axis.y*axis.z, axis.z*axis.z);
	glm::transpose(second);
	mat3 third(
		0, -axis.z, axis.y,
		axis.z, 0, -axis.x,
		-axis.y, axis.x, 0);
	glm::transpose(third);
	R = cos(glm::radians(degrees))*I + (1 - cos(glm::radians(degrees)))*second + sin(glm::radians(degrees))*third;
	return mat4(R);
}
void Transform::left(float degrees, vec3& eye, vec3& up) {
	up = glm::normalize(up);
	eye = eye*RotateMat3(degrees, up);
}
void Transform::up(float degrees, vec3& eye, vec3& up) {
	vec3 a = glm::normalize(eye);
	up = glm::normalize(up);
	vec3 cross = glm::cross(a, up);

	eye = eye*RotateMat3(degrees, cross);
	up = up*RotateMat3(degrees, cross);
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) {
	vec3 a = eye - center;

	vec3 w = glm::normalize(a);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::normalize(glm::cross(w, u));

	mat4 look(
		u.x, u.y, u.z, -glm::dot(u, eye),
		v.x, v.y, v.z, -glm::dot(u, eye),
		w.x, w.y, w.z, -glm::dot(w, eye),
		0, 0, 0, 1
		);

	look = glm::transpose(look);

	return look;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar) {
	float d = cos(glm::radians(fovy) / 2) / sin(glm::radians(fovy) / 2);
	float A = -(zFar + zNear) / (zFar - zNear);
	float B = -(2 * zFar*zNear) / (zFar - zNear);
	
	 mat4 pers(
    d/aspect, 0, 0, 0,
	   0, d, 0, 0,
	   0, 0, A, B,
	   0, 0,-1, 0);
	 pers = glm::transpose(pers);
	 return pers;
	

}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) {
	mat4 ret(
		sx, 0, 0, 0,
		0, sy, 0, 0,
		0, 0, sz, 0,
		0, 0, 0, 1);
	ret = glm::transpose(ret);

	return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) {
	mat4 ret(
		1, 0, 0, tx,
		0, 1, 0, ty,
		0, 0, 1, tz,
		0, 0, 0, 1);
	ret = glm::transpose(ret);
	return ret;
}
vec3 Transform::upvector(const vec3 &up, const vec3 &zvec) {
	vec3 x = glm::cross(up, zvec);
	vec3 y = glm::cross(zvec, x);
	vec3 ret = glm::normalize(y);
	return ret;
}
GLfloat Transform::Smootherstep(GLfloat edge0, GLfloat edge1, GLfloat Time)
{
	bool swapped = false;
	if (edge0 > edge1)
	{
		edge0 *= -1;
		edge1 *= -1;
		swapped = true;
	}
	GLfloat x = abs(edge0 + ((edge1 - edge0) / 100)*Time);
	x = Clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);

	if (swapped)
	{
		edge0 *= -1;
		edge1 *= -1;
	}
	return edge0+(x*x*x*(x*(x * 6 - 15) + 10))*(edge1 - edge0);
}
GLfloat Transform::Smoothstep(GLfloat edge0, GLfloat edge1, GLfloat Time)
{
	bool swapped = false;
	if (edge0 > edge1)
	{
		edge0 *= -1;
		edge1 *= -1;
		swapped = true;
	}
	GLfloat x = abs(edge0 + ((edge1 - edge0) / 100)*Time);
	// Scale, bias and saturate x to 0..1 range
	x = Clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
	
	if (swapped)
	{
		edge0 *= -1;
		edge1 *= -1;
	}
		
	return edge0 + (x*x*(3 - 2 * x))*(edge1-edge0);
}

GLfloat Transform::Lerp(GLfloat Start, GLfloat End, GLfloat Percent) {
	
	return(Start + Percent*(End - Start));
}
GLdouble Transform::BilinearInterpolate(GLuint HighX, GLuint LowX, GLuint HighZ, GLuint LowZ, GLdouble ExactX, GLdouble ExactZ, GLdouble P1, GLdouble P2, GLdouble P3, GLdouble P4) {


	GLdouble Xh1 = Interpolate(LowX, HighX, ExactX, P1, P2);
	GLdouble Xh2 = Interpolate(LowX, HighX, ExactX, P3, P4);

	return Interpolate(LowZ, HighZ, ExactZ, Xh1, Xh2);

}
GLdouble Transform::Interpolate(GLuint LowEdge, GLuint HighEdge, GLdouble Tweener, GLdouble  FuncVal1, GLdouble  FuncVal2) {

	return (((HighEdge - Tweener) / (HighEdge - LowEdge)))* FuncVal1 + ((Tweener - LowEdge) / (HighEdge - LowEdge))* FuncVal2;
	//	return FuncVal1 + (Tweener - LowEdge)*((FuncVal2 - FuncVal1 ) / (HighEdge - LowEdge));

}
glm::vec3 Transform::VecLerp(glm::vec3 Start, glm::vec3 End, GLfloat Percent) {
	glm::vec3 Current;

	Current.z = Transform::Lerp(Start.z, End.z, Percent / 100);
	Current.x = Transform::Lerp(Start.x, End.x, Percent / 100);
	Current.y = Transform::Lerp(Start.y, End.y, Percent / 100);

	return Current;
}
// Compute barycentric coordinates (u, v, w) for
// point p with respect to triangle (a, b, c)
glm::vec3 Transform::Barycentric(glm::vec3 PointOnTriangle, glm::vec3 PointA, glm::vec3 PointB, glm::vec3 PointC)
{
	glm::vec3 AB = PointB - PointA, AC = PointC - PointA, v2 = PointOnTriangle - PointA;
	GLfloat d00 = glm::dot(AB, AB);
	GLfloat d01 = glm::dot(AB, AC);
	GLfloat d11 = glm::dot(AC, AC);
	GLfloat d20 = glm::dot(v2, AB);
	GLfloat d21 = glm::dot(v2, AC);
	GLfloat denom = d00 * d11 - d01 * d01;
	GLfloat V = (d11 * d20 - d01 * d21) / denom;
	GLfloat W = (d00 * d21 - d01 * d20) / denom;
	GLfloat U = 1.0f - V - W;
	glm::vec3 BaryVector = glm::vec3(U, V, W);
	return BaryVector;
}
Transform::Transform(){}
Transform::~Transform(){}