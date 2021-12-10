#include "entity.hpp"

float Entity::getHealth()
{
    return (float)(health)/maxHealth;
}

unsigned int Entity::getColor()
{
    if (level <= 1) return 0x00f030ff;
    if (level == 2) return 0x0080f0ff;
    if (level == 3) return 0xff9000ff;
    if (level == 4) return 0xf03030ff;
    if (level == 5) return 0x909090ff;
    if (level == 6) return 0xffa0a0ff;
    return 0;
}