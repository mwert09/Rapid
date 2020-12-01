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

#include "src/Graphics/CommonValues.h"
#include "src/Graphics/Mesh.h"
#include "src/Graphics/Shader.h"
#include "src/Graphics/Window.h"
#include "src/Graphics/Camera.h"
#include "src/Graphics/Texture.h"
#include "src/Graphics/DirectionalLight.h"
#include "src/Graphics/SpotLight.h"
#include "src/Graphics/Material.h"
#include "src/Graphics/Model.h"

using namespace Rapid;
using namespace Graphics;

const float toRadians = 3.14159265f / 180.0f;


Window mainWindow = Window("Rapid", 1280, 720);
Camera camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 2.0f, 0.2f);

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

//Texture rockTexture = Texture("Textures/rocks.png");
Texture fabricTexture = Texture("Textures/fabric.png");
Texture brickTexture = Texture("Textures/brick.png");
Texture diffuseMap = Texture("Textures/container2.png");
Texture specularMap = Texture("Textures/container2_specular.png");

Material shinyMaterial;
Material dullMaterial;

Model carModel;
Model containerModel;
Model xWing;
Model BlackHawk;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

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
		-1.0f, -1.0f, -0.6f,	 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,	 0.5f, 0.0f,	0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -0.6f,	 1.0f, 0.0f,	0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,	 0.5f, 1.0f,	0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0,2,1,
		1,2,3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f,
	};

	Utils::CalculateAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* floor = new Mesh();
	floor->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(floor);
	
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
	fabricTexture.LoadTextureA();
	brickTexture.LoadTextureA();

	shinyMaterial = Material(1.0f, 32);
	dullMaterial = Material(0.3f, 4);

	containerModel = Model();
	containerModel.LoadModel("Models/Container.obj");

	BlackHawk = Model();
	BlackHawk.LoadModel("Models/uh60.obj");

	xWing = Model();
	xWing.LoadModel("Models/x-wing.obj");

	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f, 0.06f, 0.6f, -1.0f, -2.0f, 2.0f);
	
	unsigned int pointLightCount = 0;
	pointLights[0] = PointLight(0.0f, 1.0f, 0.0f, 0.0f, 0.1f, -4.0f, 0.0f, 0.0f, 0.3f, 0.2f, 0.1f);
	pointLightCount++;
	pointLights[1] = PointLight(0.0f, 0.0f, 1.0f, 0.0f, 0.1f, 4.0f, 2.0f, 0.0f, 0.3f, 0.1f, 0.1f);
	pointLightCount++;

	unsigned int spotLightCount = 0;
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.6f, 1.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.3f, 0.2f, 0.1f,
		20.0f);
	spotLightCount++;
	
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	GLuint uniformEyePosition = 0;
	GLuint uniformSpecularIntensity = 0;
	GLuint uniformShininess = 0;

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
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glm::vec3 lowerLight = camera.GetCameraPosition();
		lowerLight.y -= 0.4f;
		//spotLights[0].SetFlash(lowerLight, camera.GetCameraDirection());

		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);
		

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.GetCameraPosition().x, camera.GetCameraPosition().y, camera.GetCameraPosition().z);
		
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brickTexture.UseTexture();
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 4.0f, -2.5f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		fabricTexture.UseTexture();
		dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, -0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brickTexture.UseTexture();
		dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, -0.0f));
		model = glm::scale(model, glm::vec3(0.006f, 0.006f, 0.006f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		containerModel.RenderModel();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.0f, 2.0f, 0.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BlackHawk.RenderModel();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-7.0f, 0.0f, 10.0f));
		model = glm::scale(model, glm::vec3(0.006f, 0.006f, 0.006f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		xWing.RenderModel();
		
		glUseProgram(0);
		
		mainWindow.Update();
		
	}
	
	return 0;
}