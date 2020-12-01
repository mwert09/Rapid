#include "Material.h"

namespace Rapid
{
	namespace Graphics
	{
		Material::Material()
		{
			specularIntensity = 0.0f;
			shininess = 0;
			
		}

		Material::Material(GLfloat sIntensity, GLfloat shine)
		{
			specularIntensity = sIntensity;
			shininess = shine;
			
		}

		Material::~Material()
		{
			
		}

		void Material::UseMaterial(GLuint sIntensityLocation, GLuint shineLocation)
		{
			
			glUniform1f(sIntensityLocation, specularIntensity);
			glUniform1f(shineLocation, shininess);
		}

	}
}

