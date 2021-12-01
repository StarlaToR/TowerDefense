#include <raylib.h>
#include "util/mathHelper.hpp"
#include "util/dataHolder.hpp"
#include "render.hpp"
#include <cstdio>
#include "enemies/classicEnemy.hpp"

int main(void)
{
    
    DataHolder holder = DataHolder();
    InitWindow(holder.screenWidth, holder.screenHeight, "Tower Defense");
    InitAudioDevice();
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
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
    for (int i = 0; i < 100; i++) holder.t.push_back(new ClassicEnemy(holder.map));

    // Main game loop
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_TAB)) SetTargetFPS(600);
        if (IsKeyReleased(KEY_TAB)) SetTargetFPS(60);
        holder.handleGameState();
        if (holder.gameState == 2)
        for (int i = 0; i < 100; i++) holder.t[i]->update(holder.map);
        renderMain(&holder);
    }
    holder.unloadDatas();
    for (unsigned int i = 0; i < holder.t.size(); i++) delete holder.t[i];
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
