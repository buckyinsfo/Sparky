#include "simple2drenderer.h"

namespace sparky {
    namespace graphics {


        void Simple2DRenderer::submit(const Renderable2D* renderable)
        {
            m_renderQueue.push_back(renderable);
        }
        
        void Simple2DRenderer::flush()
        {
            while (!m_renderQueue.empty())
            {
                const Renderable2D* renderable = m_renderQueue.front();
                renderable->getVAO()->bind();
                renderable->getIBO()->bind();

                renderable->getShader().setUniformMat4("ml_matrix", maths::mat4::translate(renderable->getPosition()));
                glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, 0);

                renderable->getVAO()->unbind();
                renderable->getIBO()->unbind();

                m_renderQueue.pop_front();
            }
        }   
    }
}