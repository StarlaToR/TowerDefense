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