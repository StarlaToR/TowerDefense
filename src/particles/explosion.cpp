#include "explosion.hpp"
#include <raylib.h>

ExplosionParticle::ExplosionParticle()
{
    position = Vec2D();
    subColor = 0;
    counter = 0;
}

ExplosionParticle::ExplosionParticle( Vec2D pos)
{
    subColor = GetRandomValue(0,7);
    position = pos + Vec2D(GetRandomValue(-100,100) / 350.0f, GetRandomValue(-100,100) / 350.0f);
    counter = GetRandomValue(-15,2);
}

void ExplosionParticle::drawParticle(Texture2D& asset, Tiles& tiles)
{
    DrawCircle(position.x*48+50,position.y*48+50,counter*0.8f+1,Fade(subColor == 0 ? RED : (subColor == 1 ? YELLOW : GRAY),1.0f-counter/15.0f));
    
}

bool ExplosionParticle::shouldDelete()
{
    return counter>32;
}

void ExplosionParticle::updateParticle()
{
    counter++;
}