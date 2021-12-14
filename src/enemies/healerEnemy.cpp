#include "healerEnemy.hpp"
#include "../particles/heal.hpp"

HealerEnemy::HealerEnemy(TileMap& t, int wave)
{
    position = t.startPos + Vec2D(0.5f,0.5f);
    level = wave/4+1;
    slowTimer = 0;
    maxHealth = 20+20*level;
    health = maxHealth;
    reward = 3;
    speed = 2*level;
    damage = level;
    range = 2.0f+level;
    healing = 5+level*2;
    healingCooldown = 0;

    currentTile = Vec2D((int)t.startPos.x,(int)t.startPos.y);
    currentDirection = t.getTileAt(currentTile)-ROAD_START_NORTH;
    targetDirection = dirToAngle(currentDirection.dir);
    rotation = targetDirection;
    targetPos = currentDirection.getFowardTile(currentTile) + Vec2D(0.5f, 0.5f);
    angularVelocity= 0.05*speed;
    distanceToCenter = 0.1;
}

void HealerEnemy::heal(std::list<Enemy*>& enemies, Enemy* currentEnemy, std::forward_list<Particle*>& particles)
{
    bool healed = true;
    for (std::list<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); i++)
    {
        if((getPosition() - (*i)->getPosition()).getLength() <= range && (*i) != (currentEnemy))
        {
            (*i)->getHealed(healing);
            healed = false;
            particles.push_front(new HealParticle((*i)->getPosition()));
        }
    }
    if (healed)
    {
        getHealed(healing);
        particles.push_front(new HealParticle(position));
    }
    healingCooldown = 60-(level <= 5 ? 6*level : 30);

}

bool HealerEnemy::update(TileMap& t, std::list<Enemy*>& enemies, std::forward_list<Particle*>& particles, int& playerLife)
{
    damageCooldown--;
    slowTimer = cut(slowTimer-1, 0, __INT_MAX__);
    healingCooldown = cut(healingCooldown-1, 0, __INT_MAX__);
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

    if (healingCooldown <= 0) heal(enemies, this, particles);

    return (health <= 0 || position.x < 0 || position.y < 0 || position.x >= t.getWidth() || position.y >= t.getHeight());
}