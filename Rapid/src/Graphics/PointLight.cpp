#include "PointLight.h"

namespace Rapid {	namespace Graphics {

	PointLight::PointLight() : Light()
	{
		position = glm::vec3(0.0f, 0.0f, 0.0f);
		constant = 1.0f;
		linear = 0.0f;
		exponent = 0.0f;
	}

	PointLight::PointLight(GLuint shadowWidth, GLuint shadowHeight,
		GLfloat near, GLfloat far,
		GLfloat red, GLfloat green, GLfloat blue,
		GLfloat intensity, GLfloat dIntensity
		, GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat con, GLfloat lin, GLfloat exp) : Light(shadowWidth, shadowHeight, red, green,blue, intensity, dIntensity)
	{
		position = glm::vec3(xPos, yPos, zPos);
		constant = con;
		linear = lin;
		exponent = exp;

		farPlane = far;

		float aspect = (float)shadowWidth / (float)shadowHeight;

		lightProj = glm::perspective(glm::radians(90.0f), aspect, near, farPlane);

		shadowMap = new OmniShadowMap();
		shadowMap->Init(shadowWidth, shadowHeight);
	}

	PointLight::~PointLight()
	{
		
	}

	GLfloat PointLight::GetFarPlane()
	{
		return farPlane;
	}

	glm::vec3 PointLight::GetPosition()
	{
		return position;
	}

	std::vector<glm::mat4> PointLight::CalculateLightTransform()
	{
		std::vector<glm::mat4> lightMatrices;
		lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
		lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
		lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

		return lightMatrices;
	}

	void PointLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation,
		GLuint positionLocation, GLuint constantLocation,
		GLuint linearLocation, GLuint exponentLocation)
	{
		glUniform3f(ambientColorLocation, color.x, color.y, color.z);
		glUniform1f(ambientIntensityLocation, ambientIntensity);
		glUniform1f(diffuseIntensityLocation, diffuseIntensity);
		glUniform3f(positionLocation, position.x, position.y, position.z);
		glUniform1f(constantLocation, constant);
		glUniform1f(linearLocation, linear);
		glUniform1f(exponentLocation, exponent);
	}

}}