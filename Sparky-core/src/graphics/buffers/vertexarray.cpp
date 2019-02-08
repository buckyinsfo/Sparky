#include "vertexarray.h"

namespace sparky {
    namespace graphics {
        
        VertexArray::VertexArray()
        {
            glGenVertexArrays(1, &m_arrayID);
        }

        VertexArray::~VertexArray()
        {
            for (std::size_t i = 0; i < m_buffers.size(); i++)
            {
                delete m_buffers[i];
            }
        }

        void VertexArray::addBuffer(Buffer* buffer, GLuint index)
        {
            bind();
            buffer->bind();
            glEnableVertexAttribArray(index);
            //glEnableVertexArrayAttrib(index);

            glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

            buffer->unbind();
            unbind();
        }

        void VertexArray::bind() const
        {
            glBindVertexArray(m_arrayID);
        }

        void VertexArray::unbind() const
        {
            glBindVertexArray(0);
        }
    }
}