#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include "PBRMesh.h"

enum Passes{ Deferred, LightPass, TotalPasses };

//Shader compilation
GLuint vs[TotalPasses];
GLuint fs[TotalPasses];
GLuint ps[TotalPasses];

//Normal Uniforms
mat4 view;
mat4 projection;
mat4 model = mat4(1.0f);

GLuint modelLocation;
GLuint viewLocation;
GLuint projLocation;
GLuint textureLocation;

//Window variables 
unsigned int windowHeight;
unsigned int windowWidth;

//Ubo
GLuint ubo;
GLuint uboIndex;

struct LightProperties
{
	vec4 lightPos_ = vec4(1.0f);
	vec4 lightParams_ = vec4(1.0f);
	vec4 lightIntensityParams_ = vec4(1.0f);
	vec4 lightDir_ = vec4(1.0f);
	vec4 lightColor_ = vec4(1.0f);
};

//Mesh
Mesh* sphere;
Mesh* quad;
Texture* groundTexture;

// All GBuffer Related Data
enum GBUFFER_TEXTURES
{
	POSITION_TEXTURE,
	DIFFUSE_TEXTURE,
	NORMAL_TEXTURE,
	TEXCOORD_TEXTURE,
	NUM_GBUFFER_TEXTURES
};

GLuint g_textures[NUM_GBUFFER_TEXTURES];
GLuint g_fbo;
GLuint g_depthTexture;
GLuint mapLocations[NUM_GBUFFER_TEXTURES];

//Full quad pass
GLuint quadVAO;
GLuint quadVBO;
GLuint quadIBO;

GLfloat quadVertices[] = {
	1.0f,  -1.0f,  0.0f,
	1.0f, 1.0f, 0.0f ,
	-1.0f, -1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f
};

const GLushort quadIndices[] =
{
	0,1,2,2,3,1
};
