#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"


inline float toRadians(float degrees)
{
	return 2.0f * degrees * ((float)M_PI / 360.0f);
}