#include "render.hpp"
#include <raylib.h>
#include "util/renderUtil.hpp"

void renderMain(DataHolder* in)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (in->gameState == 0)
    {
        renderStartAnim(in);
    }
    else if (in->gameState == 1)
    {
        renderMainMenu(in);
    }
    else if (in->gameState == 2)
    {
        renderEditor(in);
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
    float buttonDiviser[4] = {3, 2, 1.5 ,1.2};
    DrawTexturePro(in->background,Rectangle{0,0,600,600},Rectangle{0,0,width,heigth},Vector2{0,0},0,WHITE);
    DrawTexturePro(in->title,Rectangle{0,0,450,400},Rectangle{width/4,0,1000,400},Vector2{150,150},0,WHITE);
    DrawTexturePro(in->logoIsart,Rectangle{0,0,250,250},Rectangle{0,800,100,100},Vector2{0,0},0,WHITE);
    for (int i = 0; i < 4; i++)
    {
        DrawTexturePro(in->button,Rectangle{0,0,500,500},Rectangle{width/2,heigth/buttonDiviser[i], 300, 300},Vector2{150,150},0,WHITE);
    }

    DrawText("Play", width/2.16,heigth/3.4,50,Fade(BLACK,getFade(in->framecounter)));
    DrawText("Load", width/2.16,heigth/2.15,50,Fade(BLACK,getFade(in->framecounter)));
    DrawText("Option", width/2.22,heigth/1.6,50,Fade(BLACK,getFade(in->framecounter)));
    DrawText("Credit", width/2.22,heigth/1.26,50,Fade(BLACK,getFade(in->framecounter)));
    DrawText("Tower Defense", width/3.3,heigth/20,80,Fade(BLACK,getFade(in->framecounter)));
}

void renderEditor(DataHolder* in)
{
    DrawTileMap(in,DEBUG);
}