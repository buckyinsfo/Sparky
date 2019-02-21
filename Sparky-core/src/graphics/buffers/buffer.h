#pragma once

#include <GL/glew.h>

namespace sparky {
    namespace graphics {
    
        class Buffer
        {
        private:
            GLuint m_bufferID;
            GLuint m_componentCount;

        public:
            Buffer(GLsizei count, GLfloat* data, GLuint componentCount);
            ~Buffer();

            void bind() const;
            void unbind() const;

            inline GLuint getComponentCount() const { return m_componentCount; }

        };
    }
}