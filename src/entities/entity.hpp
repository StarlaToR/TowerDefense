#pragma once
#include "../object/object.hpp"
#include "../tile/tileMap.hpp"

class Entity : public Object
{
protected:
    int health;
    int maxHealth;
    int damage;
    int attackSpeed;
public:
    
    virtual void getDamage(int damageDealt) = 0;
    virtual void update(TileMap& t) = 0;
    virtual int getTexture() = 0;
};