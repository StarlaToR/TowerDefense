#include "bigExplosion.hpp"
#include <raylib.h>

BigExplosionParticle::BigExplosionParticle(Vec2D pos)
{
    position = pos;
    counter = 0;
}

void BigExplosionParticle::drawParticle(Texture2D& asset, Tiles& tiles)
{
    DrawCircle(position.x*48+50,position.y*48+50,counter*6,Fade(GRAY,1.0f-counter/15.0f));
}

bool BigExplosionParticle::shouldDelete()
{
    return counter>15;
}

void BigExplosionParticle::updateParticle()
{
    counter++;
}