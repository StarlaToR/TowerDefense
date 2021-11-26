#pragma once

#include <raylib.h>
#include <cstddef>

#define VEC2_TO_RAYLIB_VECTOR2                                       \
    Vec2D(const Vector2& f) { x = f.x; y = f.y; }                        \
    operator Vector2() const { return Vector2{x,y}; }

#include "mathHelper.hpp"
#include "dataHolder.hpp"

enum RenderType : char
{
    NORMAL = 0,
    EXTENDED,
    BORDER,
    DEBUG,
};

Color getRGB(size_t frame);
float getFade(size_t frame);

Rectangle toRayLibRectangle(Vec2D origin, Vec2D rectSize);
void DrawTileMap(DataHolder* in, RenderType type);