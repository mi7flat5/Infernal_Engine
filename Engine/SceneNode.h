#pragma once
#include"Mesh.h"
#include"Shaders.hpp"
#include"LoadUtility.h"
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
	float					m_Radius;
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
	float Radius() const { return m_Radius; }

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
	SceneNode(ObjectId ObjectId, WeakBaseRenderComponentPtr renderComponent, RenderPass renderPass);

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


	


	

	const vec3 GetWorldPosition() const {
		vec4 Wposition = m_Props.m_ToWorld[3];
		if (Wposition.w != 1)
			return glm::vec3(Wposition) / Wposition.w;

		else return glm::vec3(m_Props.m_ToWorld[3]);
	}					

	

	void SetRadius(const float radius) { m_Props.m_Radius = radius; }




	
	
};

class RootNode : public SceneNode
{
public:
	RootNode();
	virtual bool VAddChild(std::shared_ptr<ISceneNode> kid);
	virtual void VRenderChildren(Scene *pScene);
	virtual bool VRemoveChild(ObjectId id);
	virtual bool VIsVisible(Scene *pScene) const { return true; }
};

class CameraNode : public SceneNode {
	GLfloat Xoffset, Zoffset, vdist, hdist;
	GLfloat yaw, pitch, theta, phi;
	GLfloat TerrainHeight;
	GLfloat FieldOfView;
	glm::vec3 front, campos, camfront, camup, Right, Target, Home;
	void UpdateOffsetsVectors();
	GLfloat radius;
	glm::mat4 Projection;
	glm::mat4 View;
	std::shared_ptr<SceneNode> m_pTarget;
public:
	CameraNode(const ObjectId Id,
		WeakBaseRenderComponentPtr renderComponent,
		RenderPass renderPass)
		: SceneNode(Id, renderComponent, renderPass), 
		pitch(15),
		campos(glm::vec3(0, 5, 5)),
		camfront(glm::vec3(0, 0, -1)),
		camup(glm::vec3(0, 1, 0)),
		yaw(0),
		FieldOfView(90.0f),Target(vec3(0,5,5)), radius(10) {
		Projection = Transform::perspective(90.0, (float)600 / 800, 0.1f, 1800.0f);
		UpdateOffsetsVectors();
	

	}
	mat4 GetProjection() { return Projection; }
	mat4 GetView() { return View; }
	virtual void VOnUpdate(Scene *, unsigned long const elapsedMs);
	virtual void VRender(Scene *pScene)override;
	
	void SetTarget(std::shared_ptr<SceneNode> pTarget)
	{
		Target = pTarget->GetWorldPosition();
	}
	
};

class OGLnode : public SceneNode
{
public:
	OGLnode(const ObjectId Id,
		WeakBaseRenderComponentPtr renderComponent,
		RenderPass renderPass)
		: SceneNode(Id, renderComponent, renderPass) {
		std::cout << "\nOGL SceneNode created";
	}
	
	
	virtual void VRender(Scene *pScene) override {}
	
	
	
};
class CubemapNode : public SceneNode
{
	GLuint ProjectionMatrixID, ViewMatrixID,SkyBox;
public:
	CubemapNode(const ObjectId Id,
		WeakBaseRenderComponentPtr renderComponent,
		RenderPass renderPass)
		: SceneNode(Id, renderComponent, renderPass) {
		NodeShader.reset(new Shaders("shaders/3Dvert.glsl", "shaders/3Dfrag.glsl") );
		LoadUtility::loadModel(m_Meshes, "assets/box.fbx" ,MeshType::SKYBOX);
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