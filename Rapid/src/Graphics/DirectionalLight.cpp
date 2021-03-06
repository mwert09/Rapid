#include "DirectionalLight.h"

namespace Rapid
{
	namespace Graphics
	{
		DirectionalLight::DirectionalLight() : Light()
		{
			direction = glm::vec3(0.0f, -1.0f, 0.0f);
			lightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 1.0f, 100.0f);
		}

		DirectionalLight::DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeight, GLfloat red, GLfloat green, GLfloat blue,
											GLfloat intensity, GLfloat dIntensity,
											GLfloat xDir, GLfloat yDir, GLfloat zDir) : Light(shadowWidth, shadowHeight, red,green,blue,intensity,dIntensity)
		{	
			direction = glm::vec3(xDir, yDir, zDir);
			lightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 1.0f, 100.0f);
		}

		DirectionalLight::~DirectionalLight()
		{

		}

		glm::mat4 DirectionalLight::CalculateLightTransform()
		{
			return lightProj * glm::lookAt(-direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		}

		void DirectionalLight::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation)
		{
			glUniform3f(ambientColorLocation, color.x, color.y, color.z);
			glUniform1f(ambientIntensityLocation, ambientIntensity);
			glUniform3f(directionLocation, direction.x, direction.y, direction.z);
			glUniform1f(diffuseIntensityLocation, diffuseIntensity);
		}

		void DirectionalLight::UpdateLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation)
		{
			glUniform3f(ambientColorLocation, color.x, color.y, color.z);
			glUniform1f(ambientIntensityLocation, ambientIntensity);
			glUniform3f(directionLocation, direction.x, direction.y, direction.z);
			glUniform1f(diffuseIntensityLocation, diffuseIntensity);
		}

	}
}
