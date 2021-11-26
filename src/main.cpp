#include <raylib.h>
#include "util/mathHelper.hpp"
#include "util/dataHolder.hpp"
#include "render.hpp"

int main(void)
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    DataHolder holder = DataHolder();
    InitWindow(holder.screenWidth, holder.screenHeight, "Tower Defense");
    InitAudioDevice();
    SetExitKey(KEY_NULL);
    holder.logo = LoadTexture("assets/logo_group.png");
    holder.map = TileMap();

    // Main game loop
    while (!WindowShouldClose())
    {
        holder.handleGameState();
        renderMain(&holder);
    }
    holder.unloadDatas();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
