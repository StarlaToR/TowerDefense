#include "heal.hpp"
#include <raylib.h>

HealParticle::HealParticle(Vec2D pos)
{
    position = pos+Vec2D(GetRandomValue(-2,2),GetRandomValue(-2,2))/48.0f;
    alt = GetRandomValue(0,1);
}

void HealParticle::drawParticle(Texture2D& asset, Tiles& tiles)
{
    DrawTexturePro(asset, tiles.tileCrops.at(162+alt), toRayLibRectangle(position*48+Vec2D(50,50-counter), Vec2D(96,96)), Vector2{48, 48}, 0, Fade(LIME,0.7));
    //DrawCircle(position.x*48+50,position.y*48+50-counter,6,Fade(LIME,0.5));
}

bool HealParticle::shouldDelete()
{
    return counter>15;
}

void HealParticle::updateParticle()
{
    counter++;;
}