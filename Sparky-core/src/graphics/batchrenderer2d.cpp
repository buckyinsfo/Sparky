#include "batchrenderer2d.h"


namespace sparky {
    namespace graphics {

        BatchRenderer2D::BatchRenderer2D()
        {
            init();
        }

        BatchRenderer2D::~BatchRenderer2D()
        {
            delete m_IBO;
            glDeleteBuffers(1, &m_VBO);
        }

        void BatchRenderer2D::init()
        {
            glGenVertexArrays(1, &m_VAO);
            glGenBuffers(1, &m_VBO);

            glBindVertexArray(m_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        
            glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, 0, GL_DYNAMIC_DRAW);
            
            glEnableVertexAttribArray(SHADER_VERTEX_ID);
            glEnableVertexAttribArray(SHADER_COLOR_ID);

            glVertexAttribPointer(SHADER_VERTEX_ID, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
            glVertexAttribPointer(SHADER_COLOR_ID, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(sizeof(GLfloat) * 3));
            
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];

            int offset = 0;
            for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
            {
                indices[i + 0] = offset + 0;
                indices[i + 1] = offset + 1;
                indices[i + 2] = offset + 2;

                indices[i + 3] = offset + 2;
                indices[i + 4] = offset + 3;
                indices[i + 5] = offset + 0;

                offset += 4;
            }

            m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
                        
            glBindVertexArray(0);
        }
        
        void BatchRenderer2D::begin()
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        }

        void BatchRenderer2D::submit(const Renderable2D* renderable)
        {
            const maths::vec3& position = renderable->getPosition();
            const maths::vec2& size = renderable->getSize();
            const maths::vec4& color = renderable->getColor();

            m_buffer->vertex = position;
            m_buffer->color = color;
            m_buffer++;

            m_buffer->vertex = maths::vec3(position.x, position.y + size.y, position.z);
            m_buffer->color = color;
            m_buffer++;

            m_buffer->vertex = maths::vec3(position.x + size.x, position.y + size.y, position.z);
            m_buffer->color = color;
            m_buffer++;

            m_buffer->vertex = maths::vec3(position.x + size.x, position.y, position.z);
            m_buffer->color = color;
            m_buffer++;

            m_indexCount += 6;
        }

        void BatchRenderer2D::end()
        {
            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void BatchRenderer2D::flush()
        {
            glBindVertexArray(m_VAO);
            m_IBO->bind();

            glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);

            m_IBO->unbind();
            glBindVertexArray(0);

            m_indexCount = 0;
        }

    }
}