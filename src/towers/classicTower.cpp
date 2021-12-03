#include "classicTower.hpp"

int ClassicTower::getTexture()
{

}

void ClassicTower::attack(Enemy* e)
{
    e->getDamage(damage);
}