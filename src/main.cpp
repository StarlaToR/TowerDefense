#include <raylib.h>
#include "util/mathHelper.hpp"
#include "util/dataHolder.hpp"
#include "render.hpp"
#include <cstdio>
#include <time.h>
#include "enemies/classicEnemy.hpp"
#include "enemies/bigEnemy.hpp"
#include "enemies/healerEnemy.hpp"
#include "towers/classicTower.hpp"
#include "towers/slowingTower.hpp"
#include "towers/explosiveTower.hpp"

int main(void)
{
    DataHolder holder = DataHolder();
    SetRandomSeed(time(NULL));
    InitWindow(holder.screenWidth, holder.screenHeight, "Tower Defense");
    InitAudioDevice();
    SetTargetFPS(60);
    holder.initDatas();

    // Main game loop
    while (!WindowShouldClose() && !holder.closeWindow == true)
    {
        holder.handleGameState();
        renderMain(&holder);
    }
    holder.unloadDatas();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
