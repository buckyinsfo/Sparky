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
			GLuint programID = glCreateProgram();
			GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertPathStr = FileUtils::read_file(m_vertPath);
			std::string fragPathStr = FileUtils::read_file(m_fragPath);
			
			const char* vertSrc = vertPathStr.c_str();
			const char* fragSrc = fragPathStr.c_str();

			glShaderSource(vertexID, 1, &vertSrc, NULL);
			glCompileShader(vertexID);

			GLint result;
			glGetShaderiv(vertexID, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertexID, length, &length, &error[0]);
				std::cout << "Failed to compile vertex shader!" << std::endl << &error[0] << std::endl;
				glDeleteShader(vertexID);
				return 0;
			}

			glShaderSource(fragmentID, 1, &fragSrc, NULL);
			glCompileShader(fragmentID);

			glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(fragmentID, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragmentID, length, &length, &error[0]);
				std::cout << "Failed to compile fragment shader!" << std::endl << &error[0] << std::endl;
				glDeleteShader(fragmentID);
				return 0;
			}

			glAttachShader(programID, vertexID);
			glAttachShader(programID, fragmentID);

			glLinkProgram(programID);
			glValidateProgram(programID);

			glDeleteShader(vertexID);
			glDeleteShader(fragmentID);

			return programID;
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