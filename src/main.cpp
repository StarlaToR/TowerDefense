#include <raylib.h>
#include "util/mathHelper.hpp"
#include "util/dataHolder.hpp"
#include "render.hpp"
#include <cstdio>
#include <time.h>

int main(void)
{
    DataHolder holder = DataHolder();
    SetRandomSeed(time(NULL));
    #ifdef _WIN32
    SetConfigFlags(FLAG_VSYNC_HINT); // Just a basic way of detecting windows
    #endif
    InitWindow(holder.screenWidth, holder.screenHeight, "Tower Defense");
    InitAudioDevice();
    SetTargetFPS(60);
    holder.initDatas();

    // Main game loop
    while (!WindowShouldClose() && !holder.closeWindow == true)
    {
        holder.handleGameState();
        renderMain(holder);
    }
    holder.unloadDatas();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
