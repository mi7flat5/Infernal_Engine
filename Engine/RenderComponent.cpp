#include"Engine.h"
#include "RenderComponent.h"


const char* MeshRenderComponent::g_Name = "MeshRenderComponent";
const char* CubeMapRenderComponent::g_Name = "CubeMapRenderComponent";



bool BaseRenderComponent::VInit(tinyxml2::XMLElement * pData)
{
	
	return false;
}

void BaseRenderComponent::VPostInit(void)
{
	std::shared_ptr<SceneNode> pSceneNode(VGetSceneNode());
}

void BaseRenderComponent::VOnChanged(void)
{
}

tinyxml2::XMLElement * BaseRenderComponent::VGenerateXml(void)
{
	return nullptr;
}

std::shared_ptr<SceneNode> BaseRenderComponent::VGetSceneNode(void)
{
	
	if (!m_pSceneNode)
		m_pSceneNode = VCreateSceneNode();
	return m_pSceneNode;
	
}



std::shared_ptr<SceneNode> MeshRenderComponent::VGetSceneNode(void)
{
	if (!m_pSceneNode)
		m_pSceneNode = VCreateSceneNode();
	return m_pSceneNode;
	
}

MeshRenderComponent::MeshRenderComponent(void)
{

	
}

std::shared_ptr<SceneNode> MeshRenderComponent::VCreateSceneNode(void)
{
	WeakBaseRenderComponentPtr weak(this);
	std::shared_ptr<SceneNode> bS;

	if(m_pOwner)
	bS.reset(INFERNAL_NEW OGLnode(m_pOwner->GetId(), weak, RenderPass_Actor));
	
	
	std::shared_ptr<OGLnode> dS = std::static_pointer_cast<OGLnode, SceneNode>(bS);
	
	return dS;
}

void MeshRenderComponent::VCreateInheritedXmlElements(tinyxml2::XMLElement * pBaseElement)
{
}





std::shared_ptr<SceneNode> CubeMapRenderComponent::VCreateSceneNode(void)
{
	return std::shared_ptr<SceneNode>();
}

void CubeMapRenderComponent::VCreateInheritedXmlElements(tinyxml2::XMLElement * pBaseElement)
{
}
