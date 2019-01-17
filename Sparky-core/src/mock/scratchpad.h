#pragma once

#include "../graphics/window.h"
#include "../graphics/shader.h"
#include "../maths/maths.h"
#include "../utils/fileutils.h"

#include <GLFW/glfw3.h>

#include <direct.h>

#include <iostream>
#include <string>

namespace sparky {
	namespace mock {
		
		void message();

		int createGLWindow();
	}
}