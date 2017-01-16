#include "Engine.h"
#include "SceneNode.h"


CubemapNode::CubemapNode(const ObjectId Id,
	WeakBaseRenderComponentPtr renderComponent,
	RenderPass renderPass, const char* shaderV, const char* shaderF, const char* meshPath)
	: SceneNode(Id, renderComponent, renderPass)
{
	NodeShader.reset(new Shaders(shaderV, shaderF));
	LoadUtility::loadModel(m_Meshes, meshPath, MeshType::SKYBOX);
	SetUniforms();
	for (GLuint i = 0; i < m_Meshes.size();i++)
		m_Meshes[i].SetShader(NodeShader->getProgram());
	SetRadius(0);
	m_Props.m_Name = "CubemapNode";
}
void CubemapNode::SetUniforms()
{
	SkyBox = glGetUniformLocation(NodeShader->getProgram(), "SkyBox");
	ProjectionMatrixID = glGetUniformLocation(NodeShader->getProgram(), "Projection");
	ViewMatrixID = glGetUniformLocation(NodeShader->getProgram(), "View");
}


void CubemapNode::VRender(Scene * pScene)
{
	NodeShader->Use();

	glm::mat4 CubeView = glm::mat4(glm::mat3(pScene->GetCamera()->GetView()));// remove translations
	glm::mat4 CubeProjection = pScene->GetCamera()->GetProjection();
	glUniformMatrix4fv(ProjectionMatrixID, 1, GL_FALSE, &CubeProjection[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &CubeView[0][0]);
	for (int i = 0;i < m_Meshes.size();++i)
		m_Meshes[i].DrawMesh(MeshType::SKYBOX);

}

