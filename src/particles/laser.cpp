#include "laser.hpp"
#include <raylib.h>

Laser::Laser(Vec2D pos, Vec2D target, unsigned int col)
{
    position = pos;
    targetPos = target;
    color = col;
    counter = 0;
}

void Laser::drawParticle(Texture2D& asset, Tiles& tiles)
{
    DrawLineEx(Vector2{position.x*48+50,position.y*48+50},Vector2{targetPos.x*48+50,targetPos.y*48+50},1.5f, Fade(GetColor(color),1.0f-counter/7.0f));
}

bool Laser::shouldDelete()
{
    return counter>7;
}

void Laser::updateParticle()
{
    counter++;
}