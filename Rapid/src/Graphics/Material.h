#pragma once

#include <GL/glew.h>

namespace Rapid
{
	namespace Graphics
	{
		class Material
		{
		public:
			Material();
			Material(GLfloat sIntensity, GLfloat shine);
			~Material();

			void UseMaterial(GLuint sIntensityLocation, GLuint shineLocation);
		private:
			GLfloat specularIntensity;
			GLfloat shininess;
		};

	}
}

