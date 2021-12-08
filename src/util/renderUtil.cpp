#include "renderUtil.hpp"

Color getRGB(size_t frame)
{
    return ColorFromHSV(mod(frame*0.013f, 0.0f, 1.0f)*360.0f,0.5,1.0);
}

float getFade(size_t frame) {
    size_t tmp = frame%120;
    if (tmp >= 60)
    {
        return (120-tmp)/60.0f;
    }
    return tmp/60.0f;
}

Rectangle toRayLibRectangle(Vec2D origin, Vec2D rectSize)
{
    return (Rectangle){origin.x, origin.y, rectSize.x, rectSize.y};
}

void DrawTileMap(DataHolder* in, RenderType type)
{
    for (int i = 0; i < in->map.getWidth()*in->map.getHeight(); i++)
    {
        Vec2D tilePos = Vec2D(i%in->map.getWidth(),i/in->map.getWidth());
        Vec2D origin = Vec2D(50,50)+Vec2D(48,48)*tilePos;
        unsigned char tile = in->map.getTileAt(tilePos);
        unsigned char tile2 = in->map.getTileAt(tilePos, true);
        if (type == NORMAL && tile >= ROAD_THREEWAY_FORCE_NORTH && tile <= ROAD_THREEWAY_FORCE_WEST)
        {
            tile = tile-7;
        }
        bool gry = (in->holderSelected == 3 || in->holderSelected == 4);
        bool sPos = (tile >= ROAD_NORTH && tile <= ROAD_WEST);
        DrawTexturePro(in->tileTexture,in->tiles.tileCrops.at(tile),toRayLibRectangle(origin,Vec2D(48,48)),{0,0},0.0f, (gry && !sPos) ? GetColor(0xccccccff) : WHITE);
        if (tile2 != UNDEFINED) DrawTexturePro(in->tileTexture,in->tiles.tileCrops.at(tile2),toRayLibRectangle(origin,Vec2D(48,48)),{0,0},0.0f,(gry) ? GetColor(0xccccccff) : WHITE);
        if (type >= BORDER)
        {
            DrawRectangleLinesEx(toRayLibRectangle(origin,Vec2D(48,48)),1,BLACK);
        }
        if (type  == DEBUG)
        {
            DrawText(TextFormat("%d",tile),origin.x+2,origin.y+1,10,BLACK);
            DrawText(TextFormat("%d",tile2),origin.x+2,origin.y+10,10,BLACK);
        }
    }
}

bool drawButton(const char* text, Vec2D pos, Vec2D size, Vec2D mousePos) {
    Vec2D tmp = pos+size;
    bool isInside = (mousePos.x > pos.x && mousePos.y > pos.y && mousePos.x <= tmp.x && mousePos.y <= tmp.y);
    DrawRectangleRounded(toRayLibRectangle(pos,size),0.2f,10,isInside?SKYBLUE:LIGHTGRAY);
    DrawRectangleRoundedLines(toRayLibRectangle(pos,size),0.2f,10,2.0f,BLACK);
    DrawText(text,pos.x+10,pos.y+(size.y/2)-15,30,DARKGRAY);
    return isInside;
}

bool drawButtonMenu(DataHolder* in, const char* text, Vec2D textSize, Vec2D pos, Vec2D size, Vec2D mousePos) {
    Vec2D tmp = pos+size;
    bool isInside = (mousePos.x > pos.x && mousePos.y > pos.y && mousePos.x <= tmp.x && mousePos.y <= tmp.y);
    DrawTexturePro(in->button, Rectangle{0,0,2800,2600}, Rectangle{pos.x-22,pos.y-90,size.x+25,size.y+150}, Vector2{0,0}, 0, WHITE);
    DrawTextEx(in->fontButton, text, Vector2{textSize.x,textSize.y},50,2,isInside?Fade(BLACK,getFade(in->framecounter)):BLACK);
    return isInside;
}

bool drawButtonInvisible(DataHolder* in, Vec2D pos, Vec2D size, Vec2D mousePos) {
    Vec2D tmp = pos+size;
    bool isInside = (mousePos.x > pos.x && mousePos.y > pos.y && mousePos.x <= tmp.x && mousePos.y <= tmp.y);
    DrawRectangleRec(toRayLibRectangle(pos,size),Fade(BLACK,0.5));
    return isInside;
}
void drawMapElements(DataHolder* in, bool editor)
{
    DrawRectangle(0,0,in->screenWidth,in->screenHeight,DARKGREEN);
    Camera2D cam = Camera2D();
    cam.target = Vec2D((int)(in->cameraPos.x),(int)(in->cameraPos.y));
    cam.zoom = in->cameraScale;
    BeginMode2D(cam);
    DrawTileMap(in,in->tileRenderType);
    if (!editor)
    {
        for (std::forward_list<Enemy*>::iterator i = in->enemies.begin(); i != in->enemies.end(); i++)
        {
            int tx = (*i)->getTexture();
            if (tx != 52)
            {
                DrawTexturePro(in->tileTexture,in->tiles.tileCrops.at(53),toRayLibRectangle((*i)->getPosition()*Vec2D(48,48)+Vec2D(50,50),Vec2D(48,48)),Vec2D(24,24),(*i)->getRotation()*RAD2DEG+90.0f,LIGHTGRAY);
                DrawTexturePro(in->tileTexture,in->tiles.tileCrops.at(tx),toRayLibRectangle((*i)->getPosition()*Vec2D(48,48)+Vec2D(50,50),Vec2D(64,64)),Vec2D(32,32),(*i)->getRotation()*RAD2DEG+90.0f,LIGHTGRAY);
            }
            else
            {
                DrawTexturePro(in->tileTexture,in->tiles.tileCrops.at(tx),toRayLibRectangle((*i)->getPosition()*Vec2D(48,48)+Vec2D(50,50),Vec2D(48,48)),Vec2D(24,24),(*i)->getRotation()*RAD2DEG+90.0f,LIGHTGRAY);
            }
        }
        for (std::forward_list<Tower*>::iterator i = in->towers.begin(); i != in->towers.end(); i++)
        {
            DrawTexturePro(in->tileTexture,in->tiles.tileCrops.at(153),toRayLibRectangle((*i)->getPosition()*Vec2D(48,48)+Vec2D(50,50),Vec2D(48,48)),Vec2D(24,24),0,LIGHTGRAY);
            DrawTexturePro(in->tileTexture,in->tiles.tileCrops.at((*i)->getTexture()),toRayLibRectangle((*i)->getPosition()*Vec2D(48,48)+Vec2D(50,50),Vec2D(80,80)),Vec2D(40,40),(*i)->getRotation()*RAD2DEG+90.0f,RED);
        } 
        for (std::forward_list<Missile*>::iterator i = in->missiles.begin(); i != in->missiles.end(); i++)
        {
            DrawTexturePro(in->tileTexture,in->tiles.tileCrops.at(54),toRayLibRectangle((*i)->getPosition()*Vec2D(48,48)+Vec2D(50,50),Vec2D(80,80)),Vec2D(40,40),(*i)->getRotation()*RAD2DEG+90.0f,LIGHTGRAY);
        } 
        for (std::forward_list<Particle*>::iterator i = in->particles.begin(); i != in->particles.end(); i++)
        {
            (*i)->drawParticle();
        }
        DrawTexturePro(in->tileTexture,in->tiles.tileCrops.at(in->map.getTileAt(in->map.startPos,true)),toRayLibRectangle(in->map.startPos*Vec2D(48,48)+Vec2D(50,50),Vec2D(48,48)),Vec2D(),0.0f,WHITE);
        DrawTexturePro(in->tileTexture,in->tiles.tileCrops.at(in->map.getTileAt(in->map.endPos,true)),toRayLibRectangle(in->map.endPos*Vec2D(48,48)+Vec2D(50,50),Vec2D(48,48)),Vec2D(),0.0f,WHITE);
    }
    EndMode2D();
    DrawRectangle(0,0,50,in->screenHeight,LIGHTGRAY);
    DrawRectangle(0,0,in->screenWidth,50,LIGHTGRAY);
    DrawRectangle(1202,0,in->screenWidth,in->screenHeight,LIGHTGRAY);
    DrawRectangle(0,626,in->screenWidth,in->screenHeight,LIGHTGRAY);
}

Tower* drawTowerUpgradeMenu(Tower* t, std::forward_list<Tower*>* towers)
{
    if(t != nullptr)
    {
        if(drawButton("Upgrade", Vec2D(1300, 200), Vec2D(200, 200), Vec2D(GetMouseX(), GetMouseY())))
        {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                t->upgrade();
                return t;
            }
        }

        if(drawButton("Delete", Vec2D(1300, 600), Vec2D(200, 200), Vec2D(GetMouseX(), GetMouseY())))
        {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                std::forward_list<Tower*>::iterator oldT = towers->before_begin();
                for (std::forward_list<Tower*>::iterator i = towers->begin(); i != towers->end(); i++)
                {
                    if((*i) == t)
                    {
                        delete(*i);
                        i = towers->erase_after(oldT);
                        return nullptr;
                    }
                }
            }
        }
    }
    return t;
}