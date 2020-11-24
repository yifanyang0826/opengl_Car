//
// COMP 371 Labs Framework
//
// Created by Nicolas Bergeron on 20/06/2019.
//
#include <algorithm>
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler
#include <GL/GLU.h> 
#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
						// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>

#include <irrKlang.h>
#include <FreeImageIO.h>
#include "shader_m.h"
#include "model.h"

#define PI 3.1415927
using namespace glm;
using namespace std;
using namespace irrklang;

using namespace std::filesystem;

float RandomNumber(float Min, float Max)
{
	return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}



struct TexturedColoredVertex
{
	TexturedColoredVertex(vec3 _position,vec3 _normal, vec2 _uv)
		: position(_position),normal(_normal), uv(_uv) {}

	vec3 position;
	vec3 normal;
	vec2 uv;
};



	int createTexturedCubeVertexBufferObject()
{
	vector<TexturedColoredVertex> texturedCubeVertexArray =
	{
	  TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f),vec3(-1.0f,0.0f,0.0f), vec2(0.0f, 0.0f)), //left
	  TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f),vec3(-1.0f,0.0f,0.0f),  vec2(0.0f, 1.0f)),
	  TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f),vec3(-1.0f,0.0f,0.0f),  vec2(1.0f, 1.0f)),

	  TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f),vec3(-1.0f,0.0f,0.0f),  vec2(0.0f, 0.0f)),
	  TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f),vec3(-1.0f,0.0f,0.0f),  vec2(1.0f, 1.0f)),
	  TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f),vec3(-1.0f,0.0f,0.0f),  vec2(1.0f, 0.0f)),

	  TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f),	vec3(0.0f,0.0f,-1.0f),  vec2(1.0f, 1.0f)), //far
	  TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f),vec3(0.0f,0.0f,-1.0f),  vec2(0.0f, 0.0f)),
	  TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f),vec3(0.0f,0.0f,-1.0f),  vec2(0.0f, 1.0f)),

	  TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f),	vec3(0.0f,0.0f,-1.0f),	vec2(1.0f, 1.0f)),
	  TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f),vec3(0.0f,0.0f,-1.0f),	vec2(1.0f, 0.0f)),
	  TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f),vec3(0.0f,0.0f,-1.0f),  vec2(0.0f, 0.0f)),

	  TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f),	vec3(0.0f,-1.0f,0.0f),  vec2(1.0f, 1.0f)),//bottom
	  TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f,-1.0f,0.0f), vec2(0.0f, 0.0f)),
	  TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f),	vec3(0.0f,-1.0f,0.0f),  vec2(1.0f, 0.0f)),

	  TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f),	vec3(0.0f,-1.0f,0.0f),  vec2(1.0f, 1.0f)),
	  TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f),vec3(0.0f,-1.0f,0.0f),  vec2(0.0f, 1.0f)),
	  TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f,-1.0f,0.0f), vec2(0.0f, 0.0f)),

	  TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f),vec3(0.0f,0.0f,1.0f),  vec2(0.0f, 1.0f)),// near 
	  TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f),vec3(0.0f,0.0f,1.0f),  vec2(0.0f, 0.0f)),
	  TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f),	vec3(0.0f,0.0f,1.0f),  vec2(1.0f, 0.0f)),

	  TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f),	vec3(0.0f,0.0f,1.0f),	vec2(1.0f, 1.0f)),
	  TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f),vec3(0.0f,0.0f,1.0f),	vec2(0.0f, 1.0f)),
	  TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f),	vec3(0.0f,0.0f,1.0f),	vec2(1.0f, 0.0f)),

	  TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f),vec3(1.0f,0.0f,0.0f),	vec2(1.0f, 1.0f)),//right
	  TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f),vec3(1.0f,0.0f,0.0f),	vec2(0.0f, 0.0f)),
	  TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f),vec3(1.0f,0.0f,0.0f),	vec2(1.0f, 0.0f)),

	  TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f),vec3(1.0f,0.0f,0.0f),	vec2(0.0f, 0.0f)),
	  TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f),vec3(1.0f,0.0f,0.0f),	vec2(1.0f, 1.0f)),
	  TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f),vec3(1.0f,0.0f,0.0f),	vec2(0.0f, 1.0f)),

	  TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f),	vec3(0.0f,1.0f,0.0f),	vec2(1.0f, 1.0f)), //top
	  TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f),	vec3(0.0f,1.0f,0.0f),	vec2(1.0f, 0.0f)),
	  TexturedColoredVertex(vec3(-0.5f,0.5f,-0.5f), vec3(0.0f,1.0f,0.0f),	vec2(0.0f, 0.0f)),

	  TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f),vec3(0.0f,1.0f,0.0f),	vec2(1.0f, 1.0f)),
	  TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f),vec3(0.0f,1.0f,0.0f),	vec2(0.0f, 0.0f)),
	  TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f),vec3(0.0f,1.0f,0.0f),	vec2(0.0f, 1.0f)),

	  TexturedColoredVertex(vec3(50.0f, 0.5f, 0.0f),vec3(0.0f,1.0f,0.0f),	vec2(0.0f, 1.0f)), //line ground 
	  TexturedColoredVertex(vec3(-50.0f, 0.5f, 0.0f),vec3(0.0f,1.0f,0.0f),	vec2(0.0f, 1.0f)),
	  TexturedColoredVertex(vec3(0.0f, 0.5f, 50.0f),vec3(0.0f,1.0f,0.0f),	vec2(0.0f, 1.0f)),
	  TexturedColoredVertex(vec3(0.0f, 0.5f, -50.0f),vec3(0.0f,1.0f,0.0f),	vec2(0.0f, 1.0f)),

	  TexturedColoredVertex(vec3(0.0f, 0.0f, 0.0f),	vec3(1.0f,0.0f,0.0f),	vec2(0.0f, 1.0f)),//axis
	  TexturedColoredVertex(vec3(0.0f, 5.0f, 0.0f),	vec3(1.0f,0.0f,0.0f),	vec2(0.0f, 1.0f)),
	  TexturedColoredVertex(vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f,1.0f,0.0f),	vec2(0.0f, 1.0f)),
	  TexturedColoredVertex(vec3(0.0f, 0.0f, 5.0f),	vec3(0.0f,1.0f,0.0f),	vec2(0.0f, 1.0f)),
	  TexturedColoredVertex(vec3(0.0f, 0.0f, 0.0f),	vec3(0.0f,1.0f,0.0f),	vec2(0.0f, 1.0f)),
	  TexturedColoredVertex(vec3(5.0f, 0.0f, 0.0f),	vec3(0.0f,1.0f,0.0f),	vec2(0.0f, 1.0f)),

	  TexturedColoredVertex(vec3(50.0f, 0.5f, 50.0f),vec3(0.0f,1.0f,0.0f),	vec2(1.0f, 1.0f)), //texture ground
	  TexturedColoredVertex(vec3(50.0f, 0.5f,-50.0f),vec3(0.0f,1.0f,0.0f),	vec2(1.0f, 0.0f)),
	  TexturedColoredVertex(vec3(-50.0f, 0.5f,-50.0f),vec3(0.0f,1.0f,0.0f),	vec2(0.0f, 0.0f)),

	  TexturedColoredVertex(vec3(50.0f, 0.5f, 50.0f),vec3(0.0f,1.0f,0.0f),	vec2(1.0f, 1.0f)),
	  TexturedColoredVertex(vec3(-50.0f, 0.5f,-50.0f),vec3(0.0f,1.0f,0.0f),	vec2(0.0f, 0.0f)),
	  TexturedColoredVertex(vec3(-50.0f, 0.5f, 50.0f),vec3(0.0f,1.0f,0.0f),	vec2(0.0f, 1.0f)),
	};
	for (int i = 0; i <= 360; i += 1) {
		texturedCubeVertexArray.push_back(TexturedColoredVertex(vec3(cos(PI / 180 * i), 1.0f, sin(PI / 180 * i)), vec3(cos(PI / 180 * i), 1.0f, sin(PI / 180 * i)), vec2(1.0f, (sin(PI / 720 * i)))));
		texturedCubeVertexArray.push_back(TexturedColoredVertex(vec3(cos(PI / 180 * i), -1.0f, sin(PI / 180 * i)), vec3(cos(PI / 180 * i), 1.0f, sin(PI / 180 * i)), vec2(0.0f, (sin(PI / 720 * i)))));
	}
	texturedCubeVertexArray.push_back(TexturedColoredVertex(vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec2(0.5f, 0.5f)));
	for (int i = 0; i <= 360; i += 1) {
		texturedCubeVertexArray.push_back(TexturedColoredVertex(vec3(cos(PI / 180 * i), 1.0f, sin(PI / 180 * i)), vec3(0.0f, 1.0f, 0.0f), vec2(0.5f+ 0.3*cos(PI / 180 * i), 0.5f+0.3*sin(PI / 180 * i))));
	}
	
	texturedCubeVertexArray.push_back(TexturedColoredVertex(vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 0.0f)));
	for (int i = 0; i <= 360; i += 1) {
		texturedCubeVertexArray.push_back(TexturedColoredVertex(vec3(cos(PI / 180 * i), -1.0f, sin(PI / 180 * i)), vec3(0.0f, -1.0f, 0.0f), vec2(0.5f + 0.3 * cos(PI / 180 * i), 0.5f + 0.3 * sin(PI / 180 * i))));
	}
	
	// Create a vertex array
	GLuint vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	// Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
	GLuint vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, texturedCubeVertexArray.size()* sizeof(TexturedColoredVertex), &texturedCubeVertexArray.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
		3,                   // size
		GL_FLOAT,            // type
		GL_FALSE,            // normalized?
		sizeof(TexturedColoredVertex), // stride - each vertex contain 2 vec3 (position, color)
		(void*)0             // array buffer offset
	);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1,                   // attribute 0 matches aPos in Vertex Shader
		3,                   // size
		GL_FLOAT,            // type
		GL_FALSE,            // normalized?
		sizeof(TexturedColoredVertex), // stride - each vertex contain 2 vec3 (position, color)
		(void*)(sizeof(vec3))             // array buffer offset
	);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2,                            // attribute 2 matches aUV in Vertex Shader
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(TexturedColoredVertex),
		(void*)(2*sizeof(vec3))      // uv is offseted by 2 vec3 (comes after position and color)
	);
	glEnableVertexAttribArray(2);

	return vertexBufferObject;
}
	
struct Particle
{
	Particle(vec3 _position, vec3 _velocity, GLfloat _life)
		: position(_position), velocity(_velocity), Life(_life) {}

	vec3 position;  //start at the tail 
	vec3 velocity;  //
	GLfloat Life;  //
};



int loadTexture(char* imagepath)
{
	// Load image using the Free Image library
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(imagepath, 0);
	FIBITMAP* image = FreeImage_Load(format, imagepath);
	FIBITMAP* image32bits = FreeImage_ConvertTo32Bits(image);

	// Get an available texture index from OpenGL
	GLuint texture = 0;
	glGenTextures(1, &texture);
	assert(texture != 0);

	// Set OpenGL filtering properties (bi-linear interpolation)
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Retrieve width and hight
	int width = FreeImage_GetWidth(image32bits);
	int height = FreeImage_GetHeight(image32bits);

	// This will upload the texture to the GPU memory
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
		0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image32bits));

	// Free images
	FreeImage_Unload(image);
	FreeImage_Unload(image32bits);

	return texture;
}


int FirstUnusedParticle(vector<Particle> myVector,int& lastUsedParticle)
{
	// Search from last used particle, this will usually return almost instantly
	for (int i = lastUsedParticle; i < myVector.size(); ++i) {
		if (myVector[i].Life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// Otherwise, do a linear search
	for (int i = 0; i < lastUsedParticle; ++i) {
		if (myVector[i].Life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// Override first particle if all others are alive
	lastUsedParticle = 0;
	return 0;
}
//respawn
void RespawnParticle(Particle& particle,vec3 carPosition,vec3 carVelocity,float carSize)
{
	float a = RandomNumber(0.0f, 360.0f);
	float r = 0.025f*carSize * RandomNumber(0.0f, 1.0f);
	particle.position = carPosition + vec3(0.0f, r * cos(a/180*PI),r*sin(a/180*PI));
	particle.Life = 1.0f;
	particle.velocity =	carVelocity;
}


int main(int argc, char* argv[])
{
	// Initialize GLFW and OpenGL version
	glfwInit();

#if defined(PLATFORM_OSX)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
	// On windows, we set OpenGL version to 2.1, to support more hardware
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#endif
	// Create Window and rendering context using GLFW, resolution is 800x600
	GLFWwindow* window = glfwCreateWindow(1024, 768, "Yifan's openGLCar", NULL, NULL);  //glfw default double buffer
	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to create GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Load Textures
#if defined(PLATFORM_OSX)
	GLuint grassTextureID = loadTexture("Textures/grass.jpg");
	GLuint cementTextureID = loadTexture("Textures/cement.jpg");
	GLuint particleTextureID = loadTexture("Textures/Particle.png");
#else
	GLuint grassTextureID = loadTexture("../Assets/Textures/grass.jpg");
	GLuint cementTextureID = loadTexture("../Assets/Textures/cement.jpg");
	GLuint particleTextureID = loadTexture("../Assets/Textures/Particle.png");
#endif
	//TODO 1 TEXTURE GENERATION
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	// create depth texture
	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//TODO 1 END
	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Compile and link shaders here ...
	Shader ColorShader("./vertex.glsl", "./fragment.glsl");
	Shader TextureShader("./textureVertex.glsl", "./textureFragment.glsl");
	Shader simpleDepthShader("./simpleVertex.glsl", "./simpleFragment.glsl");
	Shader modelShader("./modelVertex.glsl", "./modelFragment.glsl");
	//model
	Model santa("../Assets/Models/Santa/12165_Santa_Claus_v1_l2.obj");
	Model spider("../Assets/Models/spider/Only_Spider_with_Animations_Export.obj");
	Model house("../Assets/Models/house/farmhouse_obj.obj");
	Model dog("../Assets/Models/dog/12228_Dog_v1_L2.obj");
	Model awp("../Assets/Models/dragonLore/AWP_Dragon_Lore.obj");

	//camera
	// Camera parameters for view transform
	vec3 cameraPosition(-60.0f, 25.0f, 0.0f); //INITIAL CAMERA
	vec3 cameraLookAt(0.0f, 0.0f, 0.0f);
	vec3 cameraUp(0.0f, 1.0f, 0.0f);

	float cameraZoom = 1.0f;
	float cameraRotate = 0.0f;
	float cameraTilt = 0.0f;




	// Set projection matrix for shader, this won't change
	mat4 projectionMatrix = glm::perspective(radians(70.0f),            // field of view in degrees
		1024.0f / 768.0f,  // aspect ratio
		0.01f, 100.0f);   // near and far (near > 0)

	mat4 viewMatrix = lookAt(cameraPosition,  // eye
		cameraLookAt,  // center
		cameraUp); // up
	ColorShader.use();
	ColorShader.setMat4("viewMatrix", viewMatrix);
	ColorShader.setMat4("projectionMatrix", projectionMatrix);
	modelShader.use();
	modelShader.setMat4("view", viewMatrix);
	modelShader.setMat4("projection", projectionMatrix);
	TextureShader.use();
	TextureShader.setMat4("viewMatrix", viewMatrix);
	TextureShader.setMat4("projectionMatrix", projectionMatrix);
	TextureShader.setInt("textureSampler", 0);
	TextureShader.setInt("depthMap", 1);
	//-------------------parameters---------------
	//bullet
	vec3 bulletPosition = vec3(-30.0f, 1.0f, 35.0f);
	float bulletRotate = 0.0f;
	vec3 lightPos = vec3(-2.0f, 30.0f, 0.0f);
	//car Move
	GLenum carMode = GL_TRIANGLES;
	float carSize = 1.0f;
	vec3 carPosition = vec3(0.0f, 0.0f, 0.0f);
	float carDirection = 90.0f;
	vec3 carVector = vec3(sin(radians(carDirection)), 0.0f, cos(radians(carDirection)));
	float carForwardMove = 0.0f;
	float carLateralMove = 0.0f;

	//support flag
	bool spaceFlag = true;
	bool textureFlag = true;
	bool textureRender = false;
	bool firstPersonFlag = true;
	bool firstPersonRender = false;
	bool shadowFlag = true;
	bool shadowRender = false;
	bool carLightFlag = true;
	bool carLightRender = false;
	bool scriptFlag = true;
	bool scriptRender = false;
	//particle
	GLuint nr_particles = 500;
	std::vector<Particle> particles;
	int lastUsedParticle = 0;
	//scriptCounter
	int scriptCounter = 0;
	for (GLuint i = 0; i < nr_particles; ++i)
		particles.push_back(Particle(vec3(0.0f), vec3(0.0f), 0.0f));
	// voice
	ISoundEngine* SoundEngine = createIrrKlangDevice();
	ISoundEngine* bulletEngine = createIrrKlangDevice();
	SoundEngine->play2D("../Assets/music/Wheels_On_the_Bus.mp3", GL_TRUE);
	//mouse
	// For frame time
	float lastFrameTime = glfwGetTime();
	int lastMouseLeftState = GLFW_RELEASE;
	double lastMousePosX, lastMousePosY;
	glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);
	glfwSwapInterval(1);
	// Other OpenGL states to set once
	// Enable Backface culling

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	// Entering Main Loop
	while (!glfwWindowShouldClose(window))
	{
		// Define and upload geometry to the GPU here ...

		int texturedCubeVBO = createTexturedCubeVertexBufferObject();

		// Frame time calculation
		float dt = glfwGetTime() - lastFrameTime;
		lastFrameTime += dt;

		//depth generation
		//TODO 2
		float near_plane = -50.0f;
		float far_plane = 50.0f;
		mat4 lightProjection = ortho(-50.0f, 50.0f, -50.0f, 50.0f, near_plane, far_plane);
		//mat4 lightProjection = perspective(-50.0f, 50.0f, -50.0f, 50.0f, near_plane, far_plane);
		mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
		mat4 lightSpaceMatrix = lightProjection * lightView;
		simpleDepthShader.use();
		simpleDepthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, grassTextureID);
		//step1 buzhidaoyaobuyaojihuorender



		mat4 currentSelfRotateMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f + carSize * 2.8, 0.0f))
			* translate(mat4(1.0f), carPosition)
			* rotate(mat4(1.0f), radians(carDirection - 90.0f), vec3(0.0f, 1.0f, 0.0f))
			* scale(mat4(1.0f), vec3(carSize, carSize, carSize))
			* rotate(mat4(1.0f), radians(bulletRotate), vec3(1.0f, 0.0f, 0.0f));


		//myStory
		if (scriptRender) {

				carPosition = carPosition + 0.25f * carVector;  //press W
				carForwardMove += 0.25f;
				
	
					carDirection -= 2.0f;  //press D
					carVector = vec3(sin(radians(carDirection)), 0.0f, cos(radians(carDirection)));
					if (carLateralMove > -0.6f)
						carLateralMove -= 0.1f;
					else {
						carLateralMove = -0.6f;
					}



			scriptCounter++;
		}


		//current gengxin
		//zai yuanyou jichushang liyongcha zhi jinxing xiao move
		//LASTshuaxin
	//------------------------------------------------------------------------------------------------------------
		//car model
		//body 
			//GROUND
		simpleDepthShader.setMat4("worldMatrix", translate(mat4(1.0f), vec3(0.0f, -0.5f, 0.0f)));
		glDrawArrays(GL_TRIANGLES, 46, 6);
		mat4 pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(0.0f, -2.3f, 0.0f)) * scale(mat4(1.0f), vec3(1.5f, 0.5f, 1.0f));
		simpleDepthShader.setMat4("worldMatrix", pillarSpecialMatrix);
		glDrawArrays(carMode, 0, 36);
		//top 
		pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(0.0f, -1.9f, 0.0f)) * scale(mat4(1.0f), vec3(1.0f, 0.3f, 0.5f));
		simpleDepthShader.setMat4("worldMatrix", pillarSpecialMatrix);
		glDrawArrays(carMode, 0, 36);

		//bonnet 
		pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(1.05f, -2.45f, 0.0f)) * scale(mat4(1.0f), vec3(0.7f, 0.2f, 1.0f));
		simpleDepthShader.setMat4("worldMatrix", pillarSpecialMatrix);
		glDrawArrays(carMode, 0, 36);

		pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(-1.05f, -2.45f, 0.0f)) * scale(mat4(1.0f), vec3(0.7f, 0.2f, 1.0f));
		simpleDepthShader.setMat4("worldMatrix", pillarSpecialMatrix);
		glDrawArrays(carMode, 0, 36);
		//wheel  
		pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(0.5f, -2.5f, -0.65f))
			* rotate(mat4(1.0f), carLateralMove, vec3(0.0f, 1.0f, 0.0f))
			* rotate(mat4(1.0f), 0.5f * 3.1415926f, vec3(1.0f, 0.0f, 0.0f))
			* scale(mat4(1.0f), vec3(0.3f, 0.15f, 0.3f))
			* rotate(glm::mat4(1.0f), radians(carForwardMove * -45), vec3(0.0f, 1.0f, 0.0f));
		simpleDepthShader.setMat4("worldMatrix", pillarSpecialMatrix);
		glDrawArrays(GL_QUAD_STRIP, 52, 722);
		glDrawArrays(GL_TRIANGLE_FAN, 774, 362);
		glDrawArrays(GL_TRIANGLE_FAN, 1136, 362);

		pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(-0.5f, -2.5f, 0.65f))
			* rotate(mat4(1.0f), 0.5f * 3.1415926f, vec3(1.0f, 0.0f, 0.0f))
			* scale(mat4(1.0f), vec3(0.3f, 0.15f, 0.3f))
			* rotate(glm::mat4(1.0f), radians(carForwardMove * -45), vec3(0.0f, 1.0f, 0.0f));
		simpleDepthShader.setMat4("worldMatrix", pillarSpecialMatrix);
		glDrawArrays(GL_QUAD_STRIP, 52, 722);
		glDrawArrays(GL_TRIANGLE_FAN, 774, 362);
		glDrawArrays(GL_TRIANGLE_FAN, 1136, 362);


		pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(-0.5f, -2.5f, -0.65f))
			* rotate(mat4(1.0f), 0.5f * 3.1415926f, vec3(1.0f, 0.0f, 0.0f))
			* scale(mat4(1.0f), vec3(0.3f, 0.15f, 0.3f))
			* rotate(glm::mat4(1.0f), radians(carForwardMove * -45), vec3(0.0f, 1.0f, 0.0f));
		simpleDepthShader.setMat4("worldMatrix", pillarSpecialMatrix);
		glDrawArrays(GL_QUAD_STRIP, 52, 722);
		glDrawArrays(GL_TRIANGLE_FAN, 774, 362);
		glDrawArrays(GL_TRIANGLE_FAN, 1136, 362);

		pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(0.5f, -2.5f, 0.65f))
			* rotate(mat4(1.0f), carLateralMove, vec3(0.0f, 1.0f, 0.0f))
			* rotate(mat4(1.0f), 0.5f * 3.1415926f, vec3(1.0f, 0.0f, 0.0f))
			* scale(mat4(1.0f), vec3(0.3f, 0.15f, 0.3f))
			* rotate(glm::mat4(1.0f), radians(carForwardMove * -45), vec3(0.0f, 1.0f, 0.0f));
		simpleDepthShader.setMat4("worldMatrix", pillarSpecialMatrix);
		glDrawArrays(GL_QUAD_STRIP, 52, 722);
		glDrawArrays(GL_TRIANGLE_FAN, 774, 362);
		glDrawArrays(GL_TRIANGLE_FAN, 1136, 362);

		pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(1.425f, -2.45f, 0.3f)) * scale(mat4(1.0f), vec3(0.05f, 0.12f, 0.12f));
		simpleDepthShader.setMat4("worldMatrix", pillarSpecialMatrix);
		glDrawArrays(carMode, 0, 36);
		vec3 lightPos1 = vec3(pillarSpecialMatrix[3][0], pillarSpecialMatrix[3][1], pillarSpecialMatrix[3][2]);
		pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(-1.425f, -2.45f, 0.3f)) * scale(mat4(1.0f), vec3(0.05f, 0.12f, 0.12f));
		simpleDepthShader.setMat4("worldMatrix", pillarSpecialMatrix);
		glDrawArrays(carMode, 0, 36);
		vec3 lightPos2 = vec3(pillarSpecialMatrix[3][0], pillarSpecialMatrix[3][1], pillarSpecialMatrix[3][2]);
		pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(1.425f, -2.45f, -0.3f)) * scale(mat4(1.0f), vec3(0.05f, 0.12f, 0.12f));
		simpleDepthShader.setMat4("worldMatrix", pillarSpecialMatrix);
		glDrawArrays(carMode, 0, 36);
		vec3 lightPos3 = vec3(pillarSpecialMatrix[3][0], pillarSpecialMatrix[3][1], pillarSpecialMatrix[3][2]);
		pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(-1.425f, -2.45f, -0.3f)) * scale(mat4(1.0f), vec3(0.05f, 0.12f, 0.12f));
		simpleDepthShader.setMat4("worldMatrix", pillarSpecialMatrix);
		glDrawArrays(carMode, 0, 36);
		vec3 lightPos4 = vec3(pillarSpecialMatrix[3][0], pillarSpecialMatrix[3][1], pillarSpecialMatrix[3][2]);
		//todo 2 continue

		pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(-1.4f, -2.45, 0.0))
			* rotate(mat4(1.0f), 0.5f * 3.1415926f, vec3(0.0f, 0.0f, 1.0f))
			* scale(mat4(1.0f), vec3(0.03f, 0.1f, 0.03f));
		simpleDepthShader.setMat4("worldMatrix", pillarSpecialMatrix);
		glDrawArrays(GL_QUAD_STRIP, 52, 722);



		//----------------------------------------------
			/*	glBindFramebuffer(GL_FRAMEBUFFER, 0);
				glViewport(0, 0, 1024, 768);
				glClearColor(0.0,0.0,0.0,1.0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				debugDepthQuad.use();
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, depthMap);
				RenderQuad(); */
				//-----------------------------------------
					//todo 3
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, 1024, 768);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw texture part

		if (textureRender == true)
		{
			TextureShader.use();
			TextureShader.setFloat("transparency", 1.0f);
			TextureShader.setVec3("light[0].position", lightPos);
			TextureShader.setVec3("light[0].ambient", 0.2f, 0.2f, 0.2f);
			TextureShader.setVec3("light[0].diffuse", 0.3f, 0.3f, 0.3f);
			TextureShader.setVec3("light[0].specular", 0.3f, 0.3f, 0.3f);
			TextureShader.setVec3("light[1].position", lightPos1);
			TextureShader.setVec3("viewPos[1]", lightPos1 + carSize * carVector);
			TextureShader.setVec3("light[2].position", lightPos2);
			TextureShader.setVec3("viewPos[2]", lightPos2 - carSize * carVector);
			TextureShader.setVec3("light[3].position", lightPos3);
			TextureShader.setVec3("viewPos[3]", lightPos3 + carSize * carVector);
			TextureShader.setVec3("light[4].position", lightPos4);
			TextureShader.setVec3("viewPos[4]", lightPos4 - carSize * carVector);
			TextureShader.setVec3("viewPos[0]", cameraPosition);
			if (carLightRender) {
				TextureShader.setVec3("light[1].ambient", 0.0f, 0.0f, 0.0f);
				TextureShader.setVec3("light[1].diffuse", 0.05f, 0.05f, 0.05f);
				TextureShader.setVec3("light[1].specular", 0.3f, 0.3f, 0.3f);
				TextureShader.setVec3("light[2].ambient", 0.0f, 0.0f, 0.0f);
				TextureShader.setVec3("light[2].diffuse", 0.05f, 0.05f, 0.05f);
				TextureShader.setVec3("light[2].specular", 0.3f, 0.3f, 0.3f);
				TextureShader.setVec3("light[3].ambient", 0.0f, 0.0f, 0.0f);
				TextureShader.setVec3("light[3].diffuse", 0.05f, 0.05f, 0.05f);
				TextureShader.setVec3("light[3].specular", 0.3f, 0.3f, 0.3f);
				TextureShader.setVec3("light[4].ambient", 0.0f, 0.0f, 0.0f);
				TextureShader.setVec3("light[4].diffuse", 0.05f, 0.05f, 0.05f);
				TextureShader.setVec3("light[4].specular", 0.3f, 0.3f, 0.3f);
			}
			else {
				TextureShader.setVec3("light[1].ambient", 0.0f, 0.0f, 0.0f);
				TextureShader.setVec3("light[1].diffuse", 0.0f, 0.0f, 0.0f);
				TextureShader.setVec3("light[1].specular", 0.0f, 0.0f, 0.0f);
				TextureShader.setVec3("light[2].ambient", 0.0f, 0.0f, 0.0f);
				TextureShader.setVec3("light[2].diffuse", 0.0f, 0.0f, 0.0f);
				TextureShader.setVec3("light[2].specular", 0.0f, 0.0f, 0.0f);
				TextureShader.setVec3("light[3].ambient", 0.0f, 0.0f, 0.0f);
				TextureShader.setVec3("light[3].diffuse", 0.0f, 0.0f, 0.0f);
				TextureShader.setVec3("light[3].specular", 0.0f, 0.0f, 0.0f);
				TextureShader.setVec3("light[4].ambient", 0.0f, 0.0f, 0.0f);
				TextureShader.setVec3("light[4].diffuse", 0.0f, 0.0f, 0.0f);
				TextureShader.setVec3("light[4].specular", 0.0f, 0.0f, 0.0f);
			}
			TextureShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
			if (shadowRender == true) {
				TextureShader.setBool("shadowFlag", true);

			}
			else
				TextureShader.setBool("shadowFlag", false);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, grassTextureID);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, depthMap);
			TextureShader.setMat4("worldMatrix", translate(mat4(1.0f), vec3(0.0f, -0.5f, 0.0f)));
			glDrawArrays(GL_TRIANGLES, 46, 6);
		}

		ColorShader.use();

		ColorShader.setVec3("light[0].ambient", 0.2f, 0.2f, 0.2f);
		ColorShader.setVec3("light[0].diffuse", 1.0f, 1.0f, 1.0f);
		ColorShader.setVec3("light[0].specular", 1.0f, 1.0f, 1.0f);
		ColorShader.setVec3("light[0].position", lightPos);
		ColorShader.setVec3("viewPos", cameraPosition);

		//body gold
		pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(0.0f, -2.3f, 0.0f)) * scale(mat4(1.0f), vec3(1.5f, 0.5f, 1.0f));
		ColorShader.setVec3("material.ambient", 0.24725f, 0.1995f, 0.0745f);
		ColorShader.setVec3("material.diffuse", 0.75164f, 0.60648f, 0.22648f);
		ColorShader.setVec3("material.specular", 0.628281f, 0.555802f, 0.366065f);
		ColorShader.setFloat("material.shininess", 51.2f);
		ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
		glDrawArrays(carMode, 0, 36);
		//top //polished silver
		pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(0.0f, -1.9f, 0.0f)) * scale(mat4(1.0f), vec3(1.0f, 0.3f, 0.5f));
		ColorShader.setVec3("material.ambient", 0.23125f, 0.23125f, 0.23125f);
		ColorShader.setVec3("material.diffuse", 0.2775f, 0.2775f, 0.2775f);
		ColorShader.setVec3("material.specular", 0.773911f, 0.773911f, 0.773911f);
		ColorShader.setFloat("material.shininess", 89.6f);
		ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
		glDrawArrays(carMode, 0, 36);

		//bonnet //polished bronze
		pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(1.05f, -2.45f, 0.0f)) * scale(mat4(1.0f), vec3(0.7f, 0.2f, 1.0f));
		ColorShader.setVec3("material.ambient", 0.25f, 0.148f, 0.06475f);
		ColorShader.setVec3("material.diffuse", 0.4f, 0.268f, 0.1036f);
		ColorShader.setVec3("material.specular", 0.774597f, 0.458561f, 0.200621f);
		ColorShader.setFloat("material.shininess", 76.8f);
		ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
		glDrawArrays(carMode, 0, 36);

		pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(-1.05f, -2.45f, 0.0f)) * scale(mat4(1.0f), vec3(0.7f, 0.2f, 1.0f));
		ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
		glDrawArrays(carMode, 0, 36);



		//wheel  //black rubber  //particledraw
		if (textureRender == true)
		{
			TextureShader.use();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, cementTextureID);
			pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(0.5f, -2.5f, -0.65f))
				* rotate(mat4(1.0f), carLateralMove, vec3(0.0f, 1.0f, 0.0f))
				* rotate(mat4(1.0f), 0.5f * 3.1415926f, vec3(1.0f, 0.0f, 0.0f))
				* scale(mat4(1.0f), vec3(0.3f, 0.15f, 0.3f))
				* rotate(glm::mat4(1.0f), radians(carForwardMove * -45), vec3(0.0f, 1.0f, 0.0f));
			TextureShader.setMat4("worldMatrix", pillarSpecialMatrix);
			glDrawArrays(GL_QUAD_STRIP, 52, 722);
			glDrawArrays(GL_TRIANGLE_FAN, 774, 362);
			glDrawArrays(GL_TRIANGLE_FAN, 1136, 362);

			pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(-0.5f, -2.5f, 0.65f))
				* rotate(mat4(1.0f), 0.5f * 3.1415926f, vec3(1.0f, 0.0f, 0.0f))
				* scale(mat4(1.0f), vec3(0.3f, 0.15f, 0.3f))
				* rotate(glm::mat4(1.0f), radians(carForwardMove * -45), vec3(0.0f, 1.0f, 0.0f));
			TextureShader.setMat4("worldMatrix", pillarSpecialMatrix);
			glDrawArrays(GL_QUAD_STRIP, 52, 722);
			glDrawArrays(GL_TRIANGLE_FAN, 774, 362);
			glDrawArrays(GL_TRIANGLE_FAN, 1136, 362);


			pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(-0.5f, -2.5f, -0.65f))
				* rotate(mat4(1.0f), 0.5f * 3.1415926f, vec3(1.0f, 0.0f, 0.0f))
				* scale(mat4(1.0f), vec3(0.3f, 0.15f, 0.3f))
				* rotate(glm::mat4(1.0f), radians(carForwardMove * -45), vec3(0.0f, 1.0f, 0.0f));
			TextureShader.setMat4("worldMatrix", pillarSpecialMatrix);
			glDrawArrays(GL_QUAD_STRIP, 52, 722);
			glDrawArrays(GL_TRIANGLE_FAN, 774, 362);
			glDrawArrays(GL_TRIANGLE_FAN, 1136, 362);


			pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(0.5f, -2.5f, 0.65f))
				* rotate(mat4(1.0f), carLateralMove, vec3(0.0f, 1.0f, 0.0f))
				* rotate(mat4(1.0f), 0.5f * 3.1415926f, vec3(1.0f, 0.0f, 0.0f))
				* scale(mat4(1.0f), vec3(0.3f, 0.15f, 0.3f))
				* rotate(glm::mat4(1.0f), radians(carForwardMove * -45), vec3(0.0f, 1.0f, 0.0f));
			TextureShader.setMat4("worldMatrix", pillarSpecialMatrix);
			glDrawArrays(GL_QUAD_STRIP, 52, 722);
			glDrawArrays(GL_TRIANGLE_FAN, 774, 362);
			glDrawArrays(GL_TRIANGLE_FAN, 1136, 362);

		}
		else {
			pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(0.5f, -2.5f, -0.65f))
				* rotate(mat4(1.0f), carLateralMove, vec3(0.0f, 1.0f, 0.0f))
				* rotate(mat4(1.0f), 0.5f * 3.1415926f, vec3(1.0f, 0.0f, 0.0f))
				* scale(mat4(1.0f), vec3(0.3f, 0.15f, 0.3f))
				* rotate(glm::mat4(1.0f), radians(carForwardMove * -45), vec3(0.0f, 1.0f, 0.0f));
			ColorShader.setVec3("material.diffuse", 0.01f, 0.01f, 0.01f);
			ColorShader.setVec3("material.specular", 0.4f, 0.4f, 0.4f);
			ColorShader.setFloat("material.shininess", 10.0f);
			ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
			glDrawArrays(GL_QUAD_STRIP, 52, 722);
			glDrawArrays(GL_TRIANGLE_FAN, 774, 362);
			glDrawArrays(GL_TRIANGLE_FAN, 1136, 362);

			pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(-0.5f, -2.5f, 0.65f))
				* rotate(mat4(1.0f), 0.5f * 3.1415926f, vec3(1.0f, 0.0f, 0.0f))
				* scale(mat4(1.0f), vec3(0.3f, 0.15f, 0.3f))
				* rotate(glm::mat4(1.0f), radians(carForwardMove * -45), vec3(0.0f, 1.0f, 0.0f));
			ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
			glDrawArrays(GL_QUAD_STRIP, 52, 722);
			glDrawArrays(GL_TRIANGLE_FAN, 774, 362);
			glDrawArrays(GL_TRIANGLE_FAN, 1136, 362);


			pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(-0.5f, -2.5f, -0.65f))
				* rotate(mat4(1.0f), 0.5f * 3.1415926f, vec3(1.0f, 0.0f, 0.0f))
				* scale(mat4(1.0f), vec3(0.3f, 0.15f, 0.3f))
				* rotate(glm::mat4(1.0f), radians(carForwardMove * -45), vec3(0.0f, 1.0f, 0.0f));
			ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
			glDrawArrays(GL_QUAD_STRIP, 52, 722);
			glDrawArrays(GL_TRIANGLE_FAN, 774, 362);
			glDrawArrays(GL_TRIANGLE_FAN, 1136, 362);


			pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(0.5f, -2.5f, 0.65f))
				* rotate(mat4(1.0f), carLateralMove, vec3(0.0f, 1.0f, 0.0f))
				* rotate(mat4(1.0f), 0.5f * 3.1415926f, vec3(1.0f, 0.0f, 0.0f))
				* scale(mat4(1.0f), vec3(0.3f, 0.15f, 0.3f))
				* rotate(glm::mat4(1.0f), radians(carForwardMove * -45), vec3(0.0f, 1.0f, 0.0f));
			ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
			glDrawArrays(GL_QUAD_STRIP, 52, 722);
			glDrawArrays(GL_TRIANGLE_FAN, 774, 362);
			glDrawArrays(GL_TRIANGLE_FAN, 1136, 362);
		}

		//light 


		ColorShader.use();

		//tail

		ColorShader.setVec3("material.ambient", 1.0f, 1.0f, 1.0f);
		ColorShader.setVec3("material.diffuse", 1.0f, 1.0f, 1.0f);
		ColorShader.setVec3("material.specular", 1.0f, 1.0f, 1.0f);
		ColorShader.setFloat("material.shininess", 10.0f);
		pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(-1.4f, -2.45, 0.0))
			* rotate(mat4(1.0f), 0.5f * 3.1415926f, vec3(0.0f, 0.0f, 1.0f))
			* scale(mat4(1.0f), vec3(0.03f, 0.1f, 0.03f));
		ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
		glDrawArrays(GL_QUAD_STRIP, 52, 722);

		//COLORSHADER PART
		if (!carLightRender) {
			ColorShader.setVec3("material.ambient", 1.0f, 1.0f, 1.0f);
			ColorShader.setVec3("material.diffuse", 1.0f, 1.0f, 1.0f);
			ColorShader.setVec3("material.specular", 1.0f, 1.0f, 1.0f);
			pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(1.425f, -2.45f, 0.3f)) * scale(mat4(1.0f), vec3(0.05f, 0.12f, 0.12f));
			ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
			glDrawArrays(carMode, 0, 36);
			pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(-1.425f, -2.45f, 0.3f)) * scale(mat4(1.0f), vec3(0.05f, 0.12f, 0.12f));
			ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
			glDrawArrays(carMode, 0, 36);
			pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(1.425f, -2.45f, -0.3f)) * scale(mat4(1.0f), vec3(0.05f, 0.12f, 0.12f));
			ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
			glDrawArrays(carMode, 0, 36);
			pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(-1.425f, -2.45f, -0.3f)) * scale(mat4(1.0f), vec3(0.05f, 0.12f, 0.12f));
			ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
			glDrawArrays(carMode, 0, 36);
		}

		//draw particle
		//-----------------------------------------
		//glDisable(GL_DEPTH_TEST);
		if (!textureRender) {
			pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(-1.5f, -2.45f, 0.0f));

			for (GLuint i = 0; i < 2; ++i)
			{
				int unusedParticle = FirstUnusedParticle(particles, lastUsedParticle);
				RespawnParticle(particles[unusedParticle], vec3(pillarSpecialMatrix[3][0], pillarSpecialMatrix[3][1], pillarSpecialMatrix[3][2]), 0.5f * carVector, carSize);
			}
			// Uupdate all particles

			for (GLuint i = 0; i < nr_particles; ++i)
			{
				Particle& p = particles[i];
				p.Life -= dt; // reduce life
				if (p.Life > 0.0f)
				{
					p.position -= p.velocity * dt;
					pillarSpecialMatrix = translate(mat4(1.0f), p.position) * scale(mat4(1.0f), vec3(0.02 * carSize, 0.02 * carSize, 0.02 * carSize));
					ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
					ColorShader.setFloat("transparency", p.Life);
					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
			}
			ColorShader.setFloat("transparency", 1.0f);
		}
		else {
			TextureShader.use();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, particleTextureID);
			pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(-1.5f, -2.45f, 0.0f));
			//color draw particle
			for (GLuint i = 0; i < 2; ++i)
			{
				int unusedParticle = FirstUnusedParticle(particles, lastUsedParticle);
				RespawnParticle(particles[unusedParticle], vec3(pillarSpecialMatrix[3][0], pillarSpecialMatrix[3][1], pillarSpecialMatrix[3][2]), 0.5f * carVector, carSize);
			}
			// Uupdate all particles

			for (GLuint i = 0; i < nr_particles; ++i)
			{
				Particle& p = particles[i];
				p.Life -= dt; // reduce life
				if (p.Life > 0.0f)
				{
					p.position -= p.velocity * dt;
					pillarSpecialMatrix = translate(mat4(1.0f), p.position) * scale(mat4(1.0f), vec3(0.02 * carSize, 0.02 * carSize, 0.02 * carSize));
					TextureShader.setMat4("worldMatrix", pillarSpecialMatrix);
					TextureShader.setFloat("transparency", p.Life);
					glDrawArrays(GL_TRIANGLES, 30, 6);
				}
			}
			TextureShader.setFloat("transparency", 1.0f);

		}
		//------------------------------------------------
		//glEnable(GL_DEPTH_TEST);



		ColorShader.use();
		glLineWidth(5.0);
		mat4 axisWorldMatrix = mat4(1.0f);
		ColorShader.setFloat("material.shininess", 2.0f);
		ColorShader.setMat4("worldMatrix", axisWorldMatrix);
		ColorShader.setVec3("material.ambient", 0.219f, 0.980f, 0.078f);
		ColorShader.setVec3("material.diffuse", 0.219f, 0.980f, 0.078f);
		glDrawArrays(GL_LINES, 40, 2); // 42 -43 for y axis
		ColorShader.setVec3("material.ambient", 0.078f, 0.364f, 0.980f);
		ColorShader.setVec3("material.diffuse", 0.078f, 0.364f, 0.980f);
		glDrawArrays(GL_LINES, 42, 2); // 42 -43 for z axis
		ColorShader.setVec3("material.ambient", 0.980f, 0.090f, 0.078f);
		ColorShader.setVec3("material.diffuse", 0.980f, 0.090f, 0.078f);
		glDrawArrays(GL_LINES, 44, 2); // 42 -43 for x axis

		glPointSize(6.0);


		// Draw color ground
		if (textureRender == false) {
			glLineWidth(1.0);
			for (int i = 0; i < 51; ++i) {
				mat4 groundWorldMatrix = translate(mat4(1.0f), vec3(0.0f, -0.5f, -50.0f + 2 * i));
				ColorShader.setMat4("worldMatrix", groundWorldMatrix);
				ColorShader.setVec3("material.ambient", 0.254f, 1.0f, 0.078f);
				ColorShader.setVec3("material.diffuse", 0.254f, 1.0f, 0.078f);
				ColorShader.setVec3("material.specular", 0.0f, 0.0f, 0.0f);
				glDrawArrays(GL_LINES, 36, 2); // (0-35 is 36 vertices, 36-37 is 2vertices for ground)
			}
			for (int i = 0; i < 51; ++i) {
				mat4 groundWorldMatrix = translate(mat4(1.0f), vec3(-50.0f + 2 * i, -0.5f, 0.0f));
				ColorShader.setMat4("worldMatrix", groundWorldMatrix);
				glDrawArrays(GL_LINES, 38, 2); // (0-35 is 36 vertices, 38-39 is 2vertices for ground)
			}
		}


		ColorShader.setVec3("light[0].ambient", 1.0f, 1.0f, 1.0f);
		ColorShader.setVec3("light[0].diffuse", 1.0f, 1.0f, 1.0f);
		ColorShader.setVec3("light[0].specular", 1.0f, 1.0f, 1.0f);
		ColorShader.setVec3("material.ambient", 1.0f, 1.0f, 1.0f);
		ColorShader.setVec3("material.diffuse", 1.0f, 1.0f, 1.0f);
		//bullet
		if (scriptRender) {
			pillarSpecialMatrix = translate(mat4(1.0f), bulletPosition) * scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));
			ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
			glDrawArrays(carMode, 0, 36);
		}
		//CAR LIGHT
		if (carLightRender) { // SHINY LIGHT
			pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(1.425f, -2.45f, 0.3f)) * scale(mat4(1.0f), vec3(0.05f, 0.12f, 0.12f));
			ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
			glDrawArrays(carMode, 0, 36);
			pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(-1.425f, -2.45f, 0.3f)) * scale(mat4(1.0f), vec3(0.05f, 0.12f, 0.12f));
			ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
			glDrawArrays(carMode, 0, 36);
			pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(1.425f, -2.45f, -0.3f)) * scale(mat4(1.0f), vec3(0.05f, 0.12f, 0.12f));
			ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
			glDrawArrays(carMode, 0, 36);
			pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(-1.425f, -2.45f, -0.3f)) * scale(mat4(1.0f), vec3(0.05f, 0.12f, 0.12f));
			ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
			glDrawArrays(carMode, 0, 36);
		}
		pillarSpecialMatrix = translate(mat4(1.0f), lightPos) * scale(mat4(1.0f), vec3(2.0f, 2.0f, 2.0f));//light source
		ColorShader.setMat4("worldMatrix", pillarSpecialMatrix);
		glDrawArrays(carMode, 0, 36);


		//draw model
		modelShader.use();
		modelShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		modelShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
		modelShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		modelShader.setVec3("light.position", lightPos);
		modelShader.setVec3("viewPos", cameraPosition);

		pillarSpecialMatrix = translate(currentSelfRotateMatrix, vec3(0.0f, -2.3f, 0.0f)) * scale(mat4(1.0f), vec3(0.05f, 0.05f, 0.05f)) * rotate(glm::mat4(1.0f), radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
		modelShader.setMat4("model", pillarSpecialMatrix);
		santa.Draw(modelShader);

		pillarSpecialMatrix = translate(mat4(1.0f), vec3(-20.0f, 0.0f, 30.0f)) * scale(mat4(1.0f), vec3(0.05f, 0.05f, 0.05f));
		modelShader.setMat4("model", pillarSpecialMatrix);
		spider.Draw(modelShader);

		pillarSpecialMatrix = translate(mat4(1.0f), vec3(30.0f, 0.0f, 20.0f)) * scale(mat4(1.0f), vec3(0.5f, 0.5f,0.5f)) * rotate(glm::mat4(1.0f), radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
		modelShader.setMat4("model", pillarSpecialMatrix);
		house.Draw(modelShader);

		pillarSpecialMatrix = translate(mat4(1.0f), vec3(-20.0f, 0.0f, -40.0f)) * scale(mat4(1.0f), vec3(0.25f, 0.25f, 0.25f)) * rotate(glm::mat4(1.0f), radians(-90.0f), vec3(1.0f, 0.0f, 0.0f)) * rotate(glm::mat4(1.0f), radians(-90.0f), vec3(0.0f, 0.0f, 1.0f));
		modelShader.setMat4("model", pillarSpecialMatrix);
		dog.Draw(modelShader);

		pillarSpecialMatrix = translate(mat4(1.0f), vec3(-40.0f, 0.0f, 40.0f)) * scale(mat4(1.0f), vec3(0.1f, 0.1f, 0.1f)) * rotate(glm::mat4(1.0f), radians(-250.0f), vec3(0.0f, 1.0f, 0.0f));
		modelShader.setMat4("model", pillarSpecialMatrix);
		awp.Draw(modelShader);



		ColorShader.use();

		// End Frame
		glfwSwapBuffers(window);   //double buffer
		glfwPollEvents();

		// Handle inputs
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);




		//mousePosition
		double mousePosX, mousePosY;
		glfwGetCursorPos(window, &mousePosX, &mousePosY);

		double dx = mousePosX - lastMousePosX;
		double dy = mousePosY - lastMousePosY;

		lastMousePosX = mousePosX;
		lastMousePosY = mousePosY;


		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // move camera to the left
		{
			carPosition = carPosition + 0.25f * carVector;
			carForwardMove += 0.25f;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // move camera to the right
		{
			carDirection -= 1.0f;
			carVector = vec3(sin(radians(carDirection)), 0.0f, cos(radians(carDirection)));
			if (carLateralMove > -0.6f)
				carLateralMove -= 0.1f;
			else {
				carLateralMove = -0.6f;
			}
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // move camera up
		{
			carForwardMove -= 0.25f;
			carPosition = carPosition - 0.25f * carVector;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			carDirection += 1.0f;
			carVector = vec3(sin(radians(carDirection)), 0.0f, cos(radians(carDirection)));
			if (carLateralMove < 0.6f)
				carLateralMove += 0.1f;
			else {
				carLateralMove = 0.6;
			}
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE&&scriptRender!=true)
		{
			if (carLateralMove <= -0.05f)
				carLateralMove += 0.05f;
			else if (carLateralMove >= 0.05f)
				carLateralMove -= 0.05f;
			else
				carLateralMove = 0.0f;
		}

		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		{
			if (textureFlag == true)
			{
				if (textureRender == true)
					textureRender = false;
				else
					textureRender = true;
				textureFlag = false;
			}
		}

		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE)
		{
			textureFlag = true;
		}
		if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		{
			if (shadowFlag == true)
			{
				if (shadowRender == true)
					shadowRender = false;
				else
					shadowRender = true;
				shadowFlag = false;
			}
		}

		if (glfwGetKey(window, GLFW_KEY_V) == GLFW_RELEASE)
		{
			shadowFlag = true;
		}

		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		{
			if (firstPersonFlag == true)
			{
				if (firstPersonRender == true)
					firstPersonRender = false;
				else
					firstPersonRender = true;
				firstPersonFlag = false;
			}
		}

		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE)
		{
			firstPersonFlag = true;
		}

		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		{
			if (carLightFlag == true)
			{
				if (carLightRender == true)
					carLightRender = false;
				else
					carLightRender = true;
				carLightFlag = false;
			}
		}

		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE)
		{
			carLightFlag = true;
		}

		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{
			if (scriptFlag == true)
			{
				if (scriptRender == true) {
					bulletRotate = 0.0f;
					scriptRender = false;
					ISoundEngine* bulletEngine = createIrrKlangDevice();
				}
				else {
					scriptRender = true;
					scriptCounter = 0;
					carPosition = vec3(-50.0f + carSize, 0.0f, -50.0f + carSize);
					carSize = 1.5f;
					carLateralMove = 0.0f;
					carDirection = 90.0f;
					bulletPosition = vec3(-30.0f, 1.0f, 35.0f);
					carVector = vec3(sin(radians(carDirection)), 0.0f, cos(radians(carDirection)));
				}
				scriptFlag = false;
			}
		}

		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_RELEASE)
		{
			
			scriptFlag = true;
		}


		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			if (spaceFlag == true) 
			{
				carPosition = vec3(RandomNumber(-50.0f+carSize, 50.0f-carSize),0.0f, RandomNumber(-50.0f + carSize, 50.0f - carSize));
				spaceFlag = false;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
		{
			spaceFlag = true;
		}


	

		//car mode
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) 
		{
			carMode = GL_POINTS;
		}
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			carMode = GL_LINE_STRIP;
		}
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		{
			carMode = GL_TRIANGLES;
		}
		//car Size
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		{
			carSize += 0.1f;
		}

		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		{
			if (carSize > 0)
				carSize -= 0.1f;
			else
				carSize = carSize;
		}
		//rotate camera
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
{
	cameraRotate += 0.05f;
}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			cameraRotate -= 0.05f;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			cameraRotate += 0.05f;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			cameraRotate -= 0.05f;
		}
		//translate camera
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		{
			cameraPosition += vec3(0.5f, 0.0f, 0.0f);
			cameraLookAt += vec3(0.5f, 0.0f, 0.0f);
		}
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		{
			cameraPosition -= vec3(0.5f, 0.0f, 0.0f);
			cameraLookAt -= vec3(0.5f, 0.0f, 0.0f);
		}
		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		{
			cameraPosition += vec3(0.0f, 0.0f, 0.5f);
			cameraLookAt += vec3(0.0f, 0.0f, 0.5f);
		}
		if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		{
			cameraPosition -= vec3(0.0f, 0.0f, 0.5f);
			cameraLookAt -= vec3(0.0f, 0.0f, 0.5f);
		}
		//everything to initial
		if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)
		{
			cameraPosition = vec3(-60.0f, 25.0f, 0.0f);
			cameraLookAt = vec3(0.0f, 0.0f, 0.0f);
			cameraRotate = 0.0f;
			cameraZoom = 1.0f;
		}
		//zoom
		if (lastMouseLeftState == GLFW_RELEASE && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			if (cameraZoom >= 0.1f)
				cameraZoom = cameraZoom + 0.003 * dy;
			else
				cameraZoom = 0.1f;
		}
		//pan
		if (lastMouseLeftState == GLFW_RELEASE && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			cameraRotate += 0.003 * dx;
		}
		//tilt
		if (lastMouseLeftState == GLFW_RELEASE && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
		{
			cameraTilt += 0.003 * dy;
		}
		mat4 viewMatrix(1.0f);
		
		if (!firstPersonRender) {
			viewMatrix = lookAt(cameraPosition, cameraLookAt, cameraUp) * rotate(mat4(1.0f), cameraTilt, vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(cameraZoom, cameraZoom, cameraZoom)) * rotate(mat4(1.0f), cameraRotate, vec3(0.0f, 1.0f, 0.0f));
		}
		else {
			viewMatrix = lookAt(carPosition, carPosition + carVector - vec3(0.0f, 0.5f, 0.0f), cameraUp) * translate(mat4(1.0f), vec3(0.0f, -1.5 * carSize, 0.0f));
		}
		
		
		
		
		ColorShader.setMat4("viewMatrix", viewMatrix);
		TextureShader.use();
		TextureShader.setMat4("viewMatrix", viewMatrix);
		modelShader.use();
		modelShader.setMat4("view", viewMatrix);

		
		
		
		
	}
		

	// Shutdown GLFW
	glfwTerminate();

	return 0;
}

