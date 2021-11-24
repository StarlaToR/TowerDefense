#pragma once

#include "mathHelper.hpp"

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

class Direction
{
    public:
        int dir;

        Direction();
        Direction(int value);
        ~Direction();

        Vec2D getFowardTile(Vec2D pos);
        int getOpposite();
        int getRight();
        int getLeft();
};