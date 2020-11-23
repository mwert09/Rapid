#include "DirectionalLight.h"

namespace Rapid
{
	namespace Graphics
	{
		DirectionalLight::DirectionalLight() : Light()
		{
			direction = glm::vec3(0.0f, -1.0f, 0.0f);
		}

		DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
											GLfloat intensity, GLfloat dIntensity,
											GLfloat xDir, GLfloat yDir, GLfloat zDir) : Light(red,green,blue,intensity,dIntensity)
		{	
			direction = glm::vec3(xDir, yDir, zDir);
		}

		DirectionalLight::~DirectionalLight()
		{

		}

		void DirectionalLight::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation)
		{
			glUniform3f(ambientColorLocation, color.x, color.y, color.z);
			glUniform1f(ambientIntensityLocation, ambientIntensity);
			glUniform3f(directionLocation, direction.x, direction.y, direction.z);
			glUniform1f(diffuseIntensityLocation, diffuseIntensity);
		}
	}
}
