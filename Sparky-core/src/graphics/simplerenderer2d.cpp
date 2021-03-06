#include "simplerenderer2d.h"

namespace sparky {
    namespace graphics {

        void SimpleRenderer2D::submit(const Renderable2D* renderable)
        {
            m_renderQueue.push_back((StaticSprite*)renderable);
        }
        
        void SimpleRenderer2D::flush()
        {
            while (!m_renderQueue.empty())
            {
                const StaticSprite* sprite = (StaticSprite*)m_renderQueue.front();
                sprite->getVAO()->bind();
                sprite->getIBO()->bind();

                sprite->getShader().setUniformMat4("ml_matrix", maths::mat4::translate(sprite->getPosition()));
                glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, 0);
                
                sprite->getIBO()->unbind();
                sprite->getVAO()->unbind();

                m_renderQueue.pop_front();
            }
        }   
    }
}