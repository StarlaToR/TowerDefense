#include "direction.hpp"

Direction::Direction() : dir(0)
{
}

Direction::Direction(int value) : dir(value%4)
{
}

Direction::~Direction()
{
}

Vec2D Direction::getFowardTile(Vec2D pos)
{
    return pos + Vec2D((dir==1)-(dir==3),(dir==0)-(dir==2));
}

int Direction::getOpposite()
{
    return (dir+2)%4;
}

int Direction::getRight()
{
    return (dir+1)%4;
}

int Direction::getLeft()
{
    return (dir+3)%4;
}