#include "tower.hpp"

class SlowingTower : public Tower
{
private:
    int slowingTime = 120;
public:
    SlowingTower(Vec2D pos);

    SlowingTower():SlowingTower(Vec2D(0,0)){}

    void attack(Enemy* e);
    int getTexture();
};