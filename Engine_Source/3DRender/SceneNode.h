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

typedef BaseRenderComponent* WeakBaseRenderComponentPtr;

class SceneNodeProperties
{
	friend class SceneNode;

protected:
	ObjectId                 m_Id;
	std::string				m_Name;
	mat4					m_ToWorld, m_FromWorld;
	Sphere					m_BVsphere;
	RenderPass				m_RenderPass;

public:
	
	SceneNodeProperties(void);
	const ObjectId &ObjectId() const { return m_Id; }
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

};

typedef std::vector<std::shared_ptr<ISceneNode> > SceneNodeList;
typedef std::vector<Mesh> MeshList;


class SceneNode : public ISceneNode
{
	friend class Scene;
protected:
	SceneNodeList			m_Children;
	SceneNode				*m_pParent;
	SceneNodeProperties		m_Props;
	WeakBaseRenderComponentPtr	m_RenderComponent;
	MeshList m_Meshes;
	std::shared_ptr<Shaders> NodeShader;
public:
	SceneNode();
	SceneNode(ObjectId ObjectId, WeakBaseRenderComponentPtr renderComponent, RenderPass renderPass)
	{
		
		m_Props.m_RenderPass = renderPass;
		m_Props.m_Id = ObjectId;
		

	}

	void SetMeshList(std::vector<Mesh> inMesh);

	virtual ~SceneNode();

	virtual const SceneNodeProperties* const VGet() const { return &m_Props; }

	virtual void VSetTransform(const mat4 *toWorld, const mat4 *fromWorld = NULL);

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
	Sphere GetBVSphere()const { return m_Props.m_BVsphere; }

	


	

	const vec3 GetWorldPosition() const {
		vec4 Wposition = m_Props.m_ToWorld[3];
		if (Wposition.w != 1)
			return glm::vec3(Wposition) / Wposition.w;

		else return glm::vec3(m_Props.m_ToWorld[3]);
	}					

	

	void SetRadius(const float radius) { m_Props.m_BVsphere.radius = radius; }
	void SetSpherePosition(const vec3 InPos) { m_Props.m_BVsphere.position = InPos; }




	
	
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

class CameraNode : public SceneNode {
	GLfloat Xoffset, Zoffset, vdist, hdist;
	GLfloat yaw, pitch, theta, phi;
	GLfloat TerrainHeight;
	GLfloat FieldOfView;
	glm::vec3 front, campos, camfront, camup, Right, Target, Home;
	void UpdateOffsetsVectors();
	GLfloat radius;
	mat4 Projection, View;
	
	std::shared_ptr<SceneNode> m_pTarget;
	Frustum m_Frustum;
public:
	CameraNode(const ObjectId Id,
		WeakBaseRenderComponentPtr renderComponent,
		RenderPass renderPass)
		: SceneNode(Id, renderComponent, renderPass), 
		pitch(15),
		campos(glm::vec3(0, 0, 0)),
		camfront(glm::vec3(0, 0, -1)),
		camup(glm::vec3(0, 1, 0)),
		yaw(0),
		FieldOfView(90.0f),Target(vec3(0,0,0)), radius(30) {

		Projection = glm::perspective(60.0f, (float)WIDTH / HEIGHT, 0.1f, 1800.0f);
		UpdateOffsetsVectors();
		
	
		EDITOR_LOG("Made a CameraNode")
		
		

	}
	mat4 GetProjection() { return Projection; }
	mat4 GetView() { return View; }
	virtual void VOnUpdate(Scene *, unsigned long const elapsedMs);
	void ExtractPlanesGL(bool normalize);
	
	
	virtual void VRender(Scene *pScene)override;
	
	void SetTarget(std::shared_ptr<SceneNode> pTarget)
	{
		Target = pTarget->GetWorldPosition();
	}
	void SetYaw(GLfloat InYaw) { yaw += InYaw; }
	void SetPitch(GLfloat InPitch) { pitch += InPitch; }
	vec3 GetCameraPosition()const { return campos; }
	Frustum* GetFrustum() { return &m_Frustum; }
	void SetVectorTarget(vec3 inTarget) { Target = inTarget; }
	void SetProjection(GLuint width, GLuint height) 
	{ 
		Projection = glm::perspective(60.0f, (float)height / width, 0.1f, 1800.0f);
		EDITOR_LOG(std::string(std::string("Projection set ")+"Height: "+ ToStr(height) +" Width: " + ToStr(width)))
	}
	
};

class OGLMeshNode : public SceneNode
{
	GLuint ProjectionMatrixID, ViewMatrixID, ModelMatrixID, lightPosLoc, viewPosLoc, LC;
	mat4 ModelMatrix;
	vec3 lightColor;
public:
	OGLMeshNode(const ObjectId Id,
		WeakBaseRenderComponentPtr renderComponent,
		RenderPass renderPass)
		: SceneNode(Id, renderComponent, renderPass) 
	{
		
		NodeShader.reset(new Shaders("../shaders/dbgVert.glsl", "../shaders/ColliderFrag.glsl"));
		LoadUtility::loadModel(m_Meshes, "../assets/box.fbx", MeshType::NO_TEXTURE);
		for (GLuint i = 0; i < m_Meshes.size();i++)
			m_Meshes[i].SetShader(NodeShader->getProgram());
		SetUniforms();
		ModelMatrix = mat4(1.0f);
		
		

	}
	void SetUniforms()
	{
		lightColor = glm::vec3(1, 1, 1);
		ProjectionMatrixID = glGetUniformLocation(NodeShader->getProgram(), "Projection");
		ViewMatrixID = glGetUniformLocation(NodeShader->getProgram(), "View");
		ModelMatrixID = glGetUniformLocation(NodeShader->getProgram(), "Model");
		
	}
	
	virtual void VRender(Scene *pScene) override;
	virtual bool VPreRender(Scene* pScene) override;
	virtual void VOnUpdate(Scene *, unsigned long const elapsedMs)override;
	virtual bool VIsVisible(Scene * pScene) const;
	
	
	
	
	
};
class CubemapNode : public SceneNode
{
	GLuint ProjectionMatrixID, ViewMatrixID,SkyBox;
public:
	CubemapNode(const ObjectId Id,
		WeakBaseRenderComponentPtr renderComponent,
		RenderPass renderPass)
		: SceneNode(Id, renderComponent, renderPass) {
		
		NodeShader.reset(new Shaders("../shaders/3Dvert.glsl", "../shaders/3Dfrag.glsl") );
		LoadUtility::loadModel(m_Meshes, "../assets/box.fbx" ,MeshType::SKYBOX);
		SetUniforms();

	}
	void SetUniforms()
	{
		SkyBox = glGetUniformLocation(NodeShader->getProgram(), "SkyBox");
		ProjectionMatrixID = glGetUniformLocation(NodeShader->getProgram(), "Projection");
		ViewMatrixID = glGetUniformLocation(NodeShader->getProgram(), "View");
	}
	virtual bool VPreRender(Scene *pScene) override;

	virtual void VRender(Scene *pScene) override;
	
	virtual void VPostRender(Scene *pScene) override;

};