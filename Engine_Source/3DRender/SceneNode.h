#pragma once

#include"..\Utility\Shaders.hpp"
#include"..\Utility\LoadUtility.h"
#include"..\3DRender\Geometry.h"
#include"..\EventSystem\Event.h"


extern GLuint WIDTH, HEIGHT;
class SceneNode;
class Scene;
class ObjectComponent;
class BaseRenderComponent;
typedef BaseRenderComponent* WeakBaseRenderComponentPtr;
class OGLMeshNode;


class SceneNodeProperties
{
	friend class SceneNode;

public:
	ObjectId                 m_Id;
	std::string				m_Name;
	mat4					m_ToWorld, m_FromWorld;
	//Transform stored in vectors, rotation is Pitch-Yaw-Roll X-Y-Z
	glm::vec3					m_Wpos, m_WrotPYR, m_Wscale;
	RenderPass				m_RenderPass;
	
	SceneNodeProperties(void);
	const ObjectId &GetId() const { return m_Id; }
	mat4 const &ToWorld() const { return m_ToWorld; }
	mat4 const &FromWorld() const { return m_FromWorld; }
	
	void Transform(mat4 *toWorld, mat4 *fromWorld) const {

		if (toWorld)
			*toWorld = m_ToWorld;

		if (fromWorld)
			*fromWorld = m_FromWorld;
	}
	const char * Name() const { return m_Name.c_str(); }
	RenderPass RenderPass() const { return m_RenderPass; }
	float Radius() const { return m_BVsphere.radius; }


	BVSphere					m_BVsphere;
	
	float RadiusScale = 1.0f;
	 float ModelRadius;
	 vec3 ModelSpherePosition;
};

typedef std::vector<std::shared_ptr<ISceneNode> > SceneNodeList;
typedef std::vector<Mesh> MeshList;


class SceneNode : public ISceneNode
{
	friend class Scene;
protected:
	mat4 ViewMat, ProjectionMat;
	GLuint ProjectionMatrixID, ViewMatrixID, ModelMatrixID;
	SceneNodeList			m_Children;
	SceneNode				*m_pParent;
	SceneNodeProperties		m_Props;
	WeakBaseRenderComponentPtr	m_RenderComponent;
	MeshList m_Meshes;
	std::shared_ptr<Shaders> NodeShader;
	vec3 lightPos;
	GLuint lightPosLoc;
public:
	SceneNode();
	SceneNode(ObjectId Id, WeakBaseRenderComponentPtr renderComponent, RenderPass renderPass)
	{
		m_Props.m_RenderPass = renderPass;
		m_Props.m_Id = Id;
		
		
		
	}
		void SetMeshList(std::vector<Mesh> inMesh);

		virtual ~SceneNode() 
		{
			for (int i = 0; i < m_Meshes.size();++i)
			{
				m_Meshes[i].CleanUp();
			}
		}

	virtual const SceneNodeProperties* const VGet() const { return &m_Props; }

	virtual void VSetTransform( const mat4 *toWorld,  const mat4 *fromWorld = NULL);

	virtual void VOnRestore(Scene *pScene);
	virtual void VOnUpdate(Scene *, unsigned long const elapsedMs);

	virtual bool VPreRender(Scene *pScene);
	virtual bool VIsVisible(Scene *pScene) const;
	virtual void VRender(Scene *pScene);
	virtual void VRenderChildren(Scene *pScene);
	virtual void VPostRender(Scene *pScene);

	virtual bool VAddChild(std::shared_ptr<ISceneNode> kid);
	virtual bool VRemoveChild(ObjectId id);
	virtual void VOnLostDevice(Scene *pScene);
	virtual ObjectId GetObjectId()const { return m_Props.m_Id; }
	BVSphere GetBVSphere() const{ return m_Props.m_BVsphere; }
	BVSphere *GetBVSphereRefernce()  { return &m_Props.m_BVsphere; }
	virtual const vec3 GetWorldPosition() const 
	{
		return glm::vec3(m_Props.m_ToWorld[3]);
	}					
	void SetRadius(const float radius) { m_Props.m_BVsphere.radius = radius; }
	void SetSpherePosition(const vec3 InPos) { m_Props.m_BVsphere.position = InPos; }
	void setLightPos(vec3 inPos) { lightPos = inPos;}
	//Stores current transform in vector container
	void SetVectorTransform(const vec3& position, const vec3& rotation, const vec3& scale);
	void GetVectorTransform(vec3& position, vec3& rotation, vec3& scale);
};

class RootNode : public SceneNode
{
public:
	RootNode();
	virtual bool VAddChild(std::shared_ptr<ISceneNode> kid);
	virtual void VRenderChildren(Scene *pScene);
	virtual bool VRemoveChild(ObjectId id);
	virtual void VOnUpdate(Scene *, unsigned long const elapsedMs);
};
class OGLMeshNode : public SceneNode
{
	GLuint viewPosLoc, LC;
	
	vec3 lightColor;
	
	
public:
	OGLMeshNode(const ObjectId Id,
		WeakBaseRenderComponentPtr renderComponent,
		RenderPass renderPass, const char* shaderV, const char* shaderF, const char* meshPath);
	
	virtual void VRender(Scene *pScene) override;

	virtual void VOnUpdate(Scene *, unsigned long const elapsedMs)override;
	virtual bool VIsVisible(Scene * pScene) const;
	
	//Currently used in prototype, remove after controllers set up. 


	
};
class CameraNode : public SceneNode {
	GLfloat Xoffset, Zoffset, vdist, hdist;
	GLfloat yaw, pitch, theta, phi;
	GLfloat TerrainHeight;
	GLfloat FieldOfView;
	glm::vec3 front, campos, camfront, camup, rightvec, Target, Home;
	
	GLfloat radius;
	mat4 Projection, View;
	
	std::shared_ptr<SceneNode> m_pTarget;
	Frustum m_Frustum;
	void UpdateOffsetsVectors();
public:
	
	CameraNode(const ObjectId Id,WeakBaseRenderComponentPtr renderComponent,RenderPass renderPass);
		mat4 GetProjection() { return Projection; }
	mat4 GetView() { return View; }
	vec3 GetFront() { return camfront; }
	void MoveForward(float inVal) { Target += camfront*inVal; };
	void MoveRight(float inVal) { Target += rightvec*inVal; };
	void MoveUp(float inVal) { Target += g_Up*inVal; }
	void ReportPosition(){EDITOR_LOG("CamPos: "+ToStr(campos.x)+" "+ToStr(campos.y)+" "+ToStr(campos.z)) }
	virtual void VOnUpdate(Scene *, unsigned long const elapsedMs);
	void ExtractPlanesGL(bool normalize);
	void SetCamRadius(float inAdjustment);
	
	
	virtual void VRender(Scene *pScene)override;
	void SetTarget(vec3 InTarget)
	{
		Target = InTarget;
	}
	void SetTarget(std::shared_ptr<SceneNode> pTarget)
	{
		//m_pTarget = std::static_pointer_cast<OGLMeshNode>(pTarget);
	}
	GLfloat GetYaw() { return yaw; }
	GLfloat GetPitch() { return pitch; }
	vec3 GetRight() { return glm::normalize(rightvec); }
	vec3 GetTargetPos() { return Target; }
	void SetYaw(GLfloat InYaw) { yaw += InYaw; }
	void SetPitch(GLfloat InPitch) { pitch += InPitch; }
	vec3 GetCameraPosition()const { return campos; }
	Frustum* GetFrustum() { return &m_Frustum; }
	void SetVectorTarget(vec3 inTarget) { Target = inTarget; }
	void SetProjection(GLuint width, GLuint height);
	
	
};

class CubemapNode : public SceneNode
{
	GLuint SkyBox;
public:
	CubemapNode(const ObjectId Id,	WeakBaseRenderComponentPtr renderComponent,
		RenderPass renderPass, const char* shaderV, const char* shaderF, const char* meshPath);
		

	virtual void VRender(Scene *pScene) override;

	
	void SetUniforms();

};
class TerrainNode : public SceneNode
{
	GLint Width, Height;
	GLuint Scale, LastValidHeight, DispLevelID, SpecularShininessID, NormMappingID, viewPosLoc,lightPosLoc;

	GLfloat MaxX, MaxZ, MinX, MinZ, DispLevel;
	unsigned char * HeightMapImage;

	void SetMinMaxBoundry();//move out of scene node
	void SetScale(GLuint InScale);//move out of scene node
	vec3 lightPos;
public:
	TerrainNode(const ObjectId Id, WeakBaseRenderComponentPtr renderComponent, RenderPass renderPass);

	virtual ~TerrainNode();
	GLuint GetHeight(glm::vec3 Position);//move out of scene node
	//TerrainNode(const std::string &InPath, MeshType shader);

	virtual void VOnUpdate(Scene *, unsigned long const elapsedMs);
	virtual void VRender(Scene *pScene) override;

	
};