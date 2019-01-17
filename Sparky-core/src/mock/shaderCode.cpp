namespace sparky {
	namespace mock {

		const char* vertexShaderCode =
			"#version 330 core\r\n"
			""
			"in layout(location=0) vec3 position;"
			"in layout(location=1) vec4 vertexColor;"
			""
			"out vec4 theColor;"
			""
			"void main()"
			"{"
			"	gl_Position = vec4(position, 1.0);"
			"	theColor = vertexColor;"
			""
			""
			""
			"}";

		const char* fragmentShaderCode = 
			"#version 330 core\r\n"
			""
			"out vec4 deColor;"
			"in vec4 theColor;"
			""
			"void main()"
			"{"
			"	deColor = theColor;"
			""
			"}";

	}
}
