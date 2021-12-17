#include <raylib.h>
#include <cstdio>
#include <time.h>
#include "util/mathHelper.hpp"
#include "util/dataHolder.hpp"
#include "render.hpp"

int main(void)
{
    DataHolder holder = DataHolder();
    SetRandomSeed(time(NULL));
    #ifdef WIN
    SetConfigFlags(FLAG_VSYNC_HINT);
    #endif
    InitWindow(holder.screenWidth, holder.screenHeight, "Tower Defense");
    InitAudioDevice();
    #ifndef WIN
    SetTargetFPS(60);
    #endif
    holder.initDatas();
    PlayMusicStream(holder.sounds.introSong);

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
