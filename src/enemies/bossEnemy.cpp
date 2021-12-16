#include "bossEnemy.hpp"
#include "../particles/bigExplosion.hpp"
#include "../particles/enemyExplosion.hpp"
#include "../particles/explosion.hpp"

BossEnemy::BossEnemy(TileMap& t, int wave, int difficulty)
{
    position = t.startPos + Vec2D(0.5f,0.5f);
    level = 1;
    slowTimer = 0;
    maxHealth = 10000 * difficulty;
    health = maxHealth;
    reward = 0;
    speed = 1;
    damage = 1000;

    currentTile = Vec2D((int)t.startPos.x,(int)t.startPos.y);
    currentDirection = t.getTileAt(currentTile)-ROAD_START_NORTH;
    targetDirection = dirToAngle(currentDirection.dir);
    rotation = targetDirection;
    targetPos = t.endPos + Vec2D(0.5f, 0.5f);
    angularVelocity= 0.05*speed;
    distanceToCenter = 0.1;
}

BossEnemy::~BossEnemy()
{
}

bool BossEnemy::update(TileMap& t, std::list<Enemy*>& enemies, std::forward_list<Particle*>& particles, int &playerLife)
{
    if (health <= 0) {
        underground = true;
        anim--;
        int rng = GetRandomValue(1,10);
        if (rng <= 2)
            particles.push_front(new BigExplosionParticle(position+Vec2D(GetRandomValue(-100,100),GetRandomValue(-100,100))/100));
        else if (rng <= 4)
            particles.push_front(new EnemyExplosionParticle(position+Vec2D(GetRandomValue(-150,150),GetRandomValue(-150,150))/100));
        else
            particles.push_front(new ExplosionParticle(position+Vec2D(GetRandomValue(-200,200),GetRandomValue(-200,200))/100));
    }
    else
    {
        slowTimer = cut(slowTimer-1, 0, __INT_MAX__);
        if ((position - targetPos).lengthSquared() < distanceToCenter)
        {
            playerLife = 0;
            health = 0;
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
        this->position.x += this->speed / (slowTimer > 0 ? 480.0f : 120.0f) * cosf(rotation);
        this->position.y += this->speed / (slowTimer > 0 ? 480.0f : 120.0f) * sinf(rotation);
    }
    return (health <= 0 && anim <= 0);
}