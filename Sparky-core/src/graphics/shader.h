#pragma once

#include <iostream>
#include <vector>
#include <GL/glew.h>

#include "../maths/maths.h"
#include "../utils/fileutils.h"

namespace sparky {
	namespace graphics {

		class Shader
		{
		private:
			GLuint m_shaderID;
			const char* m_vertPath;
			const char* m_fragPath;
		public:
			Shader(const char* vertPath, const char* fragPath);
			~Shader();

			void setUniform1f(const GLchar* name, float val);
			void setUniform1i(const GLchar* name, int val);
			void setUniform2f(const GLchar* name, const maths::vec2& vec); 
			void setUniform3f(const GLchar* name, const maths::vec3& vec); 
			void setUniform4f(const GLchar* name, const maths::vec4& vec);
			void setUniformMat4(const GLchar* name, const maths::mat4& matrix);

			void enable() const;
			void disable() const;
		private:
			GLuint load();
			GLint getUniformLocation(const GLchar* name);
		};
	}
}
