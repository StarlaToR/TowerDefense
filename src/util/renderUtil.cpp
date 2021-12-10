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

void DrawTileMap(DataHolder& in, RenderType type)
{
    for (int i = 0; i < in.lists.map.getWidth()*in.lists.map.getHeight(); i++)
    {
        Vec2D tilePos = Vec2D(i%in.lists.map.getWidth(),i/in.lists.map.getWidth());
        Vec2D origin = Vec2D(50,50)+Vec2D(48,48)*tilePos;
        unsigned char tile = in.lists.map.getTileAt(tilePos);
        unsigned char tile2 = in.lists.map.getTileAt(tilePos, true);
        if (type == NORMAL && tile >= ROAD_THREEWAY_FORCE_NORTH && tile <= ROAD_THREEWAY_FORCE_WEST)
        {
            tile = tile-7;
        }
        bool gry = (in.holderSelected == 3 || in.holderSelected == 4);
        bool sPos = (tile >= ROAD_NORTH && tile <= ROAD_WEST);
        DrawTexturePro(in.textures.tileTexture,in.lists.tiles.tileCrops.at(tile),toRayLibRectangle(origin,Vec2D(48,48)),{0,0},0.0f, (gry && !sPos) ? GetColor(0xccccccff) : WHITE);
        if (tile2 != UNDEFINED) DrawTexturePro(in.textures.tileTexture,in.lists.tiles.tileCrops.at(tile2),toRayLibRectangle(origin,Vec2D(48,48)),{0,0},0.0f,(gry) ? GetColor(0xccccccff) : WHITE);
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

bool drawButtonMenu(DataHolder& in, const char* text, Vec2D textSize, Vec2D pos, Vec2D size, Vec2D mousePos) {
    Vec2D tmp = pos+size;
    bool isInside = (mousePos.x > pos.x && mousePos.y > pos.y && mousePos.x <= tmp.x && mousePos.y <= tmp.y);
    DrawTexturePro(in.textures.button, Rectangle{0,0,2800,2600}, Rectangle{pos.x-22,pos.y-90,size.x+25,size.y+150}, Vector2{0,0}, 0, WHITE);
    DrawTextEx(in.fontButton, text, Vector2{textSize.x,textSize.y},50,2,isInside?Fade(BLACK,getFade(in.framecounter)):BLACK);
    return isInside;
}

bool drawButtonInvisible(Vec2D pos, Vec2D size, Vec2D mousePos) {
    Vec2D tmp = pos+size;
    bool isInside = (mousePos.x > pos.x && mousePos.y > pos.y && mousePos.x <= tmp.x && mousePos.y <= tmp.y);
    //DrawRectangleRec(toRayLibRectangle(pos,size),Fade(BLACK,0.5));
    return isInside;
}
void drawMapElements(DataHolder& in, bool editor)

{
    DrawRectangle(0,0,in.screenWidth,in.screenHeight,DARKGREEN);
    Camera2D cam = Camera2D();
    cam.target = Vec2D((int)(in.cameraPos.x),(int)(in.cameraPos.y));
    cam.zoom = in.cameraScale;
    BeginMode2D(cam);
    DrawTileMap(in,in.tileRenderType);
    if (!editor)
    {
        for (std::list<Enemy*>::iterator i = in.lists.enemies.begin(); i != in.lists.enemies.end(); i++)
        {
            int tx = (*i)->getTexture();
            if (tx != 52)
            {
                DrawTexturePro(in.textures.tileTexture,in.lists.tiles.tileCrops.at(53),toRayLibRectangle((*i)->getPosition()*Vec2D(48,48)+Vec2D(50,50),Vec2D(48,48)),Vec2D(24,24),(*i)->getRotation()*RAD2DEG+90.0f,LIGHTGRAY);
                DrawTexturePro(in.textures.tileTexture,in.lists.tiles.tileCrops.at(tx),toRayLibRectangle((*i)->getPosition()*Vec2D(48,48)+Vec2D(50,50),Vec2D(64,64)),Vec2D(32,32),(*i)->getRotation()*RAD2DEG+90.0f,GetColor((*i)->getColor()));
            }
            else
            {
                DrawTexturePro(in.textures.tileTexture,in.lists.tiles.tileCrops.at(tx),toRayLibRectangle((*i)->getPosition()*Vec2D(48,48)+Vec2D(50,50),Vec2D(48,48)),Vec2D(24,24),(*i)->getRotation()*RAD2DEG+90.0f,GetColor((*i)->getColor()));
            }
            DrawRectangleRec(toRayLibRectangle((*i)->getPosition()*Vec2D(48,48)+Vec2D(26,20),Vec2D(48,8)),BLACK);
            DrawRectangleRec(toRayLibRectangle((*i)->getPosition()*Vec2D(48,48)+Vec2D(27,21),Vec2D(46,6)),RED);
            DrawRectangleRec(toRayLibRectangle((*i)->getPosition()*Vec2D(48,48)+Vec2D(27,21),Vec2D(46.0f*((*i)->getHealth()),6)),GREEN);
        }
        //for (std::forward_list<Tower*>::iterator i = in.lists.towers.begin(); i != in.lists.towers.end(); i++)
        for (Tower* tower : in.lists.towers)
        {
            DrawTexturePro(in.textures.tileTexture,in.lists.tiles.tileCrops.at(153),toRayLibRectangle(tower->getPosition()*Vec2D(48,48)+Vec2D(50,50),Vec2D(48,48)),Vec2D(24,24),0,LIGHTGRAY);
            DrawTexturePro(in.textures.tileTexture,in.lists.tiles.tileCrops.at(tower->getTexture()),toRayLibRectangle(tower->getPosition()*Vec2D(48,48)+Vec2D(50,50),Vec2D(80,80)),Vec2D(40,40),tower->getRotation()*RAD2DEG+90.0f,GetColor(tower->getColor()));
        }
        for (std::forward_list<Missile*>::iterator i = in.lists.missiles.begin(); i != in.lists.missiles.end(); i++)
        {
            DrawTexturePro(in.textures.tileTexture,in.lists.tiles.tileCrops.at(54),toRayLibRectangle((*i)->getPosition()*Vec2D(48,48)+Vec2D(50,50),Vec2D(80,80)),Vec2D(40,40),(*i)->getRotation()*RAD2DEG+90.0f,GetColor((*i)->getColor()));
        } 
        for (std::forward_list<Particle*>::iterator i = in.lists.particles.begin(); i != in.lists.particles.end(); i++)
        {
            (*i)->drawParticle();
        }
        DrawTexturePro(in.textures.tileTexture,in.lists.tiles.tileCrops.at(in.lists.map.getTileAt(in.lists.map.startPos,true)),toRayLibRectangle(in.lists.map.startPos*Vec2D(48,48)+Vec2D(50,50),Vec2D(48,48)),Vec2D(),0.0f,WHITE);
        DrawTexturePro(in.textures.tileTexture,in.lists.tiles.tileCrops.at(in.lists.map.getTileAt(in.lists.map.endPos,true)),toRayLibRectangle(in.lists.map.endPos*Vec2D(48,48)+Vec2D(50,50),Vec2D(48,48)),Vec2D(),0.0f,WHITE);
        if (in.selectedTower != nullptr)
        {
            DrawCircleV(in.selectedTower->getPosition()*Vec2D(48,48)+Vec2D(50,50),in.selectedTower->getRange()*48.0f,Fade(RED,0.2f));
        }
    }
    EndMode2D();
    DrawTexture(in.textures.gameUI,0,0,WHITE);
}

Tower* drawTowerUpgradeMenu(Tower* t, DataHolder& in, int& button)
{
    if(t != nullptr)
    {
        DrawRectangleRec(toRayLibRectangle(Vec2D(1250,70),Vec2D(320,500)),GRAY);
        DrawText(t->getName(),1280,100,20,BLACK);
        DrawText(TextFormat("Level: %d",t->getLevel()),1280,145,20,BLACK);
        DrawText(TextFormat("Health: %d%%",(int)(t->getHealth()*100)),1280,175,20,t->getHealth() > 0.5 ? DARKGREEN : (t->getHealth() > 0.15 ? ORANGE : RED));
        if(drawButton("Delete", Vec2D(1330, 330), Vec2D(150, 50), Vec2D(GetMouseX(), GetMouseY())))
        {
            button = 1;
        }
        if(t->getLevel() < 4 && drawButton("Upgrade", Vec2D(1330, 250), Vec2D(150, 50), Vec2D(GetMouseX(), GetMouseY())))
        {
            button = 2;
        }
    }
    else{
        for (int i = 0; i < 3; i++){
            DrawTexturePro(in.textures.tileTexture,in.lists.tiles.tileCrops.at(in.lists.towerHolders.holders[i].getTexture()),toRayLibRectangle(in.lists.towerHolders.holders[i].getPosition(),Vec2D(128,128)),Vec2D(),0,GRAY);
            DrawRectangleRec(toRayLibRectangle(in.lists.towerHolders.holders[i].getPosition(),Vec2D(128,128)), Fade(BLACK,0.5));
        }
    }
    return t;
}

void drawTileAt(Texture& tx, Rectangle tile, Vec2D position, Vec2D size, float rotation, Color& color, bool center)
{

}