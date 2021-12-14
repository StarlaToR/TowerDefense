#pragma once

#include <raylib.h>
#include <cstddef>

#define VEC2_TO_RAYLIB_VECTOR2                                       \
    Vec2D(const Vector2& f) { x = f.x; y = f.y; }                        \
    operator Vector2() const { return Vector2{x,y}; }

#include "mathHelper.hpp"
#include "dataHolder.hpp"

Color getRGB(size_t frame);
float getFade(size_t frame);

Rectangle toRayLibRectangle(Vec2D origin, Vec2D rectSize);
void DrawTileMap(DataHolder& in, RenderType type);
void DrawSpecialTiles(DataHolder& in);
bool drawButton(const char* text, Vec2D pos, Vec2D size, Vec2D mousePos);
bool drawButtonMenu(DataHolder& in, const char* text, Vec2D textSize, Vec2D pos, Vec2D size, Vec2D mousePos);
bool drawButtonInvisible(Vec2D pos, Vec2D size, Vec2D mousePos);
void drawMapElements(DataHolder& in, bool editor);
void drawTowerUpgradeMenu(DataHolder& in, int& button);