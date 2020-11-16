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

			bool keys[1024];
			GLfloat lastX;
			GLfloat lastY;
			GLfloat xChange;
			GLfloat yChange;
			GLfloat XOffsetChange;
			GLfloat YOffsetChange;
			bool mousedFirstMoved;
			bool scrollFirstMoved;
			
		public:
			Window();
			Window(const char* title, int width, int height);
			~Window();
			void Update() const;
			bool Closed() const;
			void Clear() const;
			GLfloat GetBufferWidth() { return m_bufferWidth; }
			GLfloat GetBufferHeight()	{ return m_bufferHeight; }
			bool* GetKeys() { return keys; }
			GLfloat GetXChange();
			GLfloat GetYChange();
			GLfloat GetYOffset();
			GLfloat GetXOffset();
		private:
			bool Init();
			static void HandleKeys(GLFWwindow *window, int key, int code, int action, int mode);
			static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
			static void HandleScroll(GLFWwindow* window, double xOffset, double yOffset);
			void CreateCallBacks();
		};
	}
}


