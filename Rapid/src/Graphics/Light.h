#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShadowMap.h"

namespace Rapid
{
	namespace Graphics
	{
		class Light
		{
		public:

			Light();
			Light(GLfloat shadowWidth, GLfloat shadowHeight, GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity, GLfloat dIntensity);
			~Light();

			ShadowMap* GetShadowMap() { return shadowMap; }

		public:
			glm::vec3 color;
			GLfloat ambientIntensity;
			GLfloat diffuseIntensity;

			glm::mat4 lightProj;
			
			ShadowMap* shadowMap;
		};
	}
}
