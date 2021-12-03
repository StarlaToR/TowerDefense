#include <raylib.h>
#include "util/mathHelper.hpp"
#include "util/dataHolder.hpp"
#include "render.hpp"
#include <cstdio>
#include "enemies/classicEnemy.hpp"
#include "enemies/bigEnemy.hpp"
#include "enemies/healerEnemy.hpp"

int main(void)
{
    
    DataHolder holder = DataHolder();
    InitWindow(holder.screenWidth, holder.screenHeight, "Tower Defense");
    InitAudioDevice();
    SetTargetFPS(60);
    holder.logo = LoadTexture("assets/textures/logo_group.png");
    holder.tileTexture = LoadTexture("assets/textures/towerDefense_tilesheet.png");
    holder.background = LoadTexture("assets/textures/Marie-Antoine.png");
    holder.title = LoadTexture("assets/textures/title.png");
    holder.credit = LoadTexture("assets/textures/credit.png");
    holder.button = LoadTexture("assets/textures/button.png");
    holder.logo = LoadTexture("assets/textures/logo_group.png");
    holder.tileTexture = LoadTexture("assets/textures/towerDefense_tilesheet.png");
    holder.fontButton = LoadFontEx("assets/font/ethnocentric.ttf", 100, 0, 0);
    holder.fontTitle = LoadFontEx("assets/font/GODOFWAR.TTF", 100, 0, 0);
    holder.map = TileMap();
    FILE* sv = fopen("assets/maps/default.bin","rb");
    fread(&holder.map,1,sizeof(holder.map),sv);
    fclose(sv);
    holder.tiles.registerTiles();
    for (int i = 0; i < 20; i++)
    {
        holder.t.push_back(new ClassicEnemy(&holder.map));
        holder.t.push_back(new BigEnemy(&holder.map));
        holder.t.push_back(new HealerEnemy(&holder.map));
    }

    // Main game loop
    while (!WindowShouldClose() && !holder.closeWindow == true)
    {
        if (IsKeyPressed(KEY_TAB)) SetTargetFPS(600);
        if (IsKeyReleased(KEY_TAB)) SetTargetFPS(60);
        holder.handleGameState();
        if (holder.gameState == 2)
        for (unsigned int i = 0; i < holder.t.size(); i++) holder.t[i]->update(&holder.map);
        renderMain(&holder);
    }
    holder.unloadDatas();
    for (unsigned int i = 0; i < holder.t.size(); i++) delete holder.t[i];
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
