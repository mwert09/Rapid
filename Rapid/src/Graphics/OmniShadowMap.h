#pragma once
#include "ShadowMap.h"
namespace Rapid
{
	namespace Graphics
	{
		class OmniShadowMap :
			public ShadowMap
		{
		public:
			OmniShadowMap();
			~OmniShadowMap();

			bool Init(GLuint width, GLuint heigth);
			void Write();
			void Read(GLenum TextureUnit);
			
		};


	}
}
