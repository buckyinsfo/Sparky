#include "window.h"

namespace sparky {
	namespace graphics {

		/*
		bool Window::m_keys[MAX_KEYS];
		bool Window::m_mouseButtons[MAX_BUTTONS];
		double Window::mx;
		double Window::my;
		*/
		void windowResize_callback(GLFWwindow *window, int width, int height)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			glViewport(0, 0, width, height);
		}

		void key_callback(GLFWwindow* win, int key, int scan_code, int action, int mods)
		{
			Window * window = (Window *)glfwGetWindowUserPointer(win);
			window->m_keys[key] = action != GLFW_RELEASE;
		}

		void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_mouseButtons[button] = action != GLFW_RELEASE;
		}

		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mx = xpos;
			win->my = ypos;
		}
		
		Window::Window(const char * title, int width, int height)
		{
			m_title = title;
			m_width = width;
			m_height = height;
			if (!init())
			{
				glfwTerminate();
			}

			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_keys[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				m_mouseButtons[i] = false;
			}
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		bool Window::init()
		{
			if (!glfwInit())
			{
				std::cout <<  "Failed to initialize GLFW." << std::endl;
				return false;
			}

			m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
			if (!m_window)
			{
				glfwTerminate();
				std::cout << "Failed to create GFLW window." << std::endl;
				return false;
			}

			glfwMakeContextCurrent(m_window);
			glfwSetWindowUserPointer(m_window, this);
			glfwSetWindowSizeCallback(m_window, windowResize_callback);
			glfwSetKeyCallback(m_window, key_callback);
			glfwSetMouseButtonCallback(m_window, mouse_button_callback);
			glfwSetCursorPosCallback(m_window, cursor_position_callback);

			
			if (glewInit() != GLEW_OK)
			{
				std::cout << "Failed to initialize GFEW." << std::endl;
				return false;
			}
			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
			return true;
		}

		bool Window::isKeyPressed(unsigned int keyCode) const
		{
			if (keyCode >= MAX_KEYS)
				return false;

			return m_keys[keyCode];
		}

		bool Window::isMouseButtonPressed(unsigned int button) const
		{
			if (button >= MAX_BUTTONS)
				return false;

			return m_mouseButtons[button];
		}

		void Window::getMousePosition(double& x, double& y) const
		{
			x = mx;
			y = my;	
		}
		
		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update()
		{
            GLenum error = glGetError();
            if (error != GL_NO_ERROR)
            {
                std::cout << "OpenGL Error: " << error << std::endl;
            }
            
            glfwPollEvents();
			glfwSwapBuffers(m_window);
		}

		bool Window::closed() const
		{
			return glfwWindowShouldClose(m_window);
		}
	}
}