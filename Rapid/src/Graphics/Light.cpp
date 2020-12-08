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
			shadowMap = new ShadowMap();
			shadowMap->Init(1280, 720);
		}
		
		Light::Light(GLfloat shadowWidth, GLfloat shadowHeight, GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity, GLfloat dIntensity)
		{
			shadowMap = new ShadowMap();
			shadowMap->Init(shadowWidth, shadowHeight);
			color = glm::vec3(red, green, blue);
			ambientIntensity = intensity;
			diffuseIntensity = dIntensity;
		}
		
		Light::~Light()
		{
			
		}
	
	}
}
