#define VEC2_TO_RAYLIB_VECTOR2                                       \
    Vec2D(const Vector2& f) { x = f.x; y = f.y; }                        \
    operator Vector2() const { return Vector2{x,y}; }

#include "render.hpp"
#include <raylib.h>
#include "util/renderUtil.hpp"

void renderMain(DataHolder& in) 
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    switch (in.gameState)
    {
    case INTRO:
        PlayMusicStream(in.sounds.introSong);
        renderStartAnim(in);
        break;
    case MENU:
        renderMainMenu(in);
        menuEditor(in);
        break;
    case MENUPLAY:
        renderPlay(in);
        break;
    case EDITOR:
        renderEditor(in);
        break;
    case GAMEPLAY:
        renderGameplay(in);
        break;
    case GAMEOVER:
        renderGameOver(in);
        break;
    case VICTORY:
        renderGameOver(in);
        break;
    case OPTION:
        renderOption(in);
        break;
    case CREDIT:
        renderCredit(in);
        break;
    case EXIT:
        in.closeWindow = true;
        break;
    default:
        break;
    }
    DrawText(TextFormat("Speed: x%d",in.gameSpeed),100,10,20,BLACK);
    DrawFPS(10, 10);
    EndDrawing();
}

void renderStartAnim(DataHolder& in)
{
    float width = in.screenWidth;
    float heigth = in.screenHeight;
    size_t frames = in.framecounter;
    if (frames < 180)
    {
        DrawTexturePro(in.textures.logo,Rectangle{0,0,300,300},Rectangle{width/2,heigth/2,frames*1.66666f,frames*1.6666f},Vector2{150,150},frames*2.0f,getRGB(frames));
    }
    else if (frames < 260)
    {
        DrawTexturePro(in.textures.logo,Rectangle{0,0,300,300},Rectangle{width/2,heigth/2,300,300},Vector2{150,150},0,getRGB(frames));
    }
    else if (frames < 320)
    {
        DrawTexturePro(in.textures.logo,Rectangle{0,0,300,300},Rectangle{width/2,heigth/2,300,300},Vector2{150,150},0,Fade(getRGB(frames),(320-frames)/60.0f));
    }
}

void renderMainMenu(DataHolder& in)
{
    float width = in.screenWidth;
    float heigth = in.screenHeight;
    DrawTexturePro(in.textures.background, Rectangle{(float)(in.framecounter/3.0f),0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTexturePro(in.textures.logo, Rectangle{0,0,300,300},Rectangle{width, heigth,100,100},Vector2{100,100}, 0, WHITE);
    DrawTextEx(in.fontTitle, "Tower Defense", Vector2{480,27},70,4,BLACK);
    
}

void renderGameOver(DataHolder& in)
{
    float width = in.screenWidth;
    float heigth = in.screenHeight;
    DrawTexturePro(in.textures.background, Rectangle{(float)(in.framecounter/3.0f),0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTexturePro(in.textures.board, Rectangle{0,0,720,900},Rectangle{680, 350,500,500},Vector2{150,150}, 0, WHITE);
    DrawTextEx(in.fontTitle, "Game Over", Vector2{560,27},70,4,BLACK);
    DrawText(TextFormat("Wave : %d",in.wave),1080,680,30,BLACK);
    if (drawButtonMenu(in, "Return", Vec2D(652, 780), Vec2D(650, 750),Vec2D(250,100), in.mousePos))
    {
        in.buttonSelected = 1;
    }

}

void renderVictory(DataHolder& in)
{
    DrawTextEx(in.fontTitle, "Victory", Vector2{480,27},70,4,BLACK);
}

void renderEditor(DataHolder& in)
{
    drawMapElements(in, true);
    in.buttonSelected = 0;
    in.holderHovered = -1;
    if (drawButton("Save Map", Vec2D(1300,570),Vec2D(200,50), in.mousePos))
    {
        in.buttonSelected = 1;
    }
    if (drawButton("Clear Map", Vec2D(1300,670),Vec2D(200,50), in.mousePos))
    {
        in.buttonSelected = 2;
    }
    if (drawButton("Change view", Vec2D(1300,770),Vec2D(200,50), in.mousePos))
    {
        in.buttonSelected = 3;
    }
    if (drawButtonMenu(in, "Return", Vec2D(652, 780), Vec2D(650, 750),Vec2D(250,100), in.mousePos))
    {
        in.buttonSelected = 4;
    }
    for (unsigned int i = 0; i < in.lists.tHolders.holders.size(); i++)
    {
        TileHolder* tmp = &in.lists.tHolders.holders.at(i);
        Vec2D screenPos = tmp->position*Vec2D(64,64)+Vec2D(1300,100);
        DrawTexturePro(in.textures.tileTexture,in.lists.tiles.tileCrops.at(tmp->getTile()),toRayLibRectangle(screenPos,Vec2D(48,48)),Vec2D(),0,WHITE);
        if (in.mousePos.x > screenPos.x && in.mousePos.y > screenPos.y && in.mousePos.x < screenPos.x + 48 && in.mousePos.y < screenPos.y + 48)
        {
            in.holderHovered = i;
            DrawRectangleLinesEx(toRayLibRectangle(screenPos,Vec2D(48,48)),2,BLUE);
        }
        else if (in.holderSelected == (int)(i))
        {
            DrawRectangleLinesEx(toRayLibRectangle(screenPos,Vec2D(48,48)),2,RED);
        }
    }
}

void renderGameplay(DataHolder& in)
{
    Vec2D mTilePos = (in.mousePos) / (48*in.cameraScale) - (Vec2D(50, 50)-in.cameraPos)/48.0f;
    mTilePos = Vec2D((int)(mTilePos.x),(int)(mTilePos.y));
    drawMapElements(in, false);
    in.buttonSelected = 0;
    drawTowerUpgradeMenu(in, in.buttonSelected);
    DrawText(TextFormat("Money : %d",in.money),50,680,30,BLACK);
    DrawText(TextFormat("Wave : %d",in.wave),1080,680,30,BLACK);
    DrawRectangleRec(toRayLibRectangle(Vec2D(50,750),Vec2D(1156,74)),BLACK);
    DrawRectangleRec(toRayLibRectangle(Vec2D(52,752),Vec2D(1152,70)),RED);
    DrawRectangleRec(toRayLibRectangle(Vec2D(52,752),Vec2D(11.52*in.life,70)),GREEN);
    for (int i = 0; i < 3; i++)
    {
        TowerHolder* tmpHolder = &in.lists.towerHolders.holders[i];
        if (tmpHolder->isUsed)
        {
            bool valid = (in.mousePos.x > 50 && in.mousePos.y > 50 && in.mousePos.x < 1202 && in.mousePos.y < 626 && !in.lists.map.isRoad(in.lists.map.getTileAt(mTilePos))
             && in.lists.map.getTileAt(mTilePos,true) == UNDEFINED && !in.lists.map.isTileWithTower(mTilePos));
            DrawTexturePro(in.textures.tileTexture,in.lists.tiles.tileCrops.at(tmpHolder->getTexture()),toRayLibRectangle(in.mousePos,Vec2D(80,80)),Vec2D(40,40),0,Fade(valid ? GREEN : RED,0.6f));
        }
    }

}

void menuEditor(DataHolder& in)
{
    in.gameState = MENU;
    in.buttonSelected = 0;
    
    if (drawButtonMenu(in, "Play", Vec2D(498, 345), Vec2D(455, 320),Vec2D(250,100), in.mousePos))
    {
        in.buttonSelected = 1;
    }
    if (drawButtonMenu(in, "Option",Vec2D(873, 345), Vec2D(860, 320),Vec2D(250,100), in.mousePos))
    {
        in.buttonSelected = 2;
    }
    if (drawButtonMenu(in, "Credit",Vec2D(475, 570), Vec2D(455, 540),Vec2D(250,100), in.mousePos))
    {
        in.buttonSelected = 3;
    }
    if (drawButtonMenu(in, "Exit",Vec2D(925, 570), Vec2D(860, 540),Vec2D(250,100), in.mousePos))
    {
        in.buttonSelected = 4;
    }
    if (drawButtonInvisible(Vec2D(mod(1295-in.framecounter/3.0f,0,1920), 140),Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 5;
    }
    if (drawButtonInvisible(Vec2D(1500, 800), Vec2D(100, 100), in.mousePos))
    {
        in.buttonSelected = 6;
    }
    if (IsKeyPressed(KEY_SPACE))
    {
        StopMusicStream(in.sounds.musicTroll);
    }

}

void renderPlay(DataHolder& in)
{
    in.buttonSelected = 0;
    float width = in.screenWidth;
    float heigth = in.screenHeight;
    DrawTexturePro(in.textures.background, Rectangle{in.framecounter/3.0f,0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTextEx(in.fontTitle, "Play", Vector2{660,0},100,4,BLACK);
    
    if (drawButtonMenu(in, "New", Vec2D(710,265), Vec2D(650, 220),Vec2D(250,140), in.mousePos))
    {
        in.buttonSelected = 1;
    }
    if (drawButtonMenu(in, "Load", Vec2D(695,445), Vec2D(650, 400),Vec2D(250,140), in.mousePos))
    {
        in.buttonSelected = 2;
    }
    if (drawButtonMenu(in, "Editor", Vec2D(670, 605), Vec2D(650, 580),Vec2D(250,100), in.mousePos))
    {
        in.buttonSelected = 3;
    }
    if (drawButtonMenu(in, "Return", Vec2D(652, 780), Vec2D(650, 760),Vec2D(250,100), in.mousePos))
    {
        in.buttonSelected = 4;
    }
}

void renderCredit(DataHolder& in)
{
    in.buttonSelected = 0;
    float width = in.screenWidth;
    float heigth = in.screenHeight;
    DrawTexturePro(in.textures.background, Rectangle{in.framecounter/3.0f,0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTexturePro(in.textures.logoIsart, Rectangle{0,0,256,256},Rectangle{100, 350, 200,200},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.logo, Rectangle{0,0,300,300},Rectangle{1300, 350,200,200},Vector2{0,0}, 0, WHITE);
    DrawTextEx(in.fontTitle, "Credit", Vector2{600,0},100,4,BLACK);
    DrawTextEx(in.fontTitle, "Quentin Lepine", Vector2{450,300},70,4,WHITE);
    DrawTextEx(in.fontTitle, "Antoine Mordant", Vector2{420,450},70,4,WHITE);
    DrawTextEx(in.fontTitle, "Umut Osmanoglu", Vector2{430,600},70,4,WHITE);
    if (drawButtonMenu(in, "Return", Vec2D(652, 780), Vec2D(650, 750),Vec2D(250,100), in.mousePos))
    {
        in.buttonSelected = 1;
    }
}

void renderOption(DataHolder& in)
{
    in.buttonSelected = 0;
    float width = in.screenWidth;
    float heigth = in.screenHeight;
    DrawTexturePro(in.textures.background, Rectangle{in.framecounter/3.0f,0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTextEx(in.fontTitle, "Option", Vector2{600,0},100,4,BLACK);
    if (drawButtonMenu(in, "Return", Vec2D(652, 780), Vec2D(650, 750),Vec2D(250,100), in.mousePos))
    {
        in.buttonSelected = 1;
    }
    DrawRectangleRounded(toRayLibRectangle(Vec2D(400,550),Vec2D(450,50)),0.2,10,LIGHTGRAY);
    DrawRectangleRoundedLines(toRayLibRectangle(Vec2D(400,550),Vec2D(450,50)),0.2,10,2,BLACK);
    DrawText(TextFormat("Master Volume: %.2f",in.masterVolume),410,557,40,GRAY);
    if (drawButton("+", Vec2D(950, 550), Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 2;
    }
    if (drawButton("-", Vec2D(1050, 550), Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 3;
    }
}

void renderLoad(DataHolder& in)
{
    in.buttonSelected = 0;
    float width = in.screenWidth;
    float heigth = in.screenHeight;
    DrawTexturePro(in.textures.background, Rectangle{in.framecounter/3.0f,0,2,2},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTextEx(in.fontTitle, "Load", Vector2{660,0},100,4,BLACK);
    if (drawButtonMenu(in, "Return", Vec2D(652, 780), Vec2D(650, 750),Vec2D(250,100), in.mousePos))
    {
        in.buttonSelected = 1;
    }
}