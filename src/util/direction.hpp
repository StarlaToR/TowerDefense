#pragma once

#include "mathHelper.hpp"

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

class Direction
{
    public:
        char dir;

        Direction();
        Direction(char value);
        ~Direction();

        Vec2D getFowardTile(Vec2D pos);
        Direction getOpposite();
        Direction getRight();
        Direction getLeft();
};

float dirToAngle(char dir);
char angleToDir(float angle);
