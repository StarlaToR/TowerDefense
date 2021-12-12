#include "explosion.hpp"
#include <raylib.h>

void ExplosionParticle::drawParticle(Texture2D& asset, Tiles& tiles)
{
    DrawTexturePro(asset, tiles.tileCrops.at(154+counter/2), toRayLibRectangle(position*48+Vec2D(50,50), Vec2D(96,96)), Vector2{48,48}, 0, Fade(WHITE,1.0f-counter/16.0f));
    //DrawCircle(position.x*48+50,position.y*48+50,counter*6,Fade(GRAY,1.0f-counter/15.0f));
    
}

bool ExplosionParticle::shouldDelete()
{
    return counter>16;
}

void ExplosionParticle::updateParticle()
{
    counter++;
}