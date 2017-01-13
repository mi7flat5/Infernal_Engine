#pragma once
struct BVSphere;
class Scene;
class RayPick {
	vec3 RayStart, RayDirection;
	mat4 Proj,invPV;	
public:
	RayPick(float x, float y, Scene* pScene, unsigned int Width, unsigned int Height );
	bool RayTest(BVSphere *Sphere);
	vec3 CamRight;
	~RayPick() {}
};