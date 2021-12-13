#include "enemyExplosion.hpp"
#include <raylib.h>

EnemyExplosionParticle::EnemyExplosionParticle(Vec2D pos)
{
    position = pos;
    counter = 0;
}

void EnemyExplosionParticle::drawParticle(Texture2D& asset, Tiles& tiles)
{
    if (counter >= 0) DrawTexturePro(asset, tiles.tileCrops.at(154+counter/4), toRayLibRectangle(position*48+Vec2D(50,50), Vec2D(96,96)), Vector2{48,48}, 0, Fade(WHITE,1.0f-counter/36.0f));
}

bool EnemyExplosionParticle::shouldDelete()
{
    return counter>31;
}

void EnemyExplosionParticle::updateParticle()
{
    counter++;
}