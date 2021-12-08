#include <raylib.h>
#include "util/mathHelper.hpp"
#include "util/dataHolder.hpp"
#include "render.hpp"
#include <cstdio>
#include "enemies/classicEnemy.hpp"
#include "enemies/bigEnemy.hpp"
#include "enemies/healerEnemy.hpp"
#include "towers/classicTower.hpp"
#include "towers/slowingTower.hpp"
#include "towers/explosiveTower.hpp"

int main(void)
{
    DataHolder holder = DataHolder();
    InitWindow(holder.screenWidth, holder.screenHeight, "Tower Defense");
    InitAudioDevice();
    SetTargetFPS(60);
    holder.logo = LoadTexture("assets/textures/logo_group.png");
    holder.background = LoadTexture("assets/textures/background.png");
    holder.title = LoadTexture("assets/textures/title.png");
    holder.credit = LoadTexture("assets/textures/credit.png");
    holder.tileTexture = LoadTexture("assets/textures/tileSheet.png");
    holder.button = LoadTexture("assets/textures/button.png");
    holder.buttonSound = LoadSound("assets/song/button.wav");
    holder.musicTroll = LoadMusicStream("assets/song/ouioui.mp3");
    holder.gameplayMusic = LoadMusicStream("assets/song/gameplayMusic.mp3");
    holder.introSong = LoadMusicStream("assets/song/introSong.mp3");
    holder.fontButton = LoadFontEx("assets/font/ethnocentric.ttf", 100, 0, 0);
    holder.fontTitle = LoadFontEx("assets/font/godofwar.ttf", 100, 0, 0);
    holder.map = TileMap();
    holder.selectedTower = nullptr;
    FILE* sv = fopen("assets/maps/default.bin","rb");
    fread(&holder.map,1,sizeof(holder.map),sv);
    fclose(sv);
    holder.tiles.registerTiles();

    
    holder.towers.push_front(new ExplosiveTower(holder.map.startPos+Vec2D(7,1)));

    // Main game loop
    while (!WindowShouldClose() && !holder.closeWindow == true)
    {
        UpdateMusicStream(holder.musicTroll);
        UpdateMusicStream(holder.gameplayMusic);
        UpdateMusicStream(holder.introSong);
        SetMusicVolume(holder.musicTroll, 0.2f);
        if (IsKeyPressed(KEY_TAB)) SetTargetFPS(600);
        if (IsKeyReleased(KEY_TAB)) SetTargetFPS(60);
        if(holder.timePlayed >= 16.5f) StopMusicStream(holder.musicTroll);
        holder.timePlayed = GetMusicTimePlayed(holder.musicTroll);
        holder.handleGameState();
        
        renderMain(&holder);
    }
    holder.unloadDatas();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
