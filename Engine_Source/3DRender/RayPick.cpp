#include"Engine.h"
#include"RayPick.hpp"
#include"Scene.h"


#define sqr(x) x*x
//Use with editor
RayPick::RayPick(float x, float y, unsigned int Width, unsigned int Height,Scene* pScene)
{
	float nx = -1+(2.0f * x) / Width;
	float ny = 1.0f - (2.0f * y) / Height;
	float nz = 1.0f;
	
	Proj = pScene->GetCamera()->GetProjection();
		
	vec4 wCoord(nx, ny, nz, 1);
	invPV = glm::inverse(Proj);

	RayStart =vec3(invPV*wCoord);
	RayDirection = glm::normalize(vec3(wCoord));
		
}
//use for global Height/Width -- standalone game or window
RayPick::RayPick(float x, float y,Scene* pScene)
{
	float nx = -1 + (2.0f * x) / WIDTH;
	float ny = 1.0f - (2.0f * y) / HEIGHT;
	float nz = 1.0f;

	Proj = pScene->GetCamera()->GetProjection();

	vec4 wCoord(nx, ny, nz, 1);
	invPV = glm::inverse(Proj);

	RayStart = vec3(invPV*wCoord);
	RayDirection = glm::normalize(vec3(wCoord));
}
bool RayPick::RayTest(BVSphere* Sphere) {
	
	vec3 sp = Sphere->position;
	float ViewRadius = Sphere->radius;
	

	glm::vec3 Reach = RayStart+RayDirection*1800.0f;
	glm::vec3 ThisPosition = sp;
	glm::vec3 e = ThisPosition- RayStart ;
	
	GLfloat a = glm::dot(e, RayDirection);
	if (a < 0)
		return false;

	if (glm::dot(e, e) < (sqr(ViewRadius)))
		return true;

	GLfloat eMagsqr = sqr(e.x) + sqr(e.y) + sqr(e.z);
	GLfloat reachMagsqr = sqr(Reach.x) + sqr(Reach.y) + sqr(Reach.z);

	if (eMagsqr > reachMagsqr)
		return false;

	if (sqr(ViewRadius) - glm::dot(e, e) + sqr(a) > 0)
		return true;
	
	return false;
}
