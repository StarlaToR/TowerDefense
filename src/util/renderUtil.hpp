#pragma once

#include <raylib.h>
#include <cstddef>
#include "mathHelper.hpp"

Color getRGB(size_t frame);
float getFade(size_t frame);

Rectangle toRayLibRectangle(Vec2D origin, Vec2D rectSize);