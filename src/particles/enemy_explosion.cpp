#include "enemy_explosion.hpp"
#include <raylib.h>

EnemyExplosionParticle::EnemyExplosionParticle(Vec2D pos)
{
    position = pos + Vec2D(GetRandomValue(-100,100), GetRandomValue(-4600,4600) / 100.0f);
    subColor = GetRandomValue(0,3);
    counter = GetRandomValue(-15,0);
}

void EnemyExplosionParticle::drawParticle()
{
    if (counter > 0) DrawCircle(position.x*48+50,position.y*48+50,counter*2.5f+2,Fade(subColor == 0 ? RED : (subColor == 1 ? YELLOW : GRAY),1.0f-counter/15.0f));
}

bool EnemyExplosionParticle::shouldDelete()
{
    return counter>15;
}

void EnemyExplosionParticle::updateParticle()
{
    counter++;
}