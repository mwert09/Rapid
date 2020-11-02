#pragma once

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace Rapid
{
	namespace Graphics
	{
		class Window
		{
		public:
		private:
			// Window Dimensions - Pencere Boyutlari
			GLint m_WINDOW_WIDTH = 800;
			GLint m_WINDOW_HEIGHT = 600;
			GLint m_bufferWidth, m_bufferHeight;
			const char* m_windowTitle;
			GLFWwindow* mainWindow;
			
		public:
			Window(const char* title, int width, int height);
			~Window();
			void Update() const;
			bool Closed() const;
			void Clear() const;
			GLfloat GetBufferWidth() { return m_bufferWidth; }
			GLfloat GetBufferHeight()	{ return m_bufferHeight; }
		private:
			bool Init();
		};
	}
}


