#include "Light.h"

namespace Rapid
{
	namespace Graphics
	{
		Light::Light()
		{
			color = glm::vec3(1.0f, 1.0f, 1.0f);
			ambientIntensity = 1.0f;
			diffuseIntensity = 0.0f;
		}
		
		Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity, GLfloat dIntensity)
		{
			color = glm::vec3(red, green, blue);
			ambientIntensity = intensity;
			diffuseIntensity = dIntensity;
		}
		
		Light::~Light()
		{
			
		}
	
	}
}
