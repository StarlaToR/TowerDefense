#include "direction.hpp"

Direction::Direction() : dir(0)
{
}

Direction::Direction(char value) : dir(value%4)
{
}

Direction::~Direction()
{
}

Vec2D Direction::getFowardTile(Vec2D pos)
{
    return pos + Vec2D((dir==1)-(dir==3),(dir==0)-(dir==2));
}

Direction Direction::getOpposite()
{
    return Direction((dir+2)%4);
}

Direction Direction::getRight()
{
    return Direction((dir+1)%4);
}

Direction Direction::getLeft()
{
    return Direction((dir+3)%4);
}

float dirToAngle(char dir)
{
    if (dir == 2)
        return M_PI/2;
    else if (dir == 1)
        return 0;
    else if (dir == 0)
        return 3*M_PI/2;
    else if (dir == 3)
        return M_PI;
    return 0;
}

char angleToDir(float angle)
{
    if (angle <= M_PI/2 + 0.001 && angle >= M_PI/2 - 0.001)
        return 2;
    else if (angle <= 0 + 0.001 && angle >= 0 - 0.001)
        return 1;
    else if (angle <= 3*M_PI/2 + 0.001 && angle >= 3*M_PI/2 - 0.001)
        return 0;
    else if (angle <= M_PI + 0.001 && angle >= M_PI - 0.001)
        return 3;
    return 0;
}