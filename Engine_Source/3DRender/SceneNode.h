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

protected:
	ObjectId                 m_Id;
	std::string				m_Name;
	mat4					m_ToWorld, m_FromWorld;
	
	RenderPass				m_RenderPass;

public:
	
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
};

typedef std::vector<std::shared_ptr<ISceneNode> > SceneNodeList;
typedef std::vector<Mesh> MeshList;


class SceneNode : public ISceneNode
{
	friend class Scene;
protected:
	mat4 ModelMatrix, ViewMat, ProjectionMat;
	GLuint ProjectionMatrixID, ViewMatrixID, ModelMatrixID;
	SceneNodeList			m_Children;
	SceneNode				*m_pParent;
	SceneNodeProperties		m_Props;
	WeakBaseRenderComponentPtr	m_RenderComponent;
	MeshList m_Meshes;
	std::shared_ptr<Shaders> NodeShader;
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
	BVSphere GetBVSphere()const { return m_Props.m_BVsphere; }
	virtual const vec3 GetWorldPosition() const {
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
class OGLMeshNode : public SceneNode
{
	GLuint lightPosLoc, viewPosLoc, LC;
	
	vec3 lightColor;
	vec3 lightPos;
	
public:
	OGLMeshNode(const ObjectId Id,
		WeakBaseRenderComponentPtr renderComponent,
		RenderPass renderPass, const char* shaderV, const char* shaderF, const char* meshPath)
		: SceneNode(Id, renderComponent, renderPass)
	{

		NodeShader.reset(new Shaders(shaderV, shaderF));
		LoadUtility::loadModel(m_Meshes, meshPath, MeshType::NO_TEXTURE);
		for (GLuint i = 0; i < m_Meshes.size();i++)
			m_Meshes[i].SetShader(NodeShader->getProgram());
		SetUniforms();
		ModelMatrix = mat4(1.0f);
		vec3 lpos = vec3(0, 5, -5);
		SetRadius(1);
		

	}
	void SetUniforms()
	{
		lightColor = glm::vec3(1, 1, 1);
		ProjectionMatrixID = glGetUniformLocation(NodeShader->getProgram(), "Projection");
		ViewMatrixID = glGetUniformLocation(NodeShader->getProgram(), "View");
		ModelMatrixID = glGetUniformLocation(NodeShader->getProgram(), "Model");
		lightPosLoc = glGetUniformLocation(NodeShader->getProgram(), "lightPos");
	}

	virtual void VRender(Scene *pScene) override;
	virtual bool VPreRender(Scene* pScene) override;
	virtual void VOnUpdate(Scene *, unsigned long const elapsedMs)override;
	virtual bool VIsVisible(Scene * pScene) const;
	vec3 getPosition() 
	{
		return vec3(ModelMatrix[3]);
	}
	virtual const vec3 GetWorldPosition() const {
		return vec3(ModelMatrix[3]);

	} 
	void setPosition(vec3 inPos) {
		this->ModelMatrix = Transform::translate(inPos.x, inPos.y, inPos.z);//*Transform::scale(3, 3, 3);
		SetSpherePosition(inPos);
	}
	void setScale(mat4 m) { ModelMatrix = ModelMatrix*m; }

};
class CameraNode : public SceneNode {
	GLfloat Xoffset, Zoffset, vdist, hdist;
	GLfloat yaw, pitch, theta, phi;
	GLfloat TerrainHeight;
	GLfloat FieldOfView;
	glm::vec3 front, campos, camfront, camup, rightvec, Target, Home;
	void UpdateOffsetsVectors();
	GLfloat radius;
	mat4 Projection, View;
	
	std::shared_ptr<OGLMeshNode> m_pTarget;
	Frustum m_Frustum;
public:
	CameraNode(const ObjectId Id,
		WeakBaseRenderComponentPtr renderComponent,
		RenderPass renderPass)
		: SceneNode(Id, renderComponent, renderPass), 
		pitch(0),
		campos(glm::vec3(0, 0, 0)),
		camfront(glm::vec3(0, 0, -1)),
		camup(glm::vec3(0, 1, 0)),
		yaw(90),
		FieldOfView(90.0f),Target(vec3(0,0,0)), radius(20) {

		Projection = glm::perspective(110.0f, (float)WIDTH / HEIGHT, 0.1f, 1800.0f);
		m_Frustum.Init(glm::radians(110.0), (float)WIDTH / HEIGHT, 0.01f, 1800.0f);
		UpdateOffsetsVectors();

	}
	mat4 GetProjection() { return Projection; }
	mat4 GetView() { return View; }
	vec3 GetFront() { return camfront; }
	void MoveForward(float inVal) { Target += camfront*inVal; };
	void MoveRight(float inVal) { Target += rightvec*inVal; };
	virtual void VOnUpdate(Scene *, unsigned long const elapsedMs);
	void ExtractPlanesGL(bool normalize);
	void SetCamRadius(float inAdjustment) 
	{ 
		if(inAdjustment >0)
			radius += 1.0;
		else radius -= 1;
			
		if (radius >= 60.0)
		radius = 59.0;
		if (radius <= 5.0)
		radius = 5.0;
	}
	
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
	vec3 GetRight() { return rightvec; }
	vec3 GetTargetPos() { return Target; }
	void SetYaw(GLfloat InYaw) { yaw += InYaw; }
	void SetPitch(GLfloat InPitch) { pitch += InPitch; }
	vec3 GetCameraPosition()const { return campos; }
	Frustum* GetFrustum() { return &m_Frustum; }
	void SetVectorTarget(vec3 inTarget) { Target = inTarget; }
	void SetProjection(GLuint width, GLuint height) 
	{ 
		Projection = glm::perspective(90.0f, (float)width / height, 0.1f, 1800.0f);
		m_Frustum.Init(glm::radians(90.0), (float)WIDTH / HEIGHT, 0.01f, 1000.0f);
		//glViewport(0, 0, width, height);
		//EDITOR_LOG(std::string(std::string("Projection set ")+"Height: "+ ToStr(height) +" Width: " + ToStr(width)))
	}
	
};


class CubemapNode : public SceneNode
{
	GLuint SkyBox;
public:
	CubemapNode(const ObjectId Id,
		WeakBaseRenderComponentPtr renderComponent,
		RenderPass renderPass, const char* shaderV, const char* shaderF, const char* meshPath)
		: SceneNode(Id, renderComponent, renderPass) 
	{
		NodeShader.reset(new Shaders(shaderV,shaderF ) );
		LoadUtility::loadModel(m_Meshes, meshPath ,MeshType::SKYBOX);
		SetUniforms();
		for (GLuint i = 0; i < m_Meshes.size();i++)
			m_Meshes[i].SetShader(NodeShader->getProgram());

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
class TerrainNode : public SceneNode
{
	GLint Width, Height;
	GLuint Scale, LastValidHeight, DispLevelID, SpecularShininessID, NormMappingID, lightPosLoc;

	GLfloat MaxX, MaxZ, MinX, MinZ, DispLevel;
	unsigned char * HeightMapImage;

	void SetMinMaxBoundry();//move out of scene node
	void SetScale(GLuint InScale);//move out of scene node
	vec3 lightPos;
public:
	TerrainNode(const ObjectId Id, WeakBaseRenderComponentPtr renderComponent, RenderPass renderPass)
		: SceneNode(Id, renderComponent, renderPass) 
	{
		LoadUtility::loadModel(m_Meshes, "..//assets//ParisTerrain.fbx", MeshType::TERRAIN);
		HeightMapImage = LoadUtility::loadHeightMap("..//media//hm_d.jpg", Width, Height);
		NodeShader.reset( INFERNAL_NEW Shaders("..//shaders//dispmap.vs.glsl",
			"..//shaders//dispmap.tcs.glsl",
			"..//shaders//dispmap.tes.glsl",
			"..//shaders//dispmap.fs.glsl"));
		
		ProjectionMatrixID = glGetUniformLocation(NodeShader->getProgram(), "Projection");
		ViewMatrixID = glGetUniformLocation(NodeShader->getProgram(), "View");
		ModelMatrixID = glGetUniformLocation(NodeShader->getProgram(), "Model");
		lightPosLoc = glGetUniformLocation(NodeShader->getProgram(), "light");
		for (GLuint i = 0; i < m_Meshes.size();i++)
			m_Meshes[i].SetShader(NodeShader->getProgram());
		lightPos = vec3(0, 25, 25);
		
		SetScale(50);
	}
	virtual ~TerrainNode();
	GLuint GetHeight(glm::vec3 Position);//move out of scene node
	//TerrainNode(const std::string &InPath, MeshType shader);
	virtual bool VPreRender(Scene *pScene) override;
	virtual void VOnUpdate(Scene *, unsigned long const elapsedMs);
	virtual void VRender(Scene *pScene) override;

	virtual void VPostRender(Scene *pScene) override;
};