#include "PBRMesh.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
	Clear();
}

Mesh::MeshEntry::MeshEntry()
{
	VB = INVALID_OGL_VALUE;
	IB = INVALID_OGL_VALUE;
	NumIndices = 0;
	MaterialIndex = INVALID_MATERIAL;
}

Mesh::MeshEntry::~MeshEntry()
{
	if (VB != INVALID_OGL_VALUE)
	{
		glDeleteBuffers(1, &VB);
	}

	if (IB != INVALID_OGL_VALUE)
	{
		glDeleteBuffers(1, &IB);
	}
}

bool Mesh::MeshEntry::Init(const std::vector<Vertex>& Vertices, const std::vector<unsigned int>& Indices)
{
	NumIndices = Indices.size();

	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NumIndices, &Indices[0], GL_STATIC_DRAW);

	return true;
}

bool Mesh::LoadMesh(const std::string& fileName)
{
	//Release previously loaded mesh 
	Clear();
	bool ret = false;
	Assimp::Importer Importer;

	const aiScene* pScene = Importer.ReadFile(fileName.c_str(), aiProcess_Triangulate |
		aiProcess_GenSmoothNormals |
		aiProcess_FlipUVs);

	if (pScene)
	{
		ret = InitFromScene(pScene, fileName);
	}
	else
	{
	 std::cout << "Error parsing'%s' : '%s' \n" << fileName.c_str() << Importer.GetErrorString() << "\n";
	}

	return ret;
}

void Mesh::Render(MeshEntry& m)
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, m.VB);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.IB);

	const unsigned int MaterialIndex = m.MaterialIndex;

	if (MaterialIndex < m_textures.size() && m_textures[MaterialIndex]) {
		m_textures[MaterialIndex]->Bind(GL_TEXTURE0);
	}

	glDrawElements(GL_TRIANGLES, m.NumIndices, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Mesh::Render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	for (unsigned int i = 0; i < m_Entries.size(); i++) {
		glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);

		const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

		if (MaterialIndex < m_textures.size() && m_textures[MaterialIndex]) {
			m_textures[MaterialIndex]->Bind(GL_TEXTURE0);
		}

		glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

bool Mesh::InitFromScene(const aiScene* pScene, const std::string& fileName)
{
	m_Entries.resize(pScene->mNumMeshes);
	m_textures.resize(pScene->mNumMaterials);

	//Initialize the mesh in scene
	for (unsigned int i = 0; i < m_Entries.size(); i++)
	{
		const aiMesh* paiMesh = pScene->mMeshes[i];
		InitMesh(i, paiMesh);
	}

	return InitMaterials(pScene, fileName);
}

void Mesh::InitMesh(unsigned int Index, const aiMesh* pMesh)
{
	m_Entries[Index].MaterialIndex = pMesh->mMaterialIndex;

	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;

	const aiVector3D Zero3D(0.0, 0.0, 0.0);

	for (unsigned int i = 0; i < pMesh->mNumVertices; i++)
	{
		const aiVector3D* pPos = &(pMesh->mVertices[i]);
		const aiVector3D* pNormal = &(pMesh->mNormals[i]);
		const aiVector3D* pTexCoord = pMesh->HasTextureCoords(0) ? &(pMesh->mTextureCoords[0][i]) : &Zero3D;
		const aiVector3D* pTangent = &(pMesh->mTangents[i]);

		Vertex v(vec3(pPos->x, pPos->y, pPos->z),
			vec2(pTexCoord->x, pTexCoord->y),
			vec3(pNormal->x, pNormal->y, pNormal->z));

		Vertices.push_back(v);
	}

	for (unsigned int i = 0; i < pMesh->mNumFaces; i++)
	{
		const aiFace& Face = pMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		Indices.push_back(Face.mIndices[0]);
		Indices.push_back(Face.mIndices[1]);
		Indices.push_back(Face.mIndices[2]);

	}

	m_Entries[Index].Init(Vertices, Indices);
}

bool Mesh::InitMaterials(const aiScene* pScene, const std::string& fileName)
{
	std::string::size_type SlashIndex = fileName.find_last_of("/");
	std::string Dir;

	if (SlashIndex == std::string::npos)
	{
		Dir = ".";
	}
	else if (SlashIndex == 0)
	{
		Dir = "/";
	}
	else
	{
		Dir = fileName.substr(0, SlashIndex);
	}

	bool ret = true;

	for (unsigned int i = 0; i < pScene->mNumMaterials; i++)
	{
		const aiMaterial* pMaterial = pScene->mMaterials[i];
		m_textures[i] = NULL;

		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString Path;
			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				std::string fullPath = Dir + "/" + Path.data;
				m_textures[i] = new Texture(GL_TEXTURE_2D, fullPath.c_str());

				if (!m_textures[i]->Load())
				{
					std::cout << "Error Loading texure '%s' \n" << fullPath.c_str() << "\n";
					delete m_textures[i];
					m_textures[i] = nullptr;
					ret = false;
				}
				else
				{
					std::cout << "Loaded Texture '%s'" << fullPath.c_str() << "\n";
					ret = true;
				}
			}
		}

	}

	return ret;
}

void Mesh::Clear()
{
	for (unsigned int i = 0; i < m_textures.size(); i++) {
		delete m_textures[i];
		m_textures[i] = nullptr;
	}
}