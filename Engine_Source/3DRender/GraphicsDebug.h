#pragma once


class Shaders;
enum class dbgType {
	POINT,
	LINE,
	MESH
};
class GraphicsDebug
{
	std::vector<glm::vec3> dbgPoints;
	GLuint VAO, VBO, EBO,
		ProjectionMatrixID, 
		ViewMatrixID, 
		ModelMatrixID;
	dbgType PrimType;
	Shaders* ModelShader;

public:
	GraphicsDebug() {};
	void Draw(glm::vec3&);
	GraphicsDebug(glm::vec3 &Point);
	GraphicsDebug(std::vector<glm::vec3> &Points, dbgType Type);
	
	void Draw(mat4&,mat4&,mat4&);
	~GraphicsDebug();
};

