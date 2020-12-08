#pragma once

#include <GL/glew.h>
#include <stdio.h>
#include "stb_image.h"

namespace Rapid
{
	namespace Graphics
	{
		class Texture
		{
		private:
			GLuint textureID;
			int width;
			int height;
			int bitDepth;
			const char* fileLocation;

		public:

		private:

		public:
			Texture();
			Texture(const char* fileLoc);
			~Texture();

			GLuint GetTextureID()
			{
				return textureID;
			}
			bool LoadTexture();
			bool LoadTextureA();
			void UseTexture();
			void ClearTexture();
		};

	}
}

