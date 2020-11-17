/*
 *                  Rapid Render Engine - Core
 *                          Mert Kilic
 *
 * 
 */
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <string.h>
#include <cmath>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/Graphics/Mesh.h"
#include "src/Graphics/Shader.h"
#include "src/Graphics/Window.h"
#include "src/Graphics/Camera.h"
#include "src/Graphics/Texture.h"
#include "src/Graphics/Light.h"

using namespace Rapid;
using namespace Graphics;

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow = Window("Rapid", 800, 600);
Camera camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.2f);

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

//Texture rockTexture = Texture("Textures/rocks.png");
Texture fabricTexture = Texture("Textures/fabric.png");
Texture brickTexture = Texture("Textures/brick.png");

Light mainLight;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

void CreateObjects()
{
	unsigned int indices[] = {
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2
	};
	
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,	 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,	 0.5f, 0.0f,	0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f,	 1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,	 0.5f, 1.0f,	0.0f, 0.0f, 0.0f
	};

	Utils::CalculateAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);
	
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles("Shaders/shader.vert", "Shaders/shader.frag");
	shaderList.push_back(*shader1);
}

int main()
{	
	CreateObjects();
	CreateShaders();

	//rockTexture.LoadTexture();
	fabricTexture.LoadTexture();
	brickTexture.LoadTexture();

	mainLight = Light(1.0f, 1.0f, 1.0f, 0.5f, 2.0f, -1.0f, -2.0f, 1.0f);
	
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	GLuint uniformAmbientIntensity = 0;
	GLuint uniformAmbientColour = 0;
	GLuint uniformDirection = 0;
	GLuint uniformDiffuseIntensity = 0;

	glm::mat4 projection = glm::mat4(1.0f);
	
	// Render Loop
	while (!mainWindow.Closed())
	{
		projection = glm::perspective(glm::radians(camera.GetFOV()), mainWindow.GetBufferWidth() / mainWindow.GetBufferHeight(), 0.1f, 100.0f);

		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;
		
		camera.InputControl(mainWindow.GetKeys(), deltaTime);
		camera.MouseControl(mainWindow.GetXChange(), mainWindow.GetYChange());
		camera.HandleScroll(mainWindow.GetXOffset(), mainWindow.GetYOffset());
		mainWindow.Clear();
		
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
		uniformAmbientColour = shaderList[0].GetAmbientColourLocation();
		uniformDirection = shaderList[0].GetDirectionLocation();
		uniformDiffuseIntensity = shaderList[0].GetDiffuseIntensityLocation();

		mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformDirection);
		
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
		brickTexture.UseTexture();
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		fabricTexture.UseTexture();
		meshList[1]->RenderMesh();
		
		glUseProgram(0);
		mainWindow.Update();
	}
	
	return 0;
}