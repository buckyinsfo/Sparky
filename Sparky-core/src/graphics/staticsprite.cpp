#include "staticsprite.h"

namespace sparky{
    namespace graphics {

        StaticSprite::StaticSprite(float x, float y, float width, float height, const maths::vec4& color, Shader& shader)
            : Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), color), m_shader(shader)
        {
            m_vertexArray = new VertexArray();
            GLfloat vertices[] =
            {
                0, 0, 0,
                0, height, 0,
                width, height, 0,
                width, 0, 0
            };

            GLfloat colors[] =
            {
                color.x, color.y, color.z, color.w,
                color.x, color.y, color.z, color.w,
                color.x, color.y, color.z, color.w,
                color.x, color.y, color.z, color.w
            };

            m_vertexArray->addBuffer(new Buffer(4 * 3, vertices, 3), 0);
            m_vertexArray->addBuffer(new Buffer(4 * 4, colors, 4), 1);

            GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
            m_indexBuffer = new IndexBuffer(indices, 6);
        }

        StaticSprite::~StaticSprite()
        {
            delete m_vertexArray;
            delete m_indexBuffer;
        }

    }
}