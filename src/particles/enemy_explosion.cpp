#include "enemy_explosion.hpp"
#include <raylib.h>

EnemyExplosionParticle::EnemyExplosionParticle(Vec2D pos)
{
    position = pos + Vec2D(GetRandomValue(-100,100) / 350.0f, GetRandomValue(-100,100) / 350.0f);
    subColor = GetRandomValue(0,7);
    counter = GetRandomValue(-15,2);
}

void EnemyExplosionParticle::drawParticle()
{
    if (counter >= 0) DrawCircle(position.x*48+50,position.y*48+50,counter*0.8f+1,Fade(subColor == 0 ? RED : (subColor == 1 ? YELLOW : GRAY),1.0f-counter/15.0f));
}

bool EnemyExplosionParticle::shouldDelete()
{
    return counter>25;
}

void EnemyExplosionParticle::updateParticle()
{
    counter++;
}