#include "shader.h"

namespace sparky {
	namespace graphics {

		Shader::Shader(const char* vertPath, const char* fragPath) :
			m_vertPath(vertPath), m_fragPath(fragPath)
		{
			m_shaderID = load();
		}
	
		Shader::~Shader()
		{
			glDeleteProgram(m_shaderID);
		}

		GLuint Shader::load()
		{
			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertPathStr = FileUtils::read_file(m_vertPath);
			std::string fragPathStr = FileUtils::read_file(m_fragPath);
			
			const char* vertSrc = vertPathStr.c_str();
			const char* fragSrc = fragPathStr.c_str();

			glShaderSource(vertex, 1, &vertSrc, NULL);
			glCompileShader(vertex);

			GLint result;
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				std::cout << "Failed to compile vertex shader!" << std::endl << &error[0] << std::endl;
				glDeleteShader(vertex);
				return 0;
			}

			glShaderSource(fragment, 1, &fragSrc, NULL);
			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				std::cout << "Failed to compile freagment shader!" << std::endl << &error[0] << std::endl;
				glDeleteShader(fragment);
				return 0;
			}

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);

			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

		GLint Shader::getUniformLocation(const GLchar* name)
		{
			return glGetUniformLocation(m_shaderID, name);
		}

		void Shader::setUniform1f(const GLchar* name, float val)
		{
			glUniform1f(getUniformLocation(name), val);
		}

		void Shader::setUniform1i(const GLchar* name, int val)
		{
			glUniform1i(getUniformLocation(name), val);
		}

		void Shader::setUniform2f(const GLchar* name, const maths::vec2& vec)
		{
			glUniform2f(getUniformLocation(name), vec.x, vec.y);
		}

		void Shader::setUniform3f(const GLchar* name, const maths::vec3& vec)
		{
			glUniform3f(getUniformLocation(name), vec.x, vec.y, vec.z);
		}
		
		void Shader::setUniform4f(const GLchar* name, const maths::vec4& vec)
		{
			glUniform4f(getUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
		}

		void Shader::setUniformMat4(const GLchar* name, const maths::mat4& matrix)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
		}
		
		void Shader::enable() const
		{
			glUseProgram(m_shaderID);
		}

		void Shader::disable() const
		{
			glUseProgram(0);
		}
	}
}	