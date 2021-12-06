#include "explosiveTower.hpp"

ExplosiveTower::ExplosiveTower(Vec2D pos)
{
    damage = 15;
    range = 7;
    health = 150;
    maxHealth = 150;
    attackSpeed = 90;
    attackCooldown = 0;
    cost = 20;
    position = pos + Vec2D(0.5f,0.5f);
    rotation = 0;
    angularVelocity = 0.07f;
}

void ExplosiveTower::attack(Enemy* e, std::forward_list<Missile*>* missiles)
{
    missiles->push_front(new Missile(e, getPosition(), damage));
    attackCooldown = attackSpeed;
} 

int ExplosiveTower::getTexture()
{
    return 61;
}