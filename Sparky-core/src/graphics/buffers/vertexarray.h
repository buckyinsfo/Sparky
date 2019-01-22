#pragma once

#include <vector>
#include <GL/glew.h>

#include "buffer.h"

namespace sparky {
	namespace mock {

		class VertexArray
		{
		private:
			GLuint m_arrayID;
			std::vector<Buffer*> m_buffers;

			//GLuint m_count;
		
		public:
			//VertexArray(GLsizei count, GLushort data);
			VertexArray();
			~VertexArray();

			void addBuffer(Buffer* buffer, GLuint index);
			void bind() const;
			void unbind() const;
		};
	}
}