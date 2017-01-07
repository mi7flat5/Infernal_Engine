#pragma once

#define VECCONSOLEOUT(X,STRING) std::cout<<" "<<STRING<<X.x<<", "<<X.y<<", "<<X.z;
//Shader selector for Model/Mesh

enum class MeshType {
	NO_TEXTURE,
	TEXTURE_2D,
	TEXTURE_2D_DISPLACEMENT,
	TEXTURE_2D_REFRACT,
	TEXTURE_2D_REFLECT,
	ENVIRONMENT_MAP,
	SKYBOX,
	TERRAIN
};
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 diffuse;
	glm::vec2 texCoord;
	glm::vec3 Tangent;
	glm::vec3 BitTangent;
};

struct Texture {
	GLuint id;
	std::string type;
	std::string texPath;

};
class Mesh
{

	std::vector<Vertex>verts;
	std::vector<GLuint>indices;
	std::vector<Texture>textures;
	mat4 Model;
	GLint ShaderMode;
	GLuint VAO, VBO, EBO, ModelLoc, ShaderModeLocation, ShaderID;
	void setupMesh();
	void SetupCubemap();

	void DrawCubeMap()const;
	void DrawTessellated()const;
	void DrawTerrain()const;
	void DrawTexture()const;

	void UpdateTextures()const;

	void UnbindTextures() const;
	void DrawMesh() const;
	void SetTextureMode();
	MeshType MeshMaterial;

	void SetMode(int);

public:
	Mesh(const std::vector<Vertex> &inVerts,
		const std::vector<GLuint> &inIndice,
		const std::vector<Texture> &inTextures,
		MeshType
		);
	~Mesh();
	void SetShader(GLuint);
	void CleanUp();
	void DrawMesh(MeshType) const;

};

