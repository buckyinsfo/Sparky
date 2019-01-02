#include "graphics/window.h"

#include <GLFW/glfw3.h>


int main()
{
	sparky::graphics::Window window("Sparky", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	while (!window.closed())
	{
		//std::cout << window.getWidth() << ", " << window.getHeight() << std::endl;
		window.clear();

		double x, y;
		window.getMousePosition(x, y);
		std::cout << "Position: x = " << x << ", y = " << y << std::endl;

#if 1
		if (window.isKeyPressed(GLFW_KEY_A))
		{
			std::cout << "Pressed!" << std::endl;
		}

		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			std::cout << "Left Mouse Pressed!" << std::endl;
		}

		if (window.isKeyPressed(GLFW_KEY_A) )
		{
			std::cout << "Pressed!"		<< std::endl;
		}

		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f,  0.5f);
		glVertex2f( 0.5f,  0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();
#else
		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
#endif
		window.update();
	}
	return 0;
}