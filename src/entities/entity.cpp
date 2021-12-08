#include "entity.hpp"

float Entity::getHealth()
{
    return (float)(health)/maxHealth;
}