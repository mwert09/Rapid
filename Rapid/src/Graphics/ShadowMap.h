#pragma once

#include <iostream>
#include "gl/glew.h"

namespace Rapid {
	namespace Graphics {
		class ShadowMap
		{
		public:
			ShadowMap();
			~ShadowMap();

			virtual bool Init(GLuint width, GLuint heigth);
			virtual void Write();
			virtual void Read(GLenum textureUnit);

			GLuint GetShadowWidth() { return shadowWidth; }
			GLuint GetShadowHeight() { return shadowHeight; }

		protected:
			GLuint FBO, shadowMap;
			GLuint shadowWidth, shadowHeight;
		};

	}
}