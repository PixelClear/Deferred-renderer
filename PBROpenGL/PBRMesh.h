#pragma once
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <cassert>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "PBRTexture.h"

#define PI 3.14159265f
#define INVALID_UNIFORM_LOCATION 0xffffffff
#define INVALID_OGL_VALUE 0xffffffff

//Maths
using vec2 = glm::vec2;
using vec3 = glm::vec3;
using vec4 = glm::vec4;
using mat4 = glm::mat4;
using mat3 = glm::mat3;

struct Vertex
{
	vec3 m_pos;
	vec2 m_tex;
	vec3 m_normal;

	Vertex() {}

	Vertex(const vec3& pos, const vec2& tex, const vec3& normal)
	{
		m_pos = pos;
		m_tex = tex;
		m_normal = normal;

	}
};

class Mesh
{
public:
	struct MeshEntry;

	Mesh();

	~Mesh();

	bool LoadMesh(const std::string& fileName);

	void Render();
	void Render(MeshEntry& m);

private:

	bool InitFromScene(const aiScene* pScene, const std::string& fileName);
	void InitMesh(unsigned int Index, const aiMesh* pMesh);
	bool InitMaterials(const aiScene* pScene, const std::string& fileName);
	void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF

	struct MeshEntry
	{
		MeshEntry();
		~MeshEntry();

		bool Init(const std::vector<Vertex>& Vertices, const std::vector<unsigned int>& Indices);

		uint32_t VB;
		uint32_t IB;
		unsigned int NumIndices;
		unsigned int MaterialIndex;
	};

public:

	std::vector<MeshEntry> m_Entries;
	std::vector<Texture*> m_textures;
};
