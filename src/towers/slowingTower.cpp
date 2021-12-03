#include "slowingTower.hpp"

void SlowingTower::attack(Enemy* e)
{
    e->getDamage(damage);
    e->setSlowed(slowingTime);
}