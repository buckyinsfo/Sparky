#include "scratchpad.h"

namespace sparky {
	namespace mock {

		extern const char* vertexShaderCode;
		extern const char* fragmentShaderCode;

		const unsigned int MAX_TRIS = 20;
		const unsigned int VERTS_PER_TRI = 3;
		const unsigned int FLOATS_PER_VERT = 6;
		const unsigned int STRIDE = VERTS_PER_TRI * FLOATS_PER_VERT * sizeof(float);
				
		void message()
		{
			std::cout << "The mock package!" << std::endl;
		}

		bool checkStatus(GLuint objectID, PFNGLGETSHADERIVPROC objPropGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogProc, GLenum statusType)
		{
			bool bReturn = true;
			GLint status;
			objPropGetterFunc(objectID, statusType, &status);
			if (status != GL_TRUE)
			{
				GLint logLen;
				objPropGetterFunc(objectID, GL_INFO_LOG_LENGTH, &logLen);
				GLchar* buffer = new GLchar[logLen];
				GLsizei bufferSize;
				getInfoLogProc(objectID, logLen, &bufferSize, buffer);

				const char* str = status == GL_COMPILE_STATUS ? "compile" : "link";
				std::cout << "CheckStatus object(" << str << ") error: " << buffer << std::endl;
				delete[] buffer;
				bReturn = false;
			}
			return bReturn;
		}
		bool checkShaderStatus(GLuint shaderID)
		{
			return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
		}

		bool checkProgramStatus(GLuint programID)
		{
			return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
		}

		void g_useShaders()
		{
			GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

			const GLchar* adapter[1];
			adapter[0] = vertexShaderCode;
			glShaderSource(vertShaderID, 1, adapter, 0);
			adapter[0] = fragmentShaderCode;
			glShaderSource(fragShaderID, 1, adapter, 0);
			
			glCompileShader(vertShaderID);
			glCompileShader(fragShaderID);

			if (!checkShaderStatus(vertShaderID) || !checkShaderStatus(fragShaderID))
			{
				return;
			}

			GLuint programID = glCreateProgram();
			glAttachShader(programID, vertShaderID);
			glAttachShader(programID, fragShaderID);
			glLinkProgram(programID);

			if (!checkProgramStatus(programID))
			{
				return;
			}

			glUseProgram(programID);
		}

		void createOpenGLBuffer()
		{
			GLuint vboID;
			glGenBuffers(1, &vboID);
			glBindBuffer(GL_ARRAY_BUFFER, vboID);
			glBufferData(GL_ARRAY_BUFFER, MAX_TRIS * STRIDE, NULL, GL_STATIC_DRAW);

			// Vertex
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
			
			// Color
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));
		}

		int sendTriangleToScreen(int count)
		{
			if (count >= MAX_TRIS)
				return count;
			
			const GLfloat X_DELTA = 0.1f;
			const GLfloat X_NEW = -1 + count + X_DELTA;
			
			GLfloat theTri[] = {
				X_NEW, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f,
						 
				X_NEW + X_DELTA, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f,
						 
				X_NEW, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f,
			};
			glBufferSubData(GL_ARRAY_BUFFER, MAX_TRIS * STRIDE, STRIDE, theTri);

			return ++count;
		}

        int createGLWindow3()
		{
			graphics::Window window("Sparky", 960, 540);
			glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

			// Must be called after window is created.
			glEnable(GL_DEPTH_TEST);


			createOpenGLBuffer();

			int count = 0;
			while (!window.closed())
			{
				window.clear();
				
				count = sendTriangleToScreen(count);

				//glClear(GL_DEPTH_BUFFER_BIT);
				
				glDrawArrays(GL_TRIANGLES, 0, 3);
				

				window.update();
			}
			return 0;
		}

		int createGLWindow2()
		{
			graphics::Window window("Sparky", 960, 540);
			glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

			// Must be called after window is created.
			glEnable(GL_DEPTH_TEST);

			const float RED_TRIANGLE_Z = +0.1f;
			const float GREEN_TRIANGLE_Z = -0.5f;
			GLfloat verticies[] =
			{
				-0.5f, +0.5f, GREEN_TRIANGLE_Z,
				+0.0f, +1.0f, +0.0f, +0.0f,
				+0.0f, +0.5f, GREEN_TRIANGLE_Z,
				+0.0f, +1.0f, +0.0f, +0.0f,
				+0.0f, -0.5f, GREEN_TRIANGLE_Z,
				+0.0f, +1.0f, +0.0f, +0.0f,
				
				+0.0f, +0.5f, -0.6f/*RED_TRIANGLE_Z*/,
				+1.0f, +0.0f, +0.0f, +0.0f,
				-0.5f, -0.5f, RED_TRIANGLE_Z,
				+1.0f, +0.0f, +0.0f, +0.0f,
				+0.5f, -0.5f, RED_TRIANGLE_Z,
				+1.0f, +0.0f, +0.0f, +0.0f,
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

			GLushort indices[] = { 0,1,2,3,4,5,};
			GLuint iboID;
			glGenBuffers(1, &iboID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			
			// ******************** Use shaders from Shader class
			//g_useShaders();
			//graphics::Shader shader("src/shaders/basic.vert.glsl", "src/shaders/basic.frag.glsl");
			graphics::Shader shader("src/shaders/mock.vert.glsl", "src/shaders/mock.frag.glsl");
			shader.enable();
			
			while (!window.closed())
			{
				window.clear();

				glDepthMask(true);
				glClear(GL_DEPTH_BUFFER_BIT);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

				window.update();
			}
			return 0;
		}

		int createGLWindow1()
		{
			graphics::Window window("Sparky", 960, 540);
			//glClearColor(0.2, 0.3f, 0.8f, 1.0f);

			GLfloat verticies[] =
			{
				0, 0, 0,
				8, 0, 0,
				0, 3, 0,
				0, 3, 0,
				8, 3, 0,
				8, 0, 0,
			};
			
			GLuint vboID;
			glGenBuffers(1, &vboID);
			glBindBuffer(GL_ARRAY_BUFFER, vboID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

			// Vertex
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
					
			maths::mat4 ortho = maths::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
			
			graphics::Shader shader("src/shaders/basic1.vert.glsl", "src/shaders/basic1.frag.glsl");
			shader.enable();
			
			shader.setUniformMat4("pr_matrix", ortho);
			shader.setUniformMat4("ml_matrix", maths::mat4::translate(maths::vec3(4, 3, 0)));
			//shader.setUniformMat4("ml_matrix", maths::mat4::rotate(45.0f, maths::vec3(0, 0, 1)));

			shader.setUniform2f("light_pos", maths::vec2(4.0f, 1.5f));
			shader.setUniform4f("colour", maths::vec4(0.2f, 0.3f, 0.8f, 1.0f));
			
			while (!window.closed())
			{
				window.clear();
                double x, y;
                window.getMousePosition(x, y);
                shader.setUniform2f("light_pos", maths::vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
                glDrawArrays(GL_TRIANGLES, 0, 6);
                window.update();
			}
			return 0;
		}

		int createGLWindow0()
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


// ******************** Use shaders from mock global functions
			g_useShaders();

			//maths::mat4 ortho = maths::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
			//graphics::Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
			//shader.enable();
			
			////	glUniformMatrix4fv(glGetUniformLocation(shader.m_shaderID, "pr_matrix"), 1, GL_FALSE, ortho.elements);
			//	shader.setUniformMat4("pr_matrix", ortho);
			//	shader.setUniformMat4("ml_matrix", maths::mat4::translate(maths::vec3(0.2f, 0.2f, 0.2f)));

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

        int createGLWindowWithBuffers()
        {
            graphics::Window window("Sparky", 960, 540);
            //glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

            maths::mat4 ortho = maths::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

            graphics::Shader shader("src/shaders/basic1.vert.glsl", "src/shaders/basic1.frag.glsl");
            shader.enable();

            shader.setUniformMat4("pr_matrix", ortho);
            shader.setUniformMat4("ml_matrix", maths::mat4::translate(maths::vec3(4, 3, 0)));
            
            shader.setUniform2f("light_pos", maths::vec2(4.0f, 1.5f));
            shader.setUniform4f("colour", maths::vec4(0.2f, 0.3f, 0.8f, 1.0f));
            
            graphics::Renderable2D sprite0(maths::vec3(5, 5, 0), maths::vec2(4, 4), maths::vec4(1, 0, 1, 1), shader);
            graphics::Renderable2D sprite1(maths::vec3(7, 1, 0), maths::vec2(2, 3), maths::vec4(0.2f, 0, 1, 1), shader);
            
            graphics::Simple2DRenderer renderer;

            while (!window.closed())
            {
                window.clear();
                
                double x, y;
                window.getMousePosition(x, y);
                shader.setUniform2f("light_pos", maths::vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
                
                renderer.submit(&sprite0);
                renderer.submit(&sprite1);
                renderer.flush();

                window.update();
            }
            return 0;
        }

		int createGLWindow()
		{
			glewInit();
			//glEnable(GL_DEPTH_TEST);
			//return createGLWindow0();		// Working 2 triangles w/ color and indicies.
			//return createGLWindow1();		// Working version at end of Episode 6.
			//return createGLWindow2();		// Working version with depth.
			//return createGLWindow3();		// Non-working version with animate triangle.

            return createGLWindowWithBuffers(); // Working version at end of Episode 7.
		}
	}
}