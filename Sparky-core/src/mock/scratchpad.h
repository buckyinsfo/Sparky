#pragma once

#include "../graphics/window.h"
#include "../graphics/shader.h"
#include "../maths/maths.h"
#include "../utils/fileutils.h"

#include "../graphics/buffers/buffer.h"
#include "../graphics/buffers/indexbuffer.h"
#include "../graphics/buffers/vertexarray.h"

#include "../graphics/renderer2d.h"
#include "../graphics/simple2drenderer.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

namespace sparky {
	namespace mock {
		
		void message();

		int createGLWindow();
	}
}