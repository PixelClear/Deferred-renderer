#include "PBROpenGL.h"

//#define _DebugDeferred 1

float camera = 0.0f;

double RangedRand(double range_min, double range_max)
{
	double u = (double)rand() / (RAND_MAX + 1) * (range_max - range_min)
		+ range_min;
	return u;
}

void getLightStruct(std::vector<LightProperties>& l)
{
	float x = -100.0f;
	float y = -300.0f;
	float z = -1700.0f;
	float offset = 0.0f;
	float radius = 350.0f;

	for (int i = 0; i < 4; i++)
	{
		LightProperties lp;
		lp.lightColor_ = vec4(RangedRand(0.0f, 1.0f), RangedRand(0.0f, 1.0f), RangedRand(0.0f, 1.0f), 1.0f);
		lp.lightPos_ = vec4(400.0, -300.0f, -1700.0f + offset, 0.0f);
		lp.lightDir_ = vec4(0.0f, -1.0f, 0.0f, 0.0f);
		lp.lightParams_ = vec4(radius, 0.0f, 0.0f, 1.0f);
		lp.lightIntensityParams_ = vec4(0.9f, 0.0f, 0.0f, 0.0f);

		l.push_back(lp);
		if (i == 0)offset += 400.0f;
		if (i == 1)offset += 350.0f;
		if (i == 2)offset += 300.0f;
		if (i == 3)offset += 250.0f;
	}

	offset = 0.0f;
	for (int i = 0; i < 4; i++)
	{
		LightProperties lp;
		lp.lightColor_ = vec4(RangedRand(0.0f, 1.0f), RangedRand(0.0f, 1.0f), RangedRand(0.0f, 1.0f), 1.0f);
		lp.lightPos_ = vec4(-270.0, -300.0f, -1700.0f + offset, 0.0f);
		lp.lightDir_ = vec4(0.0f, -1.0f, 0.0f, 0.0f);
		lp.lightParams_ = vec4(radius, 0.0f, 0.0f, 1.0f);
		lp.lightIntensityParams_ = vec4(0.9f, 0.0f, 0.0f, 0.0f);

		l.push_back(lp);
		if (i == 0)offset += 400.0f;
		if (i == 1)offset += 350.0f;
		if (i == 2)offset += 300.0f;
		if (i == 3)offset += 250.0f;
	}

	offset = 0.0f;
	for (int i = 0; i < 4; i++)
	{
		LightProperties lp;
		lp.lightColor_ = vec4(RangedRand(0.0f, 1.0f), RangedRand(0.0f, 1.0f), RangedRand(0.0f, 1.0f), 1.0f);
		lp.lightPos_ = vec4(-50.0f, -300.0f, -1700.0f + offset, 0.0f);
		lp.lightDir_ = vec4(0.0f, -1.0f, 0.0f, 0.0f);
		lp.lightParams_ = vec4(radius, 0.0f, 0.0f, 1.0f);
		lp.lightIntensityParams_ = vec4(0.9f, 0.0f, 0.0f, 0.0f);

		l.push_back(lp);
		if (i == 0)offset += 400.0f;
		if (i == 1)offset += 350.0f;
		if (i == 2)offset += 300.0f;
		if (i == 3)offset += 250.0f;
	}

	offset = 0.0f;
	for (int i = 0; i < 4; i++)
	{
		LightProperties lp;
		lp.lightColor_ = vec4(RangedRand(0.0f, 1.0f), RangedRand(0.0f, 1.0f), RangedRand(0.0f, 1.0f), 1.0f);
		lp.lightPos_ = vec4(-500.0, -900.0f, -1700.0f + offset, 0.0f);
		lp.lightDir_ = vec4(0.0f, -1.0f, 0.0f, 0.0f);
		lp.lightParams_ = vec4(1000.0f, 0.0f, 0.0f, 1.0f);
		lp.lightIntensityParams_ = vec4(0.9f, 0.0f, 0.0f, 0.0f);

		l.push_back(lp);
		if (i == 0)offset += 400.0f;
		if (i == 1)offset += 350.0f;
		if (i == 2)offset += 300.0f;
		if (i == 3)offset += 250.0f;
	}

	offset = 0.0f;
	for (int i = 0; i < 4; i++)
	{
		LightProperties lp;
		lp.lightColor_ = vec4(RangedRand(0.0f, 1.0f), RangedRand(0.0f, 1.0f), RangedRand(0.0f, 1.0f), 1.0f);
		lp.lightPos_ = vec4(-50.0, -3000.0f, -1700.0f + offset, 0.0f);
		lp.lightDir_ = vec4(1.0f, 0.0f, 0.0f, 0.0f);
		lp.lightParams_ = vec4(3500.0f, 0.0f, 0.0f, 1.0f);
		lp.lightIntensityParams_ = vec4(0.9f, 0.0f, 0.0f, 0.0f);

		l.push_back(lp);
		if (i == 0)offset += 400.0f;
		if (i == 1)offset += 350.0f;
		if (i == 2)offset += 300.0f;
		if (i == 3)offset += 250.0f;
	}
}

void PrepareFullQuadVAO()
{
	glGenVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);

	glGenBuffers(1, &quadIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

	glGenBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

bool prepareGBuffer()
{
	glGenFramebuffers(1, &g_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, g_fbo);

	glGenTextures(NUM_GBUFFER_TEXTURES, g_textures);
	glGenTextures(1, &g_depthTexture);

	for (unsigned int i = 0; i< NUM_GBUFFER_TEXTURES; i++)
	{
		glBindTexture(GL_TEXTURE_2D, g_textures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, windowWidth, windowHeight, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, g_textures[i], 0);
	}

	glBindTexture(GL_TEXTURE_2D, g_depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, windowWidth, windowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, g_depthTexture, 0);

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1,GL_COLOR_ATTACHMENT2,GL_COLOR_ATTACHMENT3 };

	glDrawBuffers(4, DrawBuffers);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "FB Error\n";
		return false;
	}

	glBindFramebuffer(GL_DRAW_BUFFER, 0);
	return true;
}

bool initLightUBO()
{
	GLint uboAlignment_;
	std::vector<LightProperties> lp;
    getLightStruct(lp);

	
	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(LightProperties) * lp.size(),lp.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	return true;
}

bool bindUboIndex(GLuint ps)
{
	uboIndex = glGetUniformBlockIndex(ps, "Light");

	if (uboIndex != GL_INVALID_INDEX)
	{
		glUniformBlockBinding(ps, uboIndex, 0);
		return true;
	}

	return false;
}

void bindUbo()
{
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);
}

bool initScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	sphere = new Mesh();
	quad = new Mesh();
	groundTexture = new Texture(GL_TEXTURE_2D, "../../ThirdParty/Content/test1.jpg");

	if (!groundTexture->Load())
	{
		std::cerr << " Unable to load texture \n";
		return false;
	}

	if (!sphere->LoadMesh("../../ThirdParty/Content/sphere.obj"))
	{
		std::cerr << " Unable to load Sphere \n";
		return false;
	}

	if (!quad->LoadMesh("../../ThirdParty/Content/crytek_sponza/sponza.obj"))
	{
		return false;
		std::cerr << " Unable to load quad \n";
	}

	return true;
}

bool readFile(const char* pFileName, std::string& outFile)
{
	std::ifstream f(pFileName);

	bool ret = false;

	if (f.is_open()) {
		std::string line;
		while (getline(f, line)) {
			outFile.append(line);
			outFile.append("\n");
		}

		f.close();

		ret = true;
	}
	else {
		std::cout << "Error Loading file";
	}

	return ret;
}

bool prepareShaders(const std::string& v, const std::string& f, Passes pass)
{
	GLint success;
	std::string vShaderSource{};
	std::string fShaderSource{};

	readFile(v.c_str(), vShaderSource);
	readFile(f.c_str(), fShaderSource);

	const char* vString[1];
	vString[0] = vShaderSource.c_str();

	vs[pass] = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs[pass], 1, vString, NULL);
	glCompileShader(vs[pass]);

	glGetShaderiv(vs[pass], GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char info[1024];
		glGetShaderInfoLog(vs[pass], 1024, NULL, info);
		std::cerr << std::string{ info };
		return false;
	}

	const char* fString[1];
	fString[0] = fShaderSource.c_str();

	fs[pass] = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs[pass], 1, fString, NULL);
	glCompileShader(fs[pass]);
	glGetShaderiv(fs[pass], GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char info[1024];
		glGetShaderInfoLog(fs[pass], 1024, NULL, info);
		std::cerr << std::string{ info };
		return false;
	}

	ps[pass] = glCreateProgram();
	glAttachShader(ps[pass], vs[pass]);
	glAttachShader(ps[pass], fs[pass]);
	glLinkProgram(ps[pass]);
	glGetProgramiv(ps[pass], GL_LINK_STATUS, &success);

	if (!success) {
		char InfoLog[1024];
		glGetShaderInfoLog(ps[pass], 1024, NULL, InfoLog);
		fprintf(stderr, "Error linking : '%s'\n", InfoLog);
		return false;
	}

	glUseProgram(ps[pass]);

	if (pass == Passes::Deferred)
	{
		modelLocation = glGetUniformLocation(ps[pass], "u_Model");
		viewLocation = glGetUniformLocation(ps[pass], "u_View");
		projLocation = glGetUniformLocation(ps[pass], "u_Projection");
		textureLocation = glGetUniformLocation(ps[pass], "gSampler");

		if (modelLocation == INVALID_UNIFORM_LOCATION ||
			viewLocation == INVALID_UNIFORM_LOCATION ||
			projLocation == INVALID_UNIFORM_LOCATION ||
			textureLocation == INVALID_UNIFORM_LOCATION)
			return false;
	}

	if (pass == Passes::LightPass)
	{
		initLightUBO();
		bindUboIndex(ps[pass]);

		mapLocations[POSITION_TEXTURE] = glGetUniformLocation(ps[pass], "u_PositionMap");
		mapLocations[DIFFUSE_TEXTURE] = glGetUniformLocation(ps[pass], "u_ColorMap");
		mapLocations[NORMAL_TEXTURE] = glGetUniformLocation(ps[pass], "u_NormalMap");
		mapLocations[TEXCOORD_TEXTURE] = glGetUniformLocation(ps[pass], "u_TextureCoordMap");

	}

	glDetachShader(ps[pass], vs[pass]);
	glDetachShader(ps[pass], fs[pass]);
	glUseProgram(0);
	return true;
}

bool loadShaders()
{
	if (!prepareShaders("Deferred.vs", "Deferred.ps", Passes::Deferred))
	{
		std::cerr << "Error Loading Deferred Shaders!!!\n";
		return false;
	}

	if (!prepareShaders("Light.vs", "Light.ps", Passes::LightPass))
	{
		std::cerr << "Error Loading LightPass shaders!!!\n";
		return false;
	}
	return true;
}

void debugDeferredPass()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);


	glBindFramebuffer(GL_READ_FRAMEBUFFER, g_fbo);

	GLsizei halfWidth = static_cast<GLsizei>(windowWidth / 2.0f);
	GLsizei halfheight = static_cast<GLsizei>(windowHeight / 2.0f);

	/*Draw Position texture*/
	glReadBuffer(GL_COLOR_ATTACHMENT0 + POSITION_TEXTURE);
	glBlitFramebuffer(0, 0, windowWidth, windowHeight, 0, 0, halfWidth, halfheight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	glReadBuffer(GL_COLOR_ATTACHMENT0 + DIFFUSE_TEXTURE);
	glBlitFramebuffer(0, 0, windowWidth, windowHeight, 0, halfheight, halfWidth, windowHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	glReadBuffer(GL_COLOR_ATTACHMENT0 + NORMAL_TEXTURE);
	glBlitFramebuffer(0, 0, windowWidth, windowHeight, halfWidth, halfheight, windowWidth, windowHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	glReadBuffer(GL_COLOR_ATTACHMENT0 + TEXCOORD_TEXTURE);
	glBlitFramebuffer(0, 0, windowWidth, windowHeight, halfWidth, 0, windowWidth, halfheight, GL_COLOR_BUFFER_BIT, GL_LINEAR);


	glEnable(GL_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void renderDeferredPass(int i)
{
	glUseProgram(ps[Passes::Deferred]);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, g_fbo);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	//mat4 model = glm::scale(mat4(1.0f), vec3(3.1f, 3.1f, 3.1f));
    model = glm::translate(mat4(1.0f), vec3(-150.0f, -600.0f, -800.0f+camera));
	model = glm::rotate(model, 30.0f, vec3(0.0f, 1.0f, 0.0f));

	mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, -5.0), glm::vec3(0.0, 1.0, 0.0));

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);
	glUniform1i(textureLocation, 0);
	
    quad->Render();

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glUseProgram(0);
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
}

void renderLightPass()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	glUseProgram(ps[Passes::LightPass]);
	glBindVertexArray(quadVAO);
	bindUbo();
	
	for (unsigned int i = 0; i < NUM_GBUFFER_TEXTURES; i++) {
		glActiveTexture(GL_TEXTURE1 + i);
		glBindTexture(GL_TEXTURE_2D, g_textures[POSITION_TEXTURE + i]);
	}


	glUniform1i(mapLocations[POSITION_TEXTURE], 1);
	glUniform1i(mapLocations[DIFFUSE_TEXTURE], 2);
	glUniform1i(mapLocations[NORMAL_TEXTURE], 3);
	glUniform1i(mapLocations[TEXCOORD_TEXTURE], 4);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	glUseProgram(0);
	glBindVertexArray(0);
	
	glEnable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glGenerateMipmap(GL_TEXTURE_2D);
	glEnable(GL_MULTISAMPLE);

	//for (int i = 0; i < quad->m_Entries.size(); i++)
	{

		renderDeferredPass(0);

#ifdef _DebugDeferred
		debugDeferredPass();
#else
		renderLightPass();
#endif
	}

	glutSwapBuffers();
	glutPostRedisplay();
}

void changeSize(int w, int h)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, w, h);
	projection = glm::perspective(45.0f, w / (float)h, 0.1f, 10000.0f);
	windowWidth = w;
	windowHeight = h;
}

void key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'z':
		camera -= 1.1;
		break;
	case 'a':
		camera += 1.1;
		break;
	case 'r':
		break;
	case 'w':
		break;
	}
}

void clear()
{

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE);
	windowWidth = 1350;
	windowHeight = 700;
	glutInitWindowPosition(0, 0);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("TeslaTessellate");

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		std::cout << "Error: '%s'\n" << glewGetErrorString(res);
		return false;
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutReshapeFunc(changeSize);

	//Set initial state and load models
	if (!initScene())
		return -1;
	
	//Load shaders
	if (!loadShaders())
		return -1;

	//Prepare Gbuffer
	if (!prepareGBuffer())
		return -1;

	PrepareFullQuadVAO();

	glutMainLoop();

	clear();
	return 0;
}