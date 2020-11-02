#include "Window.h"

namespace Rapid
{
	namespace Graphics
	{
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		
		Window::Window(const char* title, int width, int height)
		{
			m_windowTitle = title;
			m_WINDOW_WIDTH = width;
			m_WINDOW_HEIGHT = height;
			if(!Init())
			{
				glfwTerminate();
			}
		}

		Window::~Window()
		{
			glfwDestroyWindow(mainWindow);
			glfwTerminate();
		}

		bool Window::Init()
		{
			// Initialize GLFW - GLFW'i hazirla
			if (!glfwInit())
			{
				std::cout << "GLFW initialisation failed! - GLFW hazirlanamadi!" << std::endl;
				return false;
			}
			// Setup GLFW window properties - Pencere ozelliklerini hazirla
			// OpenGL version - OpenGL versiyonu
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			// Core Profile - Geri donus uyumlu degil
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			// Allow forward compatibility - Ileri uyumlu
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			
			// Create Window - Pencere olustur
			mainWindow = glfwCreateWindow(m_WINDOW_WIDTH, m_WINDOW_HEIGHT, m_windowTitle, NULL, NULL);
			if (!mainWindow)
			{
				std::cout << "GLFW window creation failed! - GLFW pencere olusturulamadi!" << std::endl;
				return false;
			}

			glfwGetFramebufferSize(mainWindow, &m_bufferWidth, &m_bufferHeight);

			// Set context for GLEW - GLEW baglami
			glfwMakeContextCurrent(mainWindow);

			// Allow modern extension features - modern opengl icin gerekli fonksiyonlari glew ile izinlendir
			glewExperimental = GL_TRUE;

			// Initialise GLEW
			if (glewInit() != GLEW_OK)
			{
				std::cout << "GLEW initialisation failed! - GLEW hazirlanamadi!" << std::endl;
				glfwDestroyWindow(mainWindow);
				glfwTerminate();
				return false;
			}
			glEnable(GL_DEPTH_TEST);
			glViewport(0, 0, m_bufferWidth, m_bufferHeight);
			glfwSetWindowSizeCallback(mainWindow, framebuffer_size_callback);
			return true;
		}

		void Window::Update() const
		{
			// Handle Input
			glfwPollEvents();
			// Clear Window - Diger karenin olusmasi icin bu kareyi temizleme
			glClearColor(0.0f, 0.f, 0.f, 1.0f);
			
			glfwSwapBuffers(mainWindow);
		}

		bool Window::Closed() const
		{
			return glfwWindowShouldClose(mainWindow);
		}

		void Window::Clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
			// Setup wievport size - goruntu alanini hazirla
			glViewport(0, 0, width, height);
		}
	}
}