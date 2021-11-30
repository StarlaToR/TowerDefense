/*#define VEC2_TO_RAYLIB_VECTOR2                                       \
    Vec2D(const Vector2& f) { x = f.x; y = f.y; }                        \
    operator Vector2() const { return Vector2{x,y}; }

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
    DrawText("Menu", 100,100,30,Fade(BLACK,getFade(in->framecounter)));

}

void renderEditor(DataHolder* in)
{
    for (int i = 0; i < in->map.getWidth()*in->map.getHeight(); i++)
    {
        Vec2D tilePos = Vec2D(i%in->map.getWidth(),i/in->map.getWidth());
        Vec2D origin = Vec2D(50,50)+Vec2D(48,48)*tilePos;
        DrawRectangleRec(toRayLibRectangle(origin,Vec2D(48,48)),ColorFromHSV(in->map.getTileAt(tilePos)*10, 0.5f,1.0f));
        DrawRectangleLinesEx(toRayLibRectangle(origin,Vec2D(48,48)),1,BLACK);
    }
}*/

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
    float buttonDivider[4] = {3, 2, 1.2f, 1.5f};
    DrawTexturePro(in->background, Rectangle{0,0,600,600},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in->title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTexturePro(in->logoIsart, Rectangle{0,0,250,250},Rectangle{width/16, heigth,100,100},Vector2{100,100}, 0, WHITE);
    for(int i = 0; i < 4; i++)
    {
        DrawTexturePro(in->button, Rectangle{0,0,500,500},Rectangle{width/2,heigth/buttonDivider[i],300,300},Vector2{150,150}, 0, WHITE);
    }
    DrawText("Play", width/2.16f,heigth/3.4f,50,Fade(BLACK,getFade(in->framecounter)));
    DrawText("Load", width/2.16f,heigth/2.17f,50,Fade(BLACK,getFade(in->framecounter)));
    DrawText("Option", width/2.22f,heigth/1.6f,50,Fade(BLACK,getFade(in->framecounter)));
    DrawText("Credit", width/2.22f,heigth/1.26f,50,Fade(BLACK,getFade(in->framecounter)));
    DrawText("Tower Defense", 475,20,80,Fade(BLACK,getFade(in->framecounter)));
    
}

void renderEditor(DataHolder* in)
{
    in->buttonSelected = 0;
    if (drawButton("Save Map", Vec2D(1300,70),Vec2D(200,50), in->mousePos))
    {
        in->buttonSelected = 1;
    }
    if (drawButton("Clear Map", Vec2D(1300,170),Vec2D(200,50), in->mousePos))
    {
        in->buttonSelected = 2;
    }
    if (drawButton("Change view", Vec2D(1300,270),Vec2D(200,50), in->mousePos))
    {
        in->buttonSelected = 3;
    }
    DrawTileMap(in,in->tileRenderType);
}