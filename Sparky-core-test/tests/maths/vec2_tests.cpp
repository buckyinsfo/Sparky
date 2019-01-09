#include "pch.h"

#include <string>

using namespace sparky;
using namespace maths;

TEST(vec2, init) {

	vec2 a(1.0f, 2.0f);
	vec2 b(1.0f, 2.0f);

	vec2 c = a + b;
	std::cout << c << std::endl;
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}