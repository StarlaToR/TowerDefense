#include "explosiveTower.hpp"

ExplosiveTower::ExplosiveTower(Vec2D pos)
{
    damage = 15;
    range = 70;
    health = 150;
    maxHealth = 150;
    attackSpeed = 90;
    attackCooldown = 0;
    cost = 20;
    position = pos;
    rotation = 0;
}

void ExplosiveTower::attack(Enemy* e, std::forward_list<Missile*> missiles)
{
    missiles.push_front(new Missile(e, getPosition(), damage));
    attackCooldown = attackSpeed;
} 