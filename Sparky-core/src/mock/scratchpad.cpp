#include "scratchpad.h"

namespace sparky {
	namespace mock {

		extern const char* vertexShaderCode;
		extern const char* fragmentShaderCode;

		void message()
		{
			std::cout << "The mock package!" << std::endl;
		}

		void installShaders()
		{
			GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

			const char* adapter[1];
			adapter[0] = vertexShaderCode;
			glShaderSource(vertShaderID, 1, adapter, 0);
			adapter[0] = fragmentShaderCode;
			glShaderSource(fragShaderID, 1, adapter, 0);
			
			glCompileShader(vertShaderID);
			glCompileShader(fragShaderID);

			GLuint programID = glCreateProgram();
			glAttachShader(programID, vertShaderID);
			glAttachShader(programID, fragShaderID);
			glLinkProgram(programID);

			glUseProgram(programID);
		}

		int createGLWindow()
		{

			graphics::Window window("Sparky", 960, 540);
			glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

			GLfloat verticies[] =
			{
				+0.5f, +0.5f, 0.0f,
				+0.0f, +0.0f, +1.0f, +0.0f,
				-0.5f, +0.5f, 0.0f,
				+1.0f, +0.0f, +0.0f, +0.0f,
				-0.5f, -0.5f, 0.0f,
				+1.0f, +0.0f, +0.0f, +0.0f,

				//		+0.5f, +0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f,
				+0.0f, +1.0f, +0.0f, +0.0f,
				+0.5f, -0.5f, 0.0f,
				+0.0f, +1.0f, +0.0f, +0.0f,

						/*+0.5f, +0.5f,
						-0.5f, +0.5f,
						-0.5f, -0.5f,

						+0.5f, +0.5f,
						-0.5f, -0.5f,
						+0.5f, -0.5f,*/

						/*4, 3, 0,
						12, 3, 0,
						4, 6, 0,

						4, 6, 0,
						12, 6, 0,
						12, 3, 0*/

			};

			GLuint vboID;
			glGenBuffers(1, &vboID);
			glBindBuffer(GL_ARRAY_BUFFER, vboID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

			// Vertex
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, 0);

			// Color
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (char*)(sizeof(float) * 3));


			GLushort indices[] = { 0,1,2,0,3,4 };
			GLuint iboID;
			glGenBuffers(1, &iboID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


			installShaders();
			/*maths::mat4 ortho = maths::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
			graphics::Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
			shader.enable();
			*/
			////	glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderID, "pr_matrix"), 1, GL_FALSE, ortho.elements);
			//	shader.setUniformMat4("pr_matrix", ortho);
			//	shader.setUniformMat4("ml_matrix", maths::mat4::translation(maths::vec3(0.2f, 0.2f, 0.2f)));

			while (!window.closed())
			{
				//std::cout << window.getWidth() << ", " << window.getHeight() << std::endl;
				window.clear();


				#if 0
				double x, y;
				window.getMousePosition(x, y);
				std::cout << "Position: x = " << x << ", y = " << y << std::endl;

				if (window.isKeyPressed(GLFW_KEY_A))
				{
					std::cout << "Pressed!" << std::endl;
				}

				if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
				{
					std::cout << "Left Mouse Pressed!" << std::endl;
				}

				if (window.isKeyPressed(GLFW_KEY_A))
				{
					std::cout << "Pressed!" << std::endl;
				}

				glBegin(GL_QUADS);
				glVertex2f(-0.5f, -0.5f);
				glVertex2f(-0.5f, 0.5f);
				glVertex2f(0.5f, 0.5f);
				glVertex2f(0.5f, -0.5f);
				glEnd();
				#else
				//glDrawArrays(GL_TRIANGLES, 0, 6); 
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
				#endif
				window.update();
			}
			return 0; 
		}
	}
}