#include "Engine.h"
#include "SceneNode.h"

OGLMeshNode::OGLMeshNode(const ObjectId Id,
	WeakBaseRenderComponentPtr renderComponent,
	RenderPass renderPass, const char* shaderV, const char* shaderF, const char* meshPath)
	: SceneNode(Id, renderComponent, renderPass)
{
	m_Props.m_Name = "OGLMeshNode";
	NodeShader.reset(new Shaders(shaderV, shaderF));
	LoadUtility::loadModel(m_Meshes, meshPath, MeshType::TEXTURE_2D);
	for (GLuint i = 0; i < m_Meshes.size();i++)
		m_Meshes[i].SetShader(NodeShader->getProgram());
	
	lightColor = glm::vec3(1, 1, 1);
	ProjectionMatrixID = glGetUniformLocation(NodeShader->getProgram(), "Projection");
	ViewMatrixID = glGetUniformLocation(NodeShader->getProgram(), "View");
	ModelMatrixID = glGetUniformLocation(NodeShader->getProgram(), "Model");
	lightPosLoc = glGetUniformLocation(NodeShader->getProgram(), "lightPos");
	viewPosLoc = glGetUniformLocation(NodeShader->getProgram(), "viewPos");
	
	vec3 lpos = vec3(50, -50, -50);
	


	std::vector<vec3> sphereCalc;
	LoadUtility::LoadCollider(meshPath, sphereCalc, std::vector<GLuint>(), std::vector<vec3>());
	m_Props.m_BVsphere.SphereFromDistantPoints(sphereCalc);
	EDITOR_LOG("Sphere Radius: " + ToStr((int)m_Meshes.size()))
	//EDITOR_LOG("Sphere Radius: "+ ToStr(m_Props.m_BVsphere.radius))
		//EDITOR_LOG("Sphere Position: x " + ToStr(m_Props.m_BVsphere.position.x)+" y "+ToStr(m_Props.m_BVsphere.position.y)+" z "+ToStr(m_Props.m_BVsphere.position.z))

}
void OGLMeshNode::VRender(Scene * pScene)
{
	NodeShader->Use();
	for (int i = 0;i < m_Meshes.size();i++)
	{
		m_Meshes[i].DrawMesh(MeshType::TEXTURE_2D);
	}

}

bool OGLMeshNode::VPreRender(Scene * pScene)
{
	NodeShader->Use();
	ViewMat = pScene->GetCamera()->GetView();
	ProjectionMat = pScene->GetCamera()->GetProjection();
	vec3 campos = pScene->GetCamera()->GetCameraPosition();

	SetSpherePosition(vec3(ProjectionMat*ViewMat*ModelMatrix[3]));

	
	ModelMatrix = Transform::RotateMat4(90, vec3(1, 0, 0))*Transform::scale(0.2,0.2,0.2);
	glUniform3fv(LC, 1, &lightColor[0]);
	glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
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