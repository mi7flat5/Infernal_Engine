#pragma once

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



class SceneNode : public ISceneNode
{
	friend class Scene;
protected:
	SceneNodeList			m_Children;
	SceneNode				*m_pParent;
	SceneNodeProperties		m_Props;
	WeakBaseRenderComponentPtr	m_RenderComponent;
public:
	SceneNode();
	SceneNode(ObjectId ObjectId, WeakBaseRenderComponentPtr renderComponent, RenderPass renderPass);

	virtual ~SceneNode();

	virtual const SceneNodeProperties* const VGet() const { return &m_Props; }

	virtual void VSetTransform(const mat4 *toWorld, const mat4 *fromWorld = NULL);

	virtual void VOnRestore(Scene *pScene);
	virtual void VOnUpdate(Scene *, unsigned long const elapsedMs);

	virtual void VPreRender(Scene *pScene);
	virtual bool VIsVisible(Scene *pScene) const;
	virtual void VRender(Scene *pScene);
	virtual void VRenderChildren(Scene *pScene);
	virtual void VPostRender(Scene *pScene);

	virtual bool VAddChild(std::shared_ptr<ISceneNode> kid);
	virtual bool VRemoveChild(ObjectId id);
	virtual void VOnLostDevice(Scene *pScene);


	


	

	const vec3 GetWorldPosition() const;					// [mrmike] added post-press to respect ancestor's position 

	

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

	virtual void VRender(Scene *pScene);
};