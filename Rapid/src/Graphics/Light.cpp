#include "Light.h"

namespace Rapid
{
	namespace Graphics
	{
		Light::Light()
		{
			color = glm::vec3(1.0f, 1.0f, 1.0f);
			ambientIntensity = 1.0f;
		}
		
		Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity)
		{
			color = glm::vec3(red, green, blue);
			ambientIntensity = intensity;
		}
		
		Light::~Light()
		{
			
		}
		
		void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation)
		{
			glUniform3f(ambientColorLocation, color.x, color.y, color.z);
			glUniform1f(ambientIntensityLocation, ambientIntensity);
		}
	}
}
