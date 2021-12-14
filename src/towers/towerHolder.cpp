#include "towerHolder.hpp"

TowerHolder::TowerHolder(Vec2D pos, int type, int cos, Sound* sound)
{
    position = pos;
    towerType = type;
    isUsed = false;
    cost = cos;
    towerSound = sound;
}

TowerHolder::TowerHolder(){};

TowerHolder::~TowerHolder()
{

}

void TowerHolder::update(std::forward_list<Tower*>& towers, TileMap& map, int& money, Vec2D camPos, char camScale)
{
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (GetMouseX() >= position.x && GetMouseX() <= position.x + 128 && GetMouseY() >= position.y && GetMouseY() <= position.y + 128)
        {
            if(money >= cost)
                isUsed = true;
        }
    }
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && isUsed)
    {
        Vec2D tilePos = (Vec2D(GetMouseX(),GetMouseY())) / (48*camScale) - (Vec2D(50, 50)-camPos)/48.0f;
        tilePos = Vec2D((int)(tilePos.x),(int)(tilePos.y));
        if (GetMouseX() > 50 && GetMouseY() > 50 && GetMouseX() < 1202 && GetMouseY() < 626 && tilePos.x >= 0 && tilePos.y >= 0 && tilePos.x < map.getWidth() && tilePos.y < map.getHeight())
        {
            if (!map.isRoad(map.getTileAt(tilePos)) && map.getTileAt(tilePos,true) == UNDEFINED && !map.isTileWithTower(tilePos))
            {
                map.setTileWithTower(tilePos);

                if(towerType == 0)
                    towers.push_front(new ClassicTower(tilePos, towerSound));
                if(towerType == 1)
                    towers.push_front(new SlowingTower(tilePos, towerSound));
                if(towerType == 2)
                    towers.push_front(new ExplosiveTower(tilePos, towerSound));
                map.setTileWithTower(tilePos);
                money -= cost;
            }
        }
        isUsed = false;
    }
}

int TowerHolder::getTexture()
{
    if (towerType == 0)
    {
        return 121;
    }
    if (towerType == 1)
    {
        return 61;
    }
    if (towerType == 2)
    {
        return 99;
    }
    return 121;
}

Vec2D TowerHolder::getPosition()
{
    return position;
}

int TowerHolder::getCost()
{
    return cost;
}

void TowerHolders::initTowers(Sound* classic, Sound* slow, Sound* explosive)
{
    classicTowerSound = classic;
    slowTowerSound = slow;
    explosiveTowerSound = explosive;
    holders[0] = TowerHolder(Vec2D(1300, 100), 0, 5, classicTowerSound);
    holders[1] = TowerHolder(Vec2D(1300, 250), 1, 20, slowTowerSound);
    holders[2] = TowerHolder(Vec2D(1300, 400), 2, 50, explosiveTowerSound);
}