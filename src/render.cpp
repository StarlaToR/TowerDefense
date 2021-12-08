#define VEC2_TO_RAYLIB_VECTOR2                                       \
    Vec2D(const Vector2& f) { x = f.x; y = f.y; }                        \
    operator Vector2() const { return Vector2{x,y}; }

#include "render.hpp"
#include <raylib.h>
#include "util/renderUtil.hpp"

void renderMain(DataHolder* in) 
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (in->gameState == INTRO)
    {
        PlayMusicStream(in->introSong);
        renderStartAnim(in);
    }
    else if (in->gameState == MENU)
    {
        StopMusicStream(in->introSong);
        renderMainMenu(in);
        menuEditor(in);
    }
    else if (in->gameState == MENUPLAY)
    {
        renderPlay(in);
    }
    else if (in->gameState == EDITOR)
    {
        renderEditor(in);
    }
    else if (in->gameState == GAMEPLAY)
    {
        renderGameplay(in);
    }
    else if (in->gameState == OPTION)
    {
        renderOption(in);
    }
    else if (in->gameState == CREDIT)
    {
        renderCredit(in);
    }
    else if (in->gameState == EXIT)
    {
        in->closeWindow = true;
    }
    
    DrawFPS(10, 10);
    EndDrawing();
}

void renderStartAnim(DataHolder* in)
{
    float width = in->screenWidth;
    float heigth = in->screenHeight;
    size_t frames = in->framecounter;
    if (frames < 180)
    {
        DrawTexturePro(in->logo,Rectangle{0,0,300,300},Rectangle{width/2,heigth/2,frames*1.66666f,frames*1.6666f},Vector2{150,150},frames*2.0f,getRGB(frames));
    }
    else if (frames < 260)
    {
        DrawTexturePro(in->logo,Rectangle{0,0,300,300},Rectangle{width/2,heigth/2,300,300},Vector2{150,150},0,getRGB(frames));
    }
    else if (frames < 320)
    {
        DrawTexturePro(in->logo,Rectangle{0,0,300,300},Rectangle{width/2,heigth/2,300,300},Vector2{150,150},0,Fade(getRGB(frames),(320-frames)/60.0f));
    }
}

void renderMainMenu(DataHolder* in)
{
    float width = in->screenWidth;
    float heigth = in->screenHeight;
    DrawTexturePro(in->background, Rectangle{(float)(in->framecounter/3.0f),0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in->title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTexturePro(in->logo, Rectangle{0,0,300,300},Rectangle{width, heigth,100,100},Vector2{100,100}, 0, WHITE);
    DrawTextEx(in->fontTitle, "Tower Defense", Vector2{480,27},70,4,BLACK);
    
}

void renderEditor(DataHolder* in)
{
    drawMapElements(in, true);
    in->buttonSelected = 0;
    in->holderHovered = -1;
    if (drawButton("Save Map", Vec2D(1300,570),Vec2D(200,50), in->mousePos))
    {
        in->buttonSelected = 1;
    }
    if (drawButton("Clear Map", Vec2D(1300,670),Vec2D(200,50), in->mousePos))
    {
        in->buttonSelected = 2;
    }
    if (drawButton("Change view", Vec2D(1300,770),Vec2D(200,50), in->mousePos))
    {
        in->buttonSelected = 3;
    }
    for (unsigned int i = 0; i < in->tHolders.holders.size(); i++)
    {
        TileHolder* tmp = &in->tHolders.holders.at(i);
        Vec2D screenPos = tmp->position*Vec2D(64,64)+Vec2D(1300,100);
        DrawTexturePro(in->tileTexture,in->tiles.tileCrops.at(tmp->getTile()),toRayLibRectangle(screenPos,Vec2D(48,48)),Vec2D(),0,WHITE);
        if (in->mousePos.x > screenPos.x && in->mousePos.y > screenPos.y && in->mousePos.x < screenPos.x + 48 && in->mousePos.y < screenPos.y + 48)
        {
            in->holderHovered = i;
            DrawRectangleLinesEx(toRayLibRectangle(screenPos,Vec2D(48,48)),2,BLUE);
        }
        else if (in->holderSelected == (int)(i))
        {
            DrawRectangleLinesEx(toRayLibRectangle(screenPos,Vec2D(48,48)),2,RED);
        }
    }
    DrawText(TextFormat("Money : %d",in->money),10,30,20,BLACK);
}

void renderGameplay(DataHolder* in)
{
    drawMapElements(in, false);
    in->selectedTower = drawTowerUpgradeMenu(in->selectedTower, &in->towers);
    DrawText(TextFormat("Money : %d",in->money),10,30,20,BLACK);
}

void menuEditor(DataHolder* in)
{
    in->gameState = MENU;
    in->buttonSelected = 0;
    
    if (drawButtonMenu(in, "Play", Vec2D(498, 345), Vec2D(455, 320),Vec2D(250,100), in->mousePos))
    {
        in->buttonSelected = 1;
    }
    if (drawButtonMenu(in, "Option",Vec2D(873, 345), Vec2D(860, 320),Vec2D(250,100), in->mousePos))
    {
        in->buttonSelected = 2;
    }
    if (drawButtonMenu(in, "Credit",Vec2D(475, 570), Vec2D(455, 540),Vec2D(250,100), in->mousePos))
    {
        in->buttonSelected = 3;
    }
    if (drawButtonMenu(in, "Exit",Vec2D(925, 570), Vec2D(860, 540),Vec2D(250,100), in->mousePos))
    {
        in->buttonSelected = 4;
    }
    if (drawButtonInvisible(in, Vec2D(mod(1295-in->framecounter/3.0f,0,1920), 140),Vec2D(50,50), in->mousePos))
    {
        in->buttonSelected = 5;
    }
    if (drawButtonInvisible(in, Vec2D(1500, 800), Vec2D(100, 100), in->mousePos))
    {
        in->buttonSelected = 6;
    }
    if (IsKeyPressed(KEY_SPACE))
    {
        StopMusicStream(in->musicTroll);
    }

}

void renderPlay(DataHolder* in)
{
    in->buttonSelected = 0;
    float width = in->screenWidth;
    float heigth = in->screenHeight;
    DrawTexturePro(in->background, Rectangle{in->framecounter/3.0f,0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in->title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTextEx(in->fontTitle, "Play", Vector2{660,0},100,4,BLACK);
    if (drawButtonMenu(in, "Play", Vec2D(695,350), Vec2D(650, 300),Vec2D(250,140), in->mousePos))
    {
        in->buttonSelected = 1;
    }
    if (drawButtonMenu(in, "Editor", Vec2D(670, 550), Vec2D(650, 520),Vec2D(250,100), in->mousePos))
    {
        in->buttonSelected = 2;
    }
    if (drawButtonMenu(in, "Return", Vec2D(652, 780), Vec2D(650, 750),Vec2D(250,100), in->mousePos))
    {
        in->buttonSelected = 3;
    }
}

void renderCredit(DataHolder* in)
{
    in->buttonSelected = 0;
    float width = in->screenWidth;
    float heigth = in->screenHeight;
    DrawTexturePro(in->background, Rectangle{in->framecounter/3.0f,0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in->title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTextEx(in->fontTitle, "Credit", Vector2{600,0},100,4,BLACK);
    DrawTextEx(in->fontTitle, "Quentin Lepine", Vector2{450,300},70,4,WHITE);
    DrawTextEx(in->fontTitle, "Antoine Mordant", Vector2{420,450},70,4,WHITE);
    DrawTextEx(in->fontTitle, "Umut Osmanoglu", Vector2{430,600},70,4,WHITE);
    if (drawButtonMenu(in, "Return", Vec2D(652, 780), Vec2D(650, 750),Vec2D(250,100), in->mousePos))
    {
        in->buttonSelected = 1;
    }
}

void renderOption(DataHolder* in)
{
    in->buttonSelected = 0;
    float width = in->screenWidth;
    float heigth = in->screenHeight;
    DrawTexturePro(in->background, Rectangle{in->framecounter/3.0f,0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in->title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTextEx(in->fontTitle, "Option", Vector2{600,0},100,4,BLACK);
    if (drawButtonMenu(in, "Return", Vec2D(652, 780), Vec2D(650, 750),Vec2D(250,100), in->mousePos))
    {
        in->buttonSelected = 1;
    }
}

void renderLoad(DataHolder* in)
{
    in->buttonSelected = 0;
    float width = in->screenWidth;
    float heigth = in->screenHeight;
    DrawTexturePro(in->background, Rectangle{in->framecounter/3.0f,0,2,2},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in->title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTextEx(in->fontTitle, "Load", Vector2{660,0},100,4,BLACK);
    if (drawButtonMenu(in, "Return", Vec2D(652, 780), Vec2D(650, 750),Vec2D(250,100), in->mousePos))
    {
        in->buttonSelected = 1;
    }
}