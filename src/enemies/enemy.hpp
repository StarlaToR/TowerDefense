#pragma once
#include "../entities/entity.hpp"
#include "../tile/tileMap.hpp"
#include "../particles/particle.hpp"
#include <forward_list>
#include <list>

class Enemy : public Entity
{
protected:
    int speed;
    int reward;
    int slowTimer;
    bool underground = false;
    int damageCooldown = 0;
    Direction currentDirection;
    float targetDirection;
    Vec2D currentTile;
    Vec2D targetPos;
    float angularVelocity;
    float distanceToCenter;
    bool shouldStop = false;
public:
    void setSlowed(int value);
    virtual bool update(TileMap& t, std::list<Enemy*>& enemies, std::forward_list<Particle*>& particles, int &playerLife);
    void getDamage(int damageDealt);
    void getHealed(int heal);
    int getReward();
    virtual ~Enemy() = 0;
    unsigned int getColor() override;
    bool isUnderGround() {return underground;}
    
};