#include "classicTower.hpp"

ClassicTower::ClassicTower(Vec2D pos, Sound* sound)
{
    position = pos+Vec2D(0.5f,0.5f);
    damage = 4;
    range = 3;
    health = 100;
    maxHealth = 100;
    attackSpeed = 40;
    attackCooldown = 0;
    cost = 5;
    rotation = 0;
    angularVelocity = 0.1f;
    level = 1;
    textureID = 121;
    towerSound = sound;
}

int ClassicTower::getTexture()
{
    if (attackCooldown > (attackSpeed - 14))
    {
        return textureID+(attackSpeed-attackCooldown)/2;
    }
    return textureID;
}

void ClassicTower::attack(Enemy* e, std::forward_list<Missile*>& missiles, std::forward_list<Particle*>& particles)
{
    e->getDamage(damage);
    attackCooldown = attackSpeed;
}

void ClassicTower::upgrade()
{
    if(level < 4)
    {
        level += 1;
        damage += 2;
        attackSpeed -= 5;
        textureID += 8;
    }
}