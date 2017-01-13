#include"Engine.h"
#include "SceneNode.h"

CameraNode::CameraNode(const ObjectId Id,
	WeakBaseRenderComponentPtr renderComponent,
	RenderPass renderPass)
	: SceneNode(Id, renderComponent, renderPass),
	pitch(0),
	campos(glm::vec3(0, 0, 0)),
	camfront(glm::vec3(0, 0, -1)),
	camup(glm::vec3(0, 1, 0)),
	yaw(90),
	FieldOfView(90.0f), Target(vec3(0, 0, 0)), radius(20) {

	Projection = glm::perspective(110.0f, (float)WIDTH / HEIGHT, 0.1f, 1800.0f);
	m_Frustum.Init(glm::radians(110.0), (float)WIDTH / HEIGHT, 0.01f, 1800.0f);
	UpdateOffsetsVectors();
	SetRadius(0);
	m_Props.m_Name = "CameraNode";
}
void CameraNode::SetCamRadius(float inAdjustment)
{
	if (inAdjustment > 0)
		radius += 1.0;
	else radius -= 1;

	if (radius >= 60.0)
		radius = 59.0;
	if (radius <= 5.0)
		radius = 5.0;
}
void CameraNode::SetProjection(GLuint width, GLuint height)
{
	Projection = glm::perspective(90.0f, (float)width / height, 0.1f, 1800.0f);
	m_Frustum.Init(glm::radians(90.0), (float)width / height, 0.1f, 1800.0f);
}
void CameraNode::UpdateOffsetsVectors()
{
	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89)
		pitch = -89;

	theta = yaw - 90;
	phi = pitch - 90;

	//front.x = radius * sin(glm::radians(phi))*cos(glm::radians(theta));
	//if (campos.y > TerrainHeight)
	//front.y = radius * cos(glm::radians(pitch + 90));// +10; //TODO add parameter for adjusting y facing offset
	//front.z = radius * cos(glm::radians(phi))*sin(glm::radians(theta));

	camfront = glm::normalize(Target - campos);

	vdist = radius*sin(glm::radians(pitch));
	hdist = radius*cos(glm::radians(pitch));
	Xoffset = hdist*cos(glm::radians(yaw));
	Zoffset = hdist*sin(glm::radians(yaw));
	vec3 CylinCamPos = glm::normalize(vec3(radius*cos(glm::radians(yaw)), 0, radius* sin(glm::radians(yaw))));
	rightvec = glm::normalize(glm::cross(-glm::normalize( CylinCamPos),g_Up));

}
void CameraNode::VRender(Scene *pScene)
{
	UpdateOffsetsVectors();

	glm::vec3 NewCampos;
	NewCampos.y = vdist + Target.y;	//TODO add parameter for vertical distance offset

	NewCampos.x = Target.x + Xoffset;
	NewCampos.z = Target.z + Zoffset;
	campos.x = NewCampos.x;
	campos.y = NewCampos.y;//Transform::Lerp(campos.y, NewCampos.y, .30);//TODO Create variable for camera y offset
	campos.z = NewCampos.z;

	View = glm::lookAt(campos, Target, camup);//*Transform::translate(0, -5, 0);

}
void CameraNode::VOnUpdate(Scene *pScene, unsigned long const elapsedMs)
{
	if (m_pTarget)
		Target = m_pTarget->GetWorldPosition();
}
void CameraNode::ExtractPlanesGL(bool normalize)
{

	Plane* p_planes;
	p_planes = m_Frustum.m_Planes;

	/*const GLfloat *ToWorldMatrix = (const GLfloat*)glm::value_ptr(Projection * View);*/
	mat4 ToWorldMatrix = Projection*View;
	// Left clipping plane
	m_Frustum.m_Planes[Frustum::Side::Left].a = ToWorldMatrix[3][0] + ToWorldMatrix[0][0];
	m_Frustum.m_Planes[Frustum::Side::Left].b = ToWorldMatrix[3][1] + ToWorldMatrix[0][1];
	m_Frustum.m_Planes[Frustum::Side::Left].c = ToWorldMatrix[3][2] + ToWorldMatrix[0][2];
	m_Frustum.m_Planes[Frustum::Side::Left].d = ToWorldMatrix[3][3] + ToWorldMatrix[0][3];
	// Right clipping plane
	m_Frustum.m_Planes[Frustum::Side::Right].a = ToWorldMatrix[3][0] - ToWorldMatrix[0][0];
	m_Frustum.m_Planes[Frustum::Side::Right].b = ToWorldMatrix[3][1] - ToWorldMatrix[0][1];
	m_Frustum.m_Planes[Frustum::Side::Right].c = ToWorldMatrix[3][2] - ToWorldMatrix[0][2];
	m_Frustum.m_Planes[Frustum::Side::Right].d = ToWorldMatrix[3][3] - ToWorldMatrix[0][3];
	// Top clipping plane
	m_Frustum.m_Planes[Frustum::Side::Top].a = ToWorldMatrix[3][0] - ToWorldMatrix[1][0];
	m_Frustum.m_Planes[Frustum::Side::Top].b = ToWorldMatrix[3][1] - ToWorldMatrix[1][1];
	m_Frustum.m_Planes[Frustum::Side::Top].c = ToWorldMatrix[3][2] - ToWorldMatrix[1][2];
	m_Frustum.m_Planes[Frustum::Side::Top].d = ToWorldMatrix[3][3] - ToWorldMatrix[1][3];
	// Bottom clipping plane
	m_Frustum.m_Planes[Frustum::Side::Bottom].a = ToWorldMatrix[3][0] + ToWorldMatrix[1][0];
	m_Frustum.m_Planes[Frustum::Side::Bottom].b = ToWorldMatrix[3][1] + ToWorldMatrix[1][1];
	m_Frustum.m_Planes[Frustum::Side::Bottom].c = ToWorldMatrix[3][2] + ToWorldMatrix[1][2];
	m_Frustum.m_Planes[Frustum::Side::Bottom].d = ToWorldMatrix[3][3] + ToWorldMatrix[1][3];
	// Near clipping plane
	m_Frustum.m_Planes[Frustum::Side::Near].a = ToWorldMatrix[3][0] + ToWorldMatrix[2][0];
	m_Frustum.m_Planes[Frustum::Side::Near].b = ToWorldMatrix[3][1] + ToWorldMatrix[2][1];
	m_Frustum.m_Planes[Frustum::Side::Near].c = ToWorldMatrix[3][2] + ToWorldMatrix[2][2];
	m_Frustum.m_Planes[Frustum::Side::Near].d = ToWorldMatrix[3][3] + ToWorldMatrix[2][3];
	// Far clipping plane
	m_Frustum.m_Planes[Frustum::Side::Far].a = ToWorldMatrix[3][0] - ToWorldMatrix[2][0];
	m_Frustum.m_Planes[Frustum::Side::Far].b = ToWorldMatrix[3][1] - ToWorldMatrix[2][1];
	m_Frustum.m_Planes[Frustum::Side::Far].c = ToWorldMatrix[3][2] - ToWorldMatrix[2][2];
	m_Frustum.m_Planes[Frustum::Side::Far].d = ToWorldMatrix[3][3] - ToWorldMatrix[2][3];
	// Normalize the plane equations, if requested
	if (normalize == true)
	{
		m_Frustum.m_Planes[Frustum::Side::Left].Normalize();
		m_Frustum.m_Planes[Frustum::Side::Right].Normalize();
		m_Frustum.m_Planes[Frustum::Side::Top].Normalize();
		m_Frustum.m_Planes[Frustum::Side::Bottom].Normalize();
		m_Frustum.m_Planes[Frustum::Side::Near].Normalize();
		m_Frustum.m_Planes[Frustum::Side::Far].Normalize();
	}
}