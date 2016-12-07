#ifndef MESH_H
#define MESH_H

#define VECCONSOLEOUT(X,STRING) std::cout<<'\n'<<STRING<<X.x<<", "<<X.y<<", "<<X.z;
//Shader selector for Model/Mesh
//TEXTURE_2D_HIDDEN_REFLECT is for reflection of undisplayed skybox
// NO_TEXTURE is for model without texture coorinates, extracts diffuse from mesh
//TEXTURE_3D is for Skybox cubemaps
enum class MeshType {
	NO_TEXTURE,
	TEXTURE_2D,
	TEXTURE_2D_DISPLACEMENT,
	TEXTURE_2D_REFRACT,
	TEXTURE_2D_REFLECT,
	TEXTURE_2D_HIDDEN_REFLECT,
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
public:
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
	void SetShader(GLuint);
	Mesh(const std::vector<Vertex> &inVerts,
		const std::vector<GLuint> &inIndice,
		const std::vector<Texture> &inTextures,
		MeshType
		);
	~Mesh();

	void DrawMesh(GLuint, MeshType) const;

};
#endif // !MESH_H
