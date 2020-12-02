#include "Window.h"

namespace Rapid
{
	namespace Graphics
	{
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		Window::Window()
		{
			m_windowTitle = "";
			m_WINDOW_WIDTH = 800;
			m_WINDOW_HEIGHT = 600;
			if (!Init())
			{
				glfwTerminate();
			}
			for (size_t i = 0; i < 1024; i++)
			{
				keys[i] = false;
			}
			xChange = 0.0f;
			yChange = 0.0f;
			XOffsetChange = 0.0f;
			YOffsetChange = 0.0f;
			cursorMode = false;
			
		}
		
		Window::Window(const char* title, int width, int height)
		{
			m_windowTitle = title;
			m_WINDOW_WIDTH = width;
			m_WINDOW_HEIGHT = height;
			if(!Init())
			{
				glfwTerminate();
			}
			for(size_t i = 0; i < 1024;  i++)
			{
				keys[i] = false;
			}
			xChange = 0.0f;
			yChange = 0.0f;
			XOffsetChange = 0.0f;
			YOffsetChange = 0.0f;
			cursorMode = false;
			
		}

		Window::~Window()
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
			
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

			// Set Imgui context
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
			//io.ConfigViewportsNoAutoMerge = true;
			//io.ConfigViewportsNoTaskBarIcon = true;
			ImGui::StyleColorsDark();
			ImGuiStyle& style = ImGui::GetStyle();
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				style.WindowRounding = 0.0f;
				style.Colors[ImGuiCol_WindowBg].w = 1.0f;
			}
			ImGui_ImplGlfw_InitForOpenGL(mainWindow, true);
			ImGui_ImplOpenGL3_Init();

			// Handle key + mouse input - Tus ve mouse girislerini kontrol et
			CreateCallBacks();
			if(cursorMode)
			{
				glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			else
			{
				glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
			
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
			glfwSetWindowUserPointer(mainWindow, this);
			glfwSetWindowSizeCallback(mainWindow, framebuffer_size_callback);
			return true;
		}

		void Window::Update()
		{
			if (keys[GLFW_KEY_F1])
			{
				cursorMode = true;
			}
			else if(keys[GLFW_KEY_F2])
			{
				cursorMode = false;
			}

			if(cursorMode)
			{
				glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
			else
			{
				glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			
			
			// Handle Input
			glfwPollEvents();

			// Clear Window - Diger karenin olusmasi icin bu kareyi temizleme
			glClearColor(0.0f, 0.f, 0.f, 1.0f);

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			if (ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}
			glfwSwapBuffers(mainWindow);
		}

		int Window::GetWindowWidth()
		{
			return m_WINDOW_WIDTH;
		}

		int Window::GetWindowHeight()
		{
			return m_WINDOW_HEIGHT;
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

		void Window::CreateCallBacks()
		{
			glfwSetKeyCallback(mainWindow, HandleKeys);
			glfwSetCursorPosCallback(mainWindow, HandleMouse);
			glfwSetScrollCallback(mainWindow, HandleScroll);
		}

		GLfloat Window::GetXChange()
		{
			GLfloat theChange = xChange;
			xChange = 0.0f;
			return theChange;
		}

		GLfloat Window::GetYChange()
		{
			GLfloat theChange = yChange;
			yChange = 0.0f;
			return theChange;
		}

		GLfloat Window::GetXOffset()
		{
			GLfloat theChange = XOffsetChange;
			XOffsetChange = 0.0f;
			return theChange;
		}
		
		GLfloat Window::GetYOffset()
		{
			GLfloat theChange = YOffsetChange;
			YOffsetChange = 0.0f;
			return theChange;
		}
		
		void Window::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
		{
			Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
			if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			{
				glfwSetWindowShouldClose(window, GL_TRUE);
			}
			if(key >= 0 && key < 1024)
			{
				if(action == GLFW_PRESS)
				{
					theWindow->keys[key] = true;
				}
				else if(action == GLFW_RELEASE)
				{
					theWindow->keys[key] = false;
				}
			}
		}

		void Window::HandleMouse(GLFWwindow* window, double xPos, double yPos)
		{
			Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
			if(theWindow->mousedFirstMoved)
			{
				theWindow->lastX = xPos;
				theWindow->lastY = yPos;
				theWindow->mousedFirstMoved = false;
			}
			theWindow->xChange = xPos - theWindow->lastX;
			theWindow->yChange = theWindow->lastY - yPos;
			theWindow->lastX = xPos;
			theWindow->lastY = yPos;
		}

		void Window::HandleScroll(GLFWwindow* window, double xOffset, double yOffset)
		{
			Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));	
			theWindow->XOffsetChange = xOffset;
			theWindow->YOffsetChange = yOffset;
		}
		
	}
}