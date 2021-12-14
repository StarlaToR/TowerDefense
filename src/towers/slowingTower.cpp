#include "slowingTower.hpp"
#include "../particles/laser.hpp"

SlowingTower::SlowingTower(Vec2D pos, Sound* sound)
{
    damage = 3;
    range = 5;
    health = 100;
    maxHealth = 100;
    attackSpeed = 60;
    attackCooldown = 0;
    cost = 20;
    position = pos+Vec2D(0.5f,0.5f);
    rotation = 0;
    angularVelocity = 0.07f;
    level = 1;
    slowingTime = 120;
    textureID = 55;
    towerSound = sound;
}


bool SlowingTower::attack(Enemy* e, std::forward_list<Missile*>& missiles, std::forward_list<Particle*>& particles)
{
    Vec2D rPos = Vec2D(position.x+cosf(rotation)*0.6f, position.y+sinf(rotation)*0.6f);
    particles.push_front(new Laser( rPos, e->getPosition(), getColor()));
    e->getDamage(damage);
    e->setSlowed(slowingTime);
    attackCooldown = attackSpeed;
    return true;
}

int SlowingTower::getTexture()
{
    if (attackCooldown > (attackSpeed - 22))
    {
        return textureID+(attackSpeed-attackCooldown)/2;
    }
    return textureID;
}

void SlowingTower::upgrade()
{
    if(level < 4)
    {
        level += 1;
        slowingTime += 30;
        attackSpeed -= 10;
        textureID += 11;
    }
}