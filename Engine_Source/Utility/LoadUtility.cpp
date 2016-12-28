#include"Engine.h"
#include"..\Utility\LoadUtility.h"

LoadUtility::LoadUtility() {  }
LoadUtility::~LoadUtility(){}


void LoadUtility::loadModel( std::vector<Mesh> &InMeshVec,const std::string &path,MeshType TextureType)
{
	std::vector<Mesh> meshes;
	std::vector<Texture> texRecord;
	std::vector<Vertex>verts;
	std::vector<GLuint>indices;
	std::vector<Texture> textures;
	Assimp::Importer importer;
	bool bNormalsLoaded = false;
	const aiScene *scene = importer.ReadFile(path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType | aiProcess_FlipUVs
	);
	
	if (!scene)
	{
		std::cout << "\nFailed to load! ";//TODO
		return;
	}
		
	for (GLuint i = 0;i <scene->mNumMeshes;++i)
	{
		aiMesh* tmpMesh = scene->mMeshes[(scene->mNumMeshes - 1) - i];
		for (int j = 0;j < tmpMesh->mNumVertices;++j)
		{
			Vertex tmpVert;
			glm::vec3 tmpPos;
			tmpPos.x = tmpMesh->mVertices[j].x;
			tmpPos.y = tmpMesh->mVertices[j].y;
			tmpPos.z = tmpMesh->mVertices[j].z;
			
			
			glm::vec3 tmpNorm;
			if (tmpMesh->HasNormals())
			{
				tmpNorm.x = tmpMesh->mNormals[j].x;
				tmpNorm.y = tmpMesh->mNormals[j].y;
				tmpNorm.z = tmpMesh->mNormals[j].z;
			}
		
			glm::vec3 tmpTang, tmpBitTang;
			if (tmpMesh->HasTangentsAndBitangents())
			{
				tmpTang.x = tmpMesh->mTangents[j].x;
				tmpTang.y = tmpMesh->mTangents[j].y;
				tmpTang.z = tmpMesh->mTangents[j].z;
				tmpBitTang.x = tmpMesh->mBitangents[j].x;
				tmpBitTang.y = tmpMesh->mBitangents[j].y;
				tmpBitTang.z = tmpMesh->mBitangents[j].z;
			}
			

			glm::vec3 tmpCol;
			aiColor3D aiCol;
			aiMaterial *tmpMat = scene->mMaterials[tmpMesh->mMaterialIndex];
			tmpMat->Get(AI_MATKEY_COLOR_DIFFUSE, aiCol);
			tmpCol.r = aiCol.r;
			tmpCol.g = aiCol.g;
			tmpCol.b = aiCol.b;

			tmpVert.Position = tmpPos;
			tmpVert.Normal = tmpNorm;
			tmpVert.diffuse = tmpCol;
			tmpVert.Tangent = tmpTang;
			tmpVert.BitTangent = tmpBitTang;

			if (tmpMesh->mTextureCoords[0] && TextureType != MeshType::SKYBOX)
			{
				tmpVert.texCoord.x = tmpMesh->mTextureCoords[0][j].x;
				tmpVert.texCoord.y = tmpMesh->mTextureCoords[0][j].y;
			}
			else 
			{
				tmpVert.texCoord.x = 0.0f;
				tmpVert.texCoord.y = 0.0f;
			}

			verts.push_back(tmpVert);

		}
		aiFace  tmpFace;
		for (int j = 0; j < tmpMesh->mNumFaces;++j)
		{
			tmpFace = tmpMesh->mFaces[j];
			for (int k = 0;k < tmpFace.mNumIndices;++k)
			{
				indices.push_back(tmpFace.mIndices[k]);
			}
		}
		if (tmpMesh->mMaterialIndex >= 0&&TextureType!=MeshType::SKYBOX)
		{
			aiMaterial* material = scene->mMaterials[tmpMesh->mMaterialIndex];
			// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
			// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
			// Same applies to other texture as the following list summarizes:
			// Diffuse: texture_diffuseN
			// Specular: texture_specularN
			// Normal: texture_normalN
			// Displacement map, heightmap, depthmap etc. 

			// 1. Diffuse maps
			std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "material.texture_diffuse",TextureType, texRecord, bNormalsLoaded);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			// 2. Specular maps
			std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "material.texture_specular", TextureType, texRecord, bNormalsLoaded);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			// 3. Normal maps ATTENTION! aiTextureType_NORMAL may work with fbx, aiTexturType_HEIGHT may be an option
			std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "material.texture_normal", TextureType, texRecord, bNormalsLoaded);
			textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
			
			bNormalsLoaded = true;
			
			// 4. Displacement maps
			//hack because blender and/or assimp does not export/import displacement maps in fbx 
			
			if (TextureType == MeshType::TEXTURE_2D_DISPLACEMENT||TextureType== MeshType::TERRAIN)
			{
				std::vector<Texture> displacementMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "material.texture_displacement", TextureType,texRecord, bNormalsLoaded);
				textures.insert(textures.end(), displacementMaps.begin(), displacementMaps.end());
			}
			
		}
		if (TextureType == MeshType::SKYBOX || TextureType == MeshType::ENVIRONMENT_MAP)
		{
			textures.clear();
			textures.push_back(Texture());
			textures[0].type = "CubeMap";
			textures[0].id = loadCubemap();
			
		}
	/*	for (int i = 0; i<textures.size();i++)
			std::cout << "\n" << textures[i].type;*/ //TODO add to event logging
		InMeshVec.push_back(Mesh(verts, indices, textures,TextureType));
		verts.clear();
		indices.clear();
		textures.clear();
	}
}
std::vector<Texture> LoadUtility::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, MeshType TextureType, std::vector<Texture> &texRecord, bool bNormalsLoaded)
{
	std::vector<Texture> textures;
	
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		
		mat->GetTexture(type, i, &str);
		std::string tmpTexPath = str.C_Str();
		
		// Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		//Hack for displacement maps continues, normalmap must have "_n" at end of name, and displacement map must be the same name with
		// "_d" at the end of filename
		if ((TextureType == MeshType::TEXTURE_2D_DISPLACEMENT || TextureType == MeshType::TERRAIN) && bNormalsLoaded)
		{
			std::string key("_n");
			std::size_t found = tmpTexPath.rfind(key);
			if (found != std::string::npos)
				tmpTexPath.replace(found, key.length(), "_d");
			typeName = "material.texture_displacement";
			
		}
		GLboolean skip = false;
		for (GLuint j = 0; j < texRecord.size(); j++)
		{
			if (texRecord[j].texPath == tmpTexPath)
			{
				textures.push_back(texRecord[j]);
				skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // If texture hasn't been loaded already, load it
			Texture texture;
			texture.id = TextureFromFile(tmpTexPath);
			texture.type = typeName;
			texture.texPath = tmpTexPath;
			textures.push_back(texture);
			texRecord.push_back(texture);  // Store it as texture loaded for entire model, to ensure we won't unnecessarily load duplicate textures.
		}
	}
	return textures;
}
GLint LoadUtility::TextureFromFile(std::string texpath) //TODO Add exception for loading wrong resolutions 
{
	
	std::size_t found = texpath.find_last_of("/\\");
	std::string FileName = texpath.substr(found + 1);
	
	//Generate texture ID and load texture data 
	GLuint TexID;
	glGenTextures(1, &TexID);
	int width, height;
	FileName = "../media/" + FileName;
	unsigned char* image = SOIL_load_image(FileName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, TexID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	
	//std::cout << "\nTexture Loaded: " + FileName; add to event logging
	SOIL_free_image_data(image);
	
	return TexID;
}
GLuint LoadUtility::loadCubemap()
{
	GLuint TexID;
	glGenTextures(1, &TexID);
	glActiveTexture(GL_TEXTURE0);

	std::vector<const GLchar*> faces;
	faces.push_back("../media/right.jpg");
	faces.push_back("../media/left.jpg");
	faces.push_back("../media/top.jpg");
	faces.push_back("../media/bottom.jpg");
	faces.push_back("../media/back.jpg");
	faces.push_back("../media/front.jpg");
	
	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, TexID);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
		);
	
		SOIL_free_image_data(image);
		
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return TexID;
}
//Returns height values in multi dimesional vector/array for application access to terrain height, slows load time
void LoadUtility::loadHeightMap(std::string Path, int &Width, int &Height, std::vector< std::vector<GLfloat> > &InVec)
{
	unsigned char* image = nullptr;
	
	image = SOIL_load_image(Path.c_str(), &Width, &Height, 0, SOIL_LOAD_RGB);
	
	if (!image)
	{
		//std::cout << "'\nFailed to load heightmap pixel data.";//TODO Add to logging
	}
	else {
		InVec = std::vector< std::vector<GLfloat> >(Width, std::vector<GLfloat>(Height));
		GLuint k = 0;
		for (GLuint i = 0; i < Width; i++) {
			for (GLuint j = 0; j < Height; j++) {

				InVec[j][i] = (GLdouble)image[k * 3] / 255;
				k++;
			}
		}
		SOIL_free_image_data(image);
	}
}
//Returns raw pixel image for application acess to height values
unsigned char* LoadUtility::loadHeightMap(std::string Path, int &Width, int &Height) {
	unsigned char* image = nullptr;
	GLuint k = 0;
	image = SOIL_load_image(Path.c_str(), &Width, &Height, 0, SOIL_LOAD_RGB);
	if (!image)
	{
		//std::cout << "'\nFailed to load heightmap pixel data.";//TODO Add to logging
		return nullptr;
	}
	return image;
}
//Loads vertex data for collision detection and for collider box debug rendering
void LoadUtility::LoadCollider(const std::string &path, std::vector<glm::vec3> &InVerts, std::vector<GLuint> &InIndices, std::vector<glm::vec3> &InRenderVerts) {

	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path,0);
	if (!scene)
	{
		//std::cout << "\nFile " << path << " Not found.";//TODO Add to logging
		return;
	}
	std::map<aiVector3D, int>VertMap;
	aiMesh* tmpMesh = scene->mMeshes[0];
	
	for (int j = 0;j < tmpMesh->mNumVertices;++j)
	{
		glm::vec3 tmpPos;
		tmpPos.x = tmpMesh->mVertices[j].x;
		tmpPos.y = tmpMesh->mVertices[j].y;
		tmpPos.z = tmpMesh->mVertices[j].z;
			InRenderVerts.push_back(tmpPos);
	}
	aiFace  tmpFace;
	for (int j = 0; j < tmpMesh->mNumFaces;++j)
	{
		tmpFace = tmpMesh->mFaces[j];
		for (int k = 0;k < tmpFace.mNumIndices;++k)
		{
			InIndices.push_back(tmpFace.mIndices[k]);
		}
	}
	// using map to weed out duplicates
	for (int j = 0;j < tmpMesh->mNumVertices;++j)
	{
		VertMap[tmpMesh->mVertices[j]] = j;
	}
	typedef std::map<aiVector3D, int>::iterator it_type;

	for (it_type iterator = VertMap.begin(); iterator != VertMap.end(); iterator++)
	{
		//std::map cannot sort glm::vec3, leave it in assimp's vector3D and convert here
		glm::vec3 tmpPos;
		tmpPos.x = iterator->first.x;
		tmpPos.y = iterator->first.y;
		tmpPos.z = iterator->first.z;
		InVerts.push_back(tmpPos);
	}
	//std::cout << "\inverts size: " << InVerts.size();//TODO Add to logging
}
