#pragma once

#include <GL/glew.h>

namespace sparky {
    namespace graphics {
        namespace buffers {

            class IndexBuffer
            {
            private:
                GLuint m_bufferID;
                GLuint m_count;

            public:
                IndexBuffer(GLsizei count, GLushort* data);

                void bind() const;
                void unbind() const;

                inline GLuint getCount() const { return m_count; }

            };
        }
    }
}