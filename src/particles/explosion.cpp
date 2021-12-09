#include "explosion.hpp"
#include <raylib.h>

void ExplosionParticle::drawParticle()
{
    DrawCircle(position.x*48+50,position.y*48+50,counter*6,Fade(GRAY,1.0f-counter/15.0f));
    
}

bool ExplosionParticle::shouldDelete()
{
    return counter>15;
}

void ExplosionParticle::updateParticle()
{
    counter++;
}