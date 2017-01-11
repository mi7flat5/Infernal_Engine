#pragma once
struct BVSphere;
class Scene;
class RayPick {
	vec3 RayStart, RayDirection, ViewPos;
	mat4 Proj,invPV;
public:
	RayPick(float x,float y,Scene* pScene);
	RayPick(float x, float y, unsigned int Width, unsigned int Height, Scene* pScene);
	bool RayTest(BVSphere *Sphere);

	~RayPick() {}
};