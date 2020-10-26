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
		private:
			// Window Dimensions - Pencere Boyutlari
			GLint m_WINDOW_WIDTH = 800;
			GLint m_WINDOW_HEIGHT = 600;
			const char* m_windowTitle;
			GLFWwindow* mainWindow;
			
		public:
			Window(const char* title, int width, int height);
			~Window();
			void Update() const;
			bool Closed() const;
			void Clear() const;
		private:
			bool Init();
		};
	}
}


