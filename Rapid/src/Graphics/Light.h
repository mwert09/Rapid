#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Rapid
{
	namespace Graphics
	{
		class Light
		{
		public:

			Light();
			Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);
			~Light();
			void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation);

		private:
			glm::vec3 color;
			GLfloat ambientIntensity;

			glm::vec3 direction;
			GLfloat diffuseIntensity;
		};
	}
}
