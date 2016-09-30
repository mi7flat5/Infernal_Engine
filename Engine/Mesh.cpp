#include"Engine.h"
#include"Mesh.h"

void Mesh::SetMode(int in)
{
	ShaderMode = in;
	std::cout << "'\nShaderMode changed to: " << ShaderMode;
}
Mesh::Mesh(const std::vector<Vertex> &inVerts, const std::vector<GLuint> &inIndice, const std::vector<Texture> &inTextures, MeshType Mat)
{
	this->verts = inVerts;
	this->indices = inIndice;
	this->textures = inTextures;
	MeshMaterial = Mat;
	setupMesh();
}
Mesh::~Mesh() {  }
void Mesh::setupMesh()
{
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	//Vertex data is supplied explicitly in the vertex shader for TERRAIN
	if (MeshMaterial != MeshType::TERRAIN)
	{
		glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), &verts[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,
			3,                  // Components
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),     // stride
			(void*)0);			//Pointer offset


		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);//indices
		glVertexAttribPointer(1, 3, GL_UNSIGNED_INT, GL_FALSE, 0, (GLvoid*)0);
	}

	switch (MeshMaterial)
	{
	case (MeshType::SKYBOX) :
		//For cubemap, only needs vertices and index data, set up already. 
		break;
	case (MeshType::ENVIRONMENT_MAP) :
		break;
	case(MeshType::TERRAIN) :
		//All necessary data is supplied or calulated in shaders
		break;
	case (MeshType::TEXTURE_2D_REFLECT) :
		//Normals
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
		break;
	case (MeshType::TEXTURE_2D_REFRACT) :
		//Normals
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
		break;
	case (MeshType::NO_TEXTURE) :
		//Normals
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
		// Diffuse material color for non textured meshes.
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, diffuse));
		break;
	default:
		SetTextureMode();//sets The int ShaderMode for vertex and fragment texture shader logic
						 //Normals
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
		//Texture coordinates
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));
		//Tangents
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Tangent));
		//BitTangents
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, BitTangent));
		break;
	}

	glBindVertexArray(0);
}

void Mesh::DrawMesh(GLuint ShaderID, MeshType TexType) const
{

	glBindVertexArray(this->VAO);
	switch (MeshMaterial)
	{
	case (MeshType::TEXTURE_2D) :
		DrawTexture();
		break;
	case (MeshType::TERRAIN) :
		DrawTerrain();
		break;
	case (MeshType::TEXTURE_2D_DISPLACEMENT) :
		DrawTessellated();
		break;
	case (MeshType::SKYBOX) :
		DrawCubeMap();
		
		break;
	case (MeshType::ENVIRONMENT_MAP) :
		//Does not draw, only for reflective environment mapping
		break;
	default:
		DrawMesh();
		break;
	}
	glBindVertexArray(0);
}
//Used for non textured meshs
void Mesh::DrawMesh() const
{
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
}
void Mesh::DrawCubeMap() const
{
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textures[0].id);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_3D, 0);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
}
void Mesh::DrawTessellated() const
{
	UpdateTextures();
	glPatchParameteri(GL_PATCH_VERTICES, 3);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_PATCHES, this->indices.size(), GL_UNSIGNED_INT, 0);//glDrawArraysInstanced(GL_PATCHES, 0, 4, 64 * 64);
																		 //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	UnbindTextures();
}
void Mesh::DrawTerrain()const
{
	UpdateTextures();
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArraysInstanced(GL_PATCHES, 0, 4, 64 * 64);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	UnbindTextures();
}
void Mesh::DrawTexture() const
{
	UpdateTextures();
	glUniform1i(glGetUniformLocation(ShaderID, "Mode"), ShaderMode);//TODO remove, testing only, causes instability

	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);

	UnbindTextures();
}

void Mesh::UpdateTextures() const
{
	// Bind appropriate textures
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	GLuint normalNr = 1;
	GLuint displaceMap = 1;
	for (GLuint i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
										  // Retrieve texture number (the N in diffuse_textureN)
		std::stringstream ss;
		std::string number;
		std::string name = this->textures[i].type;
		if (name == "material.texture_diffuse")
			ss << diffuseNr++; // Transfer GLuint to stream
		else if (name == "material.texture_specular")
			ss << specularNr++;
		else if (name == "material.texture_normal")
			ss << normalNr++;
		else if (name == "material.texture_displacement")
			ss << displaceMap++;

		number = ss.str();

		// Now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(ShaderID, (name + number).c_str()), i);
		// And finally bind the texture
		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
	}
}
void Mesh::UnbindTextures()const
{
	for (GLuint i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
void Mesh::SetShader(GLuint InShaderID)
{
	ShaderID = InShaderID;
}
void Mesh::SetTextureMode()
{
	ShaderMode = -1;
	GLuint diff = 0, spec = 0, norm = 0, disp = 0;
	for (GLuint i = 0; i < textures.size();i++)
	{
		if (textures[i].type == "material.texture_diffuse")
			diff++;
		if (textures[i].type == "material.texture_specular")
			spec++;
		if (textures[i].type == "material.texture_normal")
			norm++;
		if (textures[i].type == "material.texture_displacement")
			disp++;

	}
	if (diff > 0 && spec == 0 && norm == 0 && disp == 0)
		ShaderMode = 0;
	if (diff > 0 && spec > 0 && norm == 0 && disp == 0)
		ShaderMode = 1;
	if (diff > 0 && spec == 0 && norm > 0 && disp == 0)
		ShaderMode = 2;
	if (diff > 0 && spec > 0 && norm > 0 && disp == 0)
		ShaderMode = 3;
	if (diff > 0 && spec == 0 && norm == 0 && disp > 0)
		ShaderMode = 4;
	if (diff > 0 && spec > 0 && norm == 0 && disp > 0)
		ShaderMode = 5;
	if (diff > 0 && spec == 0 && norm > 0 && disp > 0)
		ShaderMode = 6;
	if ((diff > 0) && (spec > 0) && (norm > 0) && (disp >0))
		ShaderMode = 7;
	std::cout << "\nShader Mode: " << ShaderMode;
}