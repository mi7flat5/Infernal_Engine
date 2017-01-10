#include "Engine.h"
#include "SceneNode.h"

OGLMeshNode::OGLMeshNode(const ObjectId Id,
	WeakBaseRenderComponentPtr renderComponent,
	RenderPass renderPass, const char* shaderV, const char* shaderF, const char* meshPath)
	: SceneNode(Id, renderComponent, renderPass)
{
	m_Props.m_Name = "OGLMeshNode";
	NodeShader.reset(new Shaders(shaderV, shaderF));
	LoadUtility::loadModel(m_Meshes, meshPath, MeshType::NO_TEXTURE);
	for (GLuint i = 0; i < m_Meshes.size();i++)
		m_Meshes[i].SetShader(NodeShader->getProgram());
	
	lightColor = glm::vec3(1, 1, 1);
	ProjectionMatrixID = glGetUniformLocation(NodeShader->getProgram(), "Projection");
	ViewMatrixID = glGetUniformLocation(NodeShader->getProgram(), "View");
	ModelMatrixID = glGetUniformLocation(NodeShader->getProgram(), "Model");
	lightPosLoc = glGetUniformLocation(NodeShader->getProgram(), "lightPos");
	
	ModelMatrix = mat4(1.0f);
	vec3 lpos = vec3(0, 5, -5);
	SetRadius(3);

	SetSpherePosition(vec3(ModelMatrix[3]));

}
void OGLMeshNode::VRender(Scene * pScene)
{
	NodeShader->Use();
	for (int i = 0;i < m_Meshes.size();i++)
	{
		m_Meshes[i].DrawMesh(MeshType::NO_TEXTURE);
	}

}

bool OGLMeshNode::VPreRender(Scene * pScene)
{
	NodeShader->Use();
	ViewMat = pScene->GetCamera()->GetView();
	ProjectionMat = pScene->GetCamera()->GetProjection();
	vec3 campos = pScene->GetCamera()->GetCameraPosition();

	SetSpherePosition(vec3(ProjectionMat*ViewMat*ModelMatrix[3]));

	vec3 lpos = vec3(0, 5, -5);

	glUniform3fv(LC, 1, &lightColor[0]);
	glUniform3f(lightPosLoc, lpos.x, lpos.y, lpos.z);
	glUniform3f(viewPosLoc, campos.x, campos.y, campos.z);
	glUniformMatrix4fv(ProjectionMatrixID, 1, GL_FALSE, &ProjectionMat[0][0]);
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMat[0][0]);

	return true;
}

void OGLMeshNode::VOnUpdate(Scene *pScene, unsigned long const elapsedMs)
{
}
bool OGLMeshNode::VIsVisible(Scene * pScene) const
{
	Frustum* pCurrentFrustum = pScene->GetCamera()->GetFrustum();

	if (pCurrentFrustum)
	{
		if (pCurrentFrustum->Inside(GetBVSphere()))
		{
			//std::cout << ".\n";
			return true;

		}
	}
	//std::cout << "NotVisible\n";
	return false;
}