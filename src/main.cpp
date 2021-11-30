#include <raylib.h>
#include "util/mathHelper.hpp"
#include "util/dataHolder.hpp"
#include "render.hpp"
#include <cstdio>

int main(void)
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    DataHolder holder = DataHolder();
    InitWindow(holder.screenWidth, holder.screenHeight, "Tower Defense");
    InitAudioDevice();
    SetExitKey(KEY_NULL);
    holder.logo = LoadTexture("assets/logo_group.png");
    holder.tileTexture = LoadTexture("assets/towerDefense_tilesheet.png");
    holder.logoIsart= LoadTexture("assets/logo.png");
    holder.background = LoadTexture("assets/Marie-Antoine.png");
    holder.title = LoadTexture("assets/title.png");
    holder.button = LoadTexture("assets/button.png");
    holder.logo = LoadTexture("assets/textures/logo_group.png");
    holder.tileTexture = LoadTexture("assets/textures/towerDefense_tilesheet.png");
    holder.map = TileMap();
    FILE* sv = fopen("assets/maps/default.bin","rb");
    fread(&holder.map,1,sizeof(holder.map),sv);
    fclose(sv);
    holder.tiles.registerTiles();

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
