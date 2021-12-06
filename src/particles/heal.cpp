#include "heal.hpp"
#include <raylib.h>

HealParticle::HealParticle(Vec2D pos)
{
    position = pos+Vec2D(GetRandomValue(-2,2),GetRandomValue(-2,2))/48.0f;
}

void HealParticle::drawParticle()
{
    DrawCircle(position.x*48+50,position.y*48+50-counter,6,Fade(LIME,0.5));
    counter++;
}

bool HealParticle::shouldDelete()
{
    return counter>15;
}