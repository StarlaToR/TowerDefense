#include "tower.hpp"
#include "classicTower.hpp"
#include "slowingTower.hpp"
#include "explosiveTower.hpp"
#include <forward_list>

class TowerHolder
{
private:
    int towerType;
    Vec2D position;
    int cost;
    float range = 0;
    Sound* towerSound;

public:
    bool isUsed;
    TowerHolder(Vec2D pos,int type, int cos, Sound* sound, float range);
    TowerHolder();
    ~TowerHolder();

    Vec2D getPosition();
    int getTexture();
    int getCost();
    float getRange() {return range;}
    void update(std::forward_list<Tower*>& towers, TileMap& map, int& money, Vec2D camPos, char camScale);
};

class TowerHolders
{
    private:
        Sound* slowTowerSound = nullptr;
        Sound* classicTowerSound = nullptr;
        Sound* explosiveTowerSound = nullptr;

    public:
        TowerHolder holders[3];
        TowerHolders() {}
        void initTowers(Sound* classic, Sound* slow, Sound* explosive);
};