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
#include "src/Graphics/SkyBox.h"

using namespace Rapid;
using namespace Graphics;

const float toRadians = 3.14159265f / 180.0f;

GLuint uniformProjection = 0;
GLuint uniformModel = 0;
GLuint uniformView = 0;
GLuint uniformEyePosition = 0;
GLuint uniformSpecularIntensity = 0;
GLuint uniformShininess = 0;
GLuint uniformDirectionalLightTransform = 0;
GLuint uniformOmniLightPos = 0;
GLuint uniformFarPlane = 0;

Window mainWindow = Window("Rapid", 1280, 720);
Camera camera;

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Shader directionalShadowShader;
Shader omniShadowShader;

Texture sandstone = Texture("Textures/sandstone.png");
Texture diffuseMap = Texture("Textures/container2.png");
Texture specularMap = Texture("Textures/container2_specular.png");
Texture ground = Texture("Textures/Sand_005_baseColor.jpg");

Material shinyMaterial;
Material dullMaterial;

Model containerModel;
Model BlackHawk;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

SkyBox skybox;

unsigned int pointLightCount = 0;
unsigned int spotLightCount = 0;

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

	directionalShadowShader = Shader();
	directionalShadowShader.CreateFromFiles("Shaders/directional_shadow_map.vert", "Shaders/directional_shadow_map.frag");
	omniShadowShader.CreateFromFiles("Shaders/omni_shadow_map.vert", "Shaders/omni_shadow_map.geom", "Shaders/omni_shadow_map.frag");
}

void RenderScene()
{
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(-3.0f, 1.0f, -50.5f));
	model = glm::scale(model, glm::vec3(10.4f, 5.4f, 5.4f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	sandstone.UseTexture();
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	meshList[0]->RenderMesh();

	/*model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 4.0f, -2.5f));
	//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	fabricTexture.UseTexture();
	dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	meshList[1]->RenderMesh();*/

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.0f));
	model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	ground.UseTexture();
	dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	meshList[2]->RenderMesh();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(6.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.006f, 0.006f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	containerModel.RenderModel();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-3.0f, 0.7f, 0.0f));
	model = glm::rotate(model, -90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	BlackHawk.RenderModel();

	/*model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-7.0f, 0.0f, 10.0f));
	model = glm::scale(model, glm::vec3(0.006f, 0.006f, 0.006f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	xWing.RenderModel();*/

}

void DirectionalShadowMapPass(DirectionalLight *light)
{
	directionalShadowShader.UseShader();
	light->GetShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);
	glm::mat4 lTransform = light->CalculateLightTransform();
	directionalShadowShader.SetDirectionalLightTransform(&lTransform);
	glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());
	uniformModel = directionalShadowShader.GetModelLocation();
	directionalShadowShader.Validate();
	RenderScene();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OmniShadowMapPass(PointLight* light)
{
	omniShadowShader.UseShader();
	glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());
	
	light->GetShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);
	
	uniformOmniLightPos = omniShadowShader.GetOmniLightPosLocation();
	uniformFarPlane = omniShadowShader.GetFarPlanePosLocation();

	glUniform3f(uniformOmniLightPos, light->GetPosition().x, light->GetPosition().y, light->GetPosition().z);
	glUniform1f(uniformFarPlane, light->GetFarPlane());

	omniShadowShader.SetLightMatrices(light->CalculateLightTransform());
	
	uniformModel = omniShadowShader.GetModelLocation();
	omniShadowShader.Validate();
	RenderScene();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{

	glViewport(0, 0, 1280, 720);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox.DrawSkyBox(viewMatrix, projectionMatrix);
	
	shaderList[0].UseShader();

	uniformModel = shaderList[0].GetModelLocation();
	uniformProjection = shaderList[0].GetProjectionLocation();
	uniformView = shaderList[0].GetViewLocation();
	uniformModel = shaderList[0].GetModelLocation();
	uniformEyePosition = shaderList[0].GetEyePositionLocation();
	uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
	uniformShininess = shaderList[0].GetShininessLocation();

	


	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniform3f(uniformEyePosition, camera.GetCameraPosition().x, camera.GetCameraPosition().y, camera.GetCameraPosition().z);

	shaderList[0].SetDirectionalLight(&mainLight);
	shaderList[0].SetPointLights(pointLights, pointLightCount, 3, 0);
	shaderList[0].SetSpotLights(spotLights, spotLightCount, 3 + pointLightCount, pointLightCount);
	glm::mat4 lightTransform = mainLight.CalculateLightTransform();
	shaderList[0].SetDirectionalLightTransform(&lightTransform);

	mainLight.GetShadowMap()->Read(GL_TEXTURE2);
	shaderList[0].SetTexture(1);
	shaderList[0].SetDirectionalShadowMap(2);

	
	glm::vec3 lowerLight = camera.GetCameraPosition();
	lowerLight.y -= 0.3f;
	spotLights[0].SetFlash(lowerLight, camera.GetCameraDirection());

	shaderList[0].Validate();
	RenderScene();
}

int main()
{
	
	camera = Camera(glm::vec3(-2.0f, 3.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 3.0f, 0.5f);
	CreateObjects();
	CreateShaders();
	
	sandstone.LoadTexture();
	ground.LoadTextureA();

	shinyMaterial = Material(1.0f, 32);
	dullMaterial = Material(0.3f, 4);

	containerModel = Model();
	containerModel.LoadModel("Models/Container.obj");

	BlackHawk = Model();
	BlackHawk.LoadModel("Models/uh60.obj");
	
	float directionalLightRedValue = 1, directionalLightGreenValue = 1, directionalLightBlueValue = 1,
	directionalLightIntensity = 0.5f, directionalLightDiffuseIntensity = 0.3f,
	directionalLightXDir = 1, directionalLightYDir = 0, directionalLightZDir = 0.20f;
	
	mainLight = DirectionalLight(2048, 2048, 1.0, 1.0, 1.0,
		0.5, 0.3,
		0.0f, -7.0f, -1.0f);
	
	/*pointLights[0] = PointLight(1024, 1024, 0.01f, 100.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -4.0f, 3.0f, 0.0f, 0.3f, 0.1f, 0.1f);
	pointLightCount++;
	pointLights[1] = PointLight(1024, 1024, 0.01f, 100.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 2.0f, 0.0f, 0.3f, 0.1f, 0.1f);
	pointLightCount++;*/

	
	spotLights[0] = SpotLight(1024, 1024, 0.01f, 100.0f, 1.0f, 1.0f, 1.0f,
		0.6f, 1.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.3f, 0.2f, 0.1f,
		20.0f);
	spotLightCount++;
	
	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/nightsky_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/nightsky_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/nightsky_up.tga");
	skyboxFaces.push_back("Textures/Skybox/nightsky_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/nightsky_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/nightsky_ft.tga");

	skybox = SkyBox(skyboxFaces);

	glm::mat4 projection = glm::mat4(1.0f);
	
	// Render Loop
	while (!mainWindow.Closed())
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{
			ImGui::Begin("Directional Light Settings");                          // Create a window called "Hello, world!" and append into it.

			if (ImGui::SliderFloat("Directional Light Intensity", &directionalLightIntensity, 0.0f, 1.0f) |  
				ImGui::SliderFloat("Directional Light Diffuse Intensity", &directionalLightDiffuseIntensity, 0.0f, 1.0f) |
				ImGui::SliderFloat("Directional Light Red Color", &directionalLightRedValue, 0.0f, 1.0f) |
				ImGui::SliderFloat("Directional Light Green Color", &directionalLightGreenValue, 0.0f, 1.0f) |
				ImGui::SliderFloat("Directional Light Blue Color", &directionalLightBlueValue, 0.0f, 1.0f) |
				ImGui::SliderFloat("Directional Light X Direction", &directionalLightXDir, -100.0f, 100.0f) | 
				ImGui::SliderFloat("Directional Light Y Direction", &directionalLightYDir, -100.0f, 100.0f) | 
				ImGui::SliderFloat("Directional Light Z Direction", &directionalLightZDir, -100.0f, 100.0f))
			{
				shaderList[0].UpdateDirectionalLight(&mainLight, directionalLightRedValue, directionalLightGreenValue, directionalLightBlueValue,
					directionalLightIntensity, directionalLightDiffuseIntensity, directionalLightXDir, directionalLightYDir, directionalLightZDir);
			}

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		{
			ImGui::Begin("Spot Light Settings");                          // Create a window called "Hello, world!" and append into it.

			if (ImGui::Checkbox("Toggle Spot Light", &spotLights[0].isOn))
			{
				shaderList[0].UpdateSpotLight(&spotLights[0], 0, 1.0, 1.0, 1.0, 0.6, 1.0, 0.0f, -1.0f, 0.0f);
			}

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		ImGui::Render();
		
		projection = glm::perspective(glm::radians(camera.GetFOV()), mainWindow.GetBufferWidth() / mainWindow.GetBufferHeight(), 0.1f, 100.0f);

		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		if(mainWindow.cursorMode)
		{
			camera.InputControl(mainWindow.GetKeys(), deltaTime);
			camera.MouseControl(mainWindow.GetXChange(), mainWindow.GetYChange());
			camera.HandleScroll(mainWindow.GetXOffset(), mainWindow.GetYOffset());
		}
		mainWindow.Clear();

		DirectionalShadowMapPass(&mainLight);
		for(size_t i = 0; i < pointLightCount; i++)
		{
			OmniShadowMapPass(&pointLights[i]);
		}

		for(size_t i = 0; i < spotLightCount; i++)
		{
			OmniShadowMapPass(&spotLights[i]);
		}
		RenderPass(camera.CalculateViewMatrix(), projection);
		
		glUseProgram(0);
		
		mainWindow.Update();
		
	}
	
	return 0;
}