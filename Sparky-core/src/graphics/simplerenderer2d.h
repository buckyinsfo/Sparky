#pragma once

#include <deque>

#include "renderer2d.h"
#include "staticsprite.h"

namespace sparky {
    namespace graphics {

        class SimpleRenderer2D : public Renderer2D
        {
        private:
            std::deque<const StaticSprite*> m_renderQueue;
            
        public:
            void submit(const Renderable2D* renderable) override;
            void flush() override;
        };
    }
}
