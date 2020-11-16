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
			Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity);
			~Light();
			void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation);

		private:
			glm::vec3 color;
			GLfloat ambientIntensity;
		};
	}
}
