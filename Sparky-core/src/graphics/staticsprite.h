#pragma once

#include "renderable2d.h"

#include "shader.h"

namespace sparky {
    namespace graphics {
        class StaticSprite : public Renderable2D
        {
        private:
            VertexArray* m_vertexArray;
            IndexBuffer* m_indexBuffer;
            Shader& m_shader;

        public:
            StaticSprite(float x, float y, float width, float height, const maths::vec4& color, Shader& shader);
            ~StaticSprite();

            inline const VertexArray* getVAO() const { return m_vertexArray; }
            inline const IndexBuffer* getIBO() const { return m_indexBuffer; }

            inline Shader& getShader() const { return m_shader; }
        };
    }
}
