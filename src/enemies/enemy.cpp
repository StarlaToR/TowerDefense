#include "enemy.hpp"

void Enemy::setSlowed(int value)
{
    slowTimer = value;
}

bool Enemy::update(TileMap& t, std::list<Enemy*>& enemies, std::forward_list<Particle*>& particles, int &playerLife)
{
    damageCooldown--;
    slowTimer = cut(slowTimer-1, 0, __INT_MAX__);
    Vec2D currentTilePosition((int)getPosition().x, (int)getPosition().y);
    if ((currentTilePosition.x != currentTile.x || currentTilePosition.y != currentTile.y) && (position - targetPos).lengthSquared() < distanceToCenter)
    {
        currentTile = currentTilePosition;
        unsigned char newTile = t.getTileAt(currentTilePosition);
        unsigned char newTile2 = t.getTileAt(currentTilePosition,true);
        if (newTile >= ROAD_END_NORTH && newTile <= ROAD_END_WEST)
        {
            playerLife -= damage;
            reward = 0;
            health = 0;
        }
        else if (newTile2 >= TUNNEL_NORTH && newTile2 <= TUNNEL_WEST)
        {
            if (!underground)
            {
                underground = true;
                targetPos = currentDirection.getFowardTile(currentTilePosition) + Vec2D(0.5f, 0.5f);
            }
            else
            {
                underground = false;
                currentDirection = getNextDirection(newTile, currentDirection);
                targetPos = currentDirection.getFowardTile(currentTilePosition) + Vec2D(0.5f, 0.5f);
            }
        }
        else if (underground)
        {
            targetPos = currentDirection.getFowardTile(currentTilePosition) + Vec2D(0.5f, 0.5f);
        }
        else
        {
            currentDirection = getNextDirection(newTile, currentDirection);
            targetPos = currentDirection.getFowardTile(currentTilePosition) + Vec2D(0.5f, 0.5f);
        }
    }
    Vec2D dif = targetPos - position;
    float tmpDir;
    if (dif.x == 0)
    {
        if (dif.y > 0)
            tmpDir = PI / 2.0f;
        else
            tmpDir = -PI / 2.0f;
    }
    else
    {
        tmpDir = (atanf(dif.y / dif.x));
        if (dif.x < 0)
        {
            tmpDir += PI;
        }
    }
    float ang = mod(rotation - tmpDir, -PI, PI);
    float vAng = slowTimer > 0 ? angularVelocity/4 : angularVelocity;
    float dec = cut(ang, -vAng, vAng);
    rotation = mod(rotation - dec, -PI, PI);
    if (ang > 1.6f/3.0f*PI || ang < -1.6f/3.0f*PI)
    {
        shouldStop = true;
    }
    if (!shouldStop)
    {
        this->position.x += this->speed / (slowTimer > 0 ? 240.0f : 60.0f) * cosf(rotation);
        this->position.y += this->speed / (slowTimer > 0 ? 240.0f : 60.0f) * sinf(rotation);
    }
    else
    {
        shouldStop = !(ang < vAng && ang > -vAng);
    }
    return (health <= 0 || position.x < 0 || position.y < 0 || position.x >= t.getWidth() || position.y >= t.getHeight());
}

void Enemy::getHealed(int heal)
{
    health += heal;
    if (health > maxHealth)
    {
        damageCooldown = 0;
        health = maxHealth;
    }
}

int Enemy::getReward()
{
    return reward;
}

Enemy::~Enemy()
{
}

void Enemy::getDamage(int damageDealt)
{
    health -= damageDealt;
    if (health < 0) health = 0;
    damageCooldown = 6;
}

unsigned int Enemy::getColor()
{
    if (damageCooldown > 0) return 0xff8080ff;
    if (level <= 1) return 0x00f030ff;
    if (level == 2) return 0x0080f0ff;
    if (level == 3) return 0xff9000ff;
    if (level == 4) return 0xf03030ff;
    if (level == 5) return 0x909090ff;
    if (level == 6) return 0xffa0a0ff;
    return 0;
}