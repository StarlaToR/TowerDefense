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
    bool isUsed;
    int cost;

public:
    TowerHolder(Vec2D pos,int type, int cost);
    TowerHolder();
    ~TowerHolder();

    Vec2D getPosition();
    int getTexture();
    void update(std::forward_list<Tower*>& towers, TileMap& map, int& money, Vec2D camPos, char camScale);
};

class TowerHolders
{

    public:
        TowerHolder holders[3];
        TowerHolders();
};