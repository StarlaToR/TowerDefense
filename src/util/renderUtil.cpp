#include "renderUtil.hpp"

Color getRGB(size_t frame)
{
    return ColorFromHSV(mod(frame * 0.013f, 0.0f, 1.0f) * 360.0f, 0.5, 1.0);
}

float getFade(size_t frame)
{
    size_t tmp = frame % 120;
    if (tmp >= 60)
    {
        return (120 - tmp) / 60.0f;
    }
    return tmp / 60.0f;
}

Rectangle toRayLibRectangle(Vec2D origin, Vec2D rectSize)
{
    return (Rectangle){origin.x, origin.y, rectSize.x, rectSize.y};
}

void DrawTileMap(DataHolder &in, RenderType type)
{
    Vec2D mTilePos = (in.mousePos) / (48 * in.cameraScale) - (Vec2D(50, 50) - in.cameraPos) / 48.0f;
    for (int i = 0; i < in.lists.map.getWidth() * in.lists.map.getHeight(); i++)
    {
        Vec2D tilePos = Vec2D(i % in.lists.map.getWidth(), i / in.lists.map.getWidth());
        Vec2D origin = Vec2D(50, 50) + Vec2D(48, 48) * tilePos;
        unsigned char tile = in.lists.map.getTileAt(tilePos);
        unsigned char tile2 = in.lists.map.getTileAt(tilePos, true);
        if (type == NORMAL && tile >= ROAD_THREEWAY_FORCE_NORTH && tile <= ROAD_THREEWAY_FORCE_WEST)
        {
            tile = tile - 7;
        }
        bool gry = (in.holderSelected >= 3 && in.holderSelected <= 5);
        bool sPos = (tile >= ROAD_NORTH && tile <= ROAD_WEST);
        DrawTexturePro(in.textures.tileTexture, in.lists.tiles.tileCrops.at(tile), toRayLibRectangle(origin, Vec2D(48, 48)), {0, 0}, 0.0f, (gry && !sPos) ? GetColor(0xccccccff) : WHITE);
        if (tile2 != UNDEFINED)
            DrawTexturePro(in.textures.tileTexture, in.lists.tiles.tileCrops.at(tile2), toRayLibRectangle(origin, Vec2D(48, 48)), {0, 0}, 0.0f, (gry) ? GetColor(0xccccccff) : WHITE);
        if (type >= BORDER || mTilePos.isIntEquivalent(tilePos))
        {
            DrawRectangleLinesEx(toRayLibRectangle(origin, Vec2D(48, 48)), 1, BLACK);
        }
        if (type == DEBUG)
        {
            DrawText(TextFormat("%d", tile), origin.x + 2, origin.y + 1, 10, BLACK);
            DrawText(TextFormat("%d", tile2), origin.x + 2, origin.y + 10, 10, BLACK);
        }
    }
}

void DrawSpecialTiles(DataHolder &in)
{
    for (int i = 0; i < in.lists.map.getWidth() * in.lists.map.getHeight(); i++)
    {
        Vec2D tilePos = Vec2D(i % in.lists.map.getWidth(), i / in.lists.map.getWidth());
        Vec2D origin = Vec2D(50, 50) + Vec2D(48, 48) * tilePos;
        unsigned char tile = in.lists.map.getTileAt(tilePos, true);
        if (tile >= TUNNEL_NORTH && tile <= TUNNEL_WEST)
        {
            DrawTexturePro(in.textures.tileTexture, in.lists.tiles.tileCrops.at(tile), toRayLibRectangle(origin, Vec2D(48, 48)), {0, 0}, 0.0f, WHITE);
        }
    }
}

bool drawButton(DataHolder &in, const char *text, Vec2D pos, Vec2D size, Vec2D mousePos)
{
    Vec2D tmp = pos + size;
    bool isInside = (mousePos.x > pos.x && mousePos.y > pos.y && mousePos.x <= tmp.x && mousePos.y <= tmp.y);
    DrawRectangleRounded(toRayLibRectangle(pos, size), 0.2f, 10, isInside ? SKYBLUE : LIGHTGRAY);
    DrawRectangleRoundedLines(toRayLibRectangle(pos, size), 0.2f, 10, 2.0f, BLACK);
    DrawTextEx(in.fontButton, text, Vec2D(pos.x + (size.x > 200 ? size.x / 2 - 30 : 10), pos.y + (size.y / 2) - 15), 30, 0, DARKGRAY);
    return isInside;
}

bool drawButtonMenu(DataHolder &in, const char *text, Vec2D textSize, Vec2D pos, Vec2D size, Vec2D mousePos)
{
    Vec2D tmp = pos + size;
    bool isInside = (mousePos.x > pos.x && mousePos.y > pos.y && mousePos.x <= tmp.x && mousePos.y <= tmp.y);
    DrawTexturePro(isInside ? in.textures.buttonDown : in.textures.button, Rectangle{0, 0, 2800, 2600}, Rectangle{pos.x - 22, pos.y - 90 + isInside * 12, size.x + 25, size.y + 150}, Vector2{0, 0}, 0, WHITE);
    DrawTextEx(in.fontButton, text, Vec2D{textSize.x, textSize.y + isInside * 12}, 50, 2, isInside ? Fade(BLACK, getFade(in.framecounter)) : BLACK);
    return isInside;
}

bool drawButtonInvisible(Vec2D pos, Vec2D size, Vec2D mousePos)
{
    Vec2D tmp = pos + size;
    bool isInside = (mousePos.x > pos.x && mousePos.y > pos.y && mousePos.x <= tmp.x && mousePos.y <= tmp.y);
    return isInside;
}

void drawMapElements(DataHolder &in, bool editor)
{
    DrawRectangle(0, 0, in.screenWidth, in.screenHeight, DARKGREEN);
    Camera2D cam = Camera2D();
    cam.target = Vec2D((int)(in.cameraPos.x), (int)(in.cameraPos.y));
    cam.zoom = in.cameraScale;
    BeginMode2D(cam);
    DrawTileMap(in, in.tileRenderType);
    if (!editor)
    {
        char drawBoss = 0;
        Enemy *boss;
        for (std::list<Enemy *>::iterator i = in.lists.enemies.begin(); i != in.lists.enemies.end(); i++)
        {
            int tx = (*i)->getTexture();
            int color = (*i)->getColor();
            if (tx != TOWER_BASE)
            {
                if ((*i)->isUnderGround())
                    continue;
                if (tx != 52)
                {
                    DrawTexturePro(in.textures.tileTexture, in.lists.tiles.tileCrops.at(53), toRayLibRectangle((*i)->getPosition() * Vec2D(48, 48) + Vec2D(50, 50), Vec2D(48, 48)), Vec2D(24, 24), (*i)->getRotation() * RAD2DEG + 90.0f, LIGHTGRAY);
                    DrawTexturePro(in.textures.tileTexture, in.lists.tiles.tileCrops.at(tx), toRayLibRectangle((*i)->getPosition() * Vec2D(48, 48) + Vec2D(50, 50), Vec2D(64, 64)), Vec2D(32, 32), (*i)->getRotation() * RAD2DEG + 90.0f, (color == 0 ? getRGB(in.framecounter) : GetColor(color)));
                }
                else
                {
                    DrawTexturePro(in.textures.tileTexture, in.lists.tiles.tileCrops.at(tx), toRayLibRectangle((*i)->getPosition() * Vec2D(48, 48) + Vec2D(50, 50), Vec2D(48, 48)), Vec2D(24, 24), (*i)->getRotation() * RAD2DEG + 90.0f, (color == 0 ? getRGB(in.framecounter) : GetColor(color)));
                }
                DrawRectangleRec(toRayLibRectangle((*i)->getPosition() * Vec2D(48, 48) + Vec2D(26, 20), Vec2D(48, 8)), BLACK);
                DrawRectangleRec(toRayLibRectangle((*i)->getPosition() * Vec2D(48, 48) + Vec2D(27, 21), Vec2D(46, 6)), RED);
                DrawRectangleRec(toRayLibRectangle((*i)->getPosition() * Vec2D(48, 48) + Vec2D(27, 21), Vec2D(46.0f * ((*i)->getHealth()), 6)), GREEN);
            }
            else
            {
                boss = *i;
                drawBoss = 1 + boss->isUnderGround();
            }
        }
        for (Tower *tower : in.lists.towers)
        {
            DrawTexturePro(in.textures.tileTexture, in.lists.tiles.tileCrops.at(153), toRayLibRectangle(tower->getPosition() * Vec2D(48, 48) + Vec2D(50, 50), Vec2D(48, 48)), Vec2D(24, 24), 0, LIGHTGRAY);
            DrawTexturePro(in.textures.tileTexture, in.lists.tiles.tileCrops.at(tower->getTexture()), toRayLibRectangle(tower->getPosition() * Vec2D(48, 48) + Vec2D(50, 50), Vec2D(80, 80)), Vec2D(40, 40), tower->getRotation() * RAD2DEG + 90.0f, GetColor(tower->getColor()));
        }
        unsigned char tmp1 = in.lists.map.getTileAt(in.lists.map.startPos, true);
        if (tmp1 != UNDEFINED)
            DrawTexturePro(in.textures.tileTexture, in.lists.tiles.tileCrops.at(tmp1), toRayLibRectangle(in.lists.map.startPos * Vec2D(48, 48) + Vec2D(50, 50), Vec2D(48, 48)), Vec2D(), 0.0f, WHITE);
        tmp1 = in.lists.map.getTileAt(in.lists.map.endPos, true);
        if (tmp1 != UNDEFINED)
            DrawTexturePro(in.textures.tileTexture, in.lists.tiles.tileCrops.at(tmp1), toRayLibRectangle(in.lists.map.endPos * Vec2D(48, 48) + Vec2D(50, 50), Vec2D(48, 48)), Vec2D(), 0.0f, WHITE);
        for (std::forward_list<Missile *>::iterator i = in.lists.missiles.begin(); i != in.lists.missiles.end(); i++)
        {
            DrawTexturePro(in.textures.tileTexture, in.lists.tiles.tileCrops.at(54), toRayLibRectangle((*i)->getPosition() * Vec2D(48, 48) + Vec2D(50, 50), Vec2D(80, 80)), Vec2D(40, 40), (*i)->getRotation() * RAD2DEG + 90.0f, GetColor((*i)->getColor()));
        }
        DrawSpecialTiles(in);
        if (drawBoss == 2)
        {
            DrawTexturePro(in.textures.boss, in.lists.tiles.tileCrops.at(boss->getTexture()), toRayLibRectangle((boss)->getPosition() * Vec2D(48, 48) + Vec2D(70, 70), Vec2D(192, 192)), Vec2D(96, 96), (boss)->getRotation() * RAD2DEG - 90.0f, Fade(BLACK,0.5));
            DrawTexturePro(in.textures.boss, in.lists.tiles.tileCrops.at(boss->getTexture()), toRayLibRectangle((boss)->getPosition() * Vec2D(48, 48) + Vec2D(50, 50), Vec2D(192, 192)), Vec2D(96, 96), (boss)->getRotation() * RAD2DEG - 90.0f, WHITE);
            DrawRectangleRec(toRayLibRectangle((boss)->getPosition() * Vec2D(48, 48) + Vec2D(6, -8), Vec2D(88, 18)), BLACK);
            DrawRectangleRec(toRayLibRectangle((boss)->getPosition() * Vec2D(48, 48) + Vec2D(7, -7), Vec2D(86, 16)), RED);
            DrawRectangleRec(toRayLibRectangle((boss)->getPosition() * Vec2D(48, 48) + Vec2D(7, -7), Vec2D(86.0f * ((boss)->getHealth()), 16)), GREEN);
        }
        for (std::forward_list<Particle *>::iterator i = in.lists.particles.begin(); i != in.lists.particles.end(); i++)
        {
            (*i)->drawParticle(in.textures.tileTexture, in.lists.tiles);
        }
        if (drawBoss == 1)
        {
            DrawTexturePro(in.textures.boss, in.lists.tiles.tileCrops.at(boss->getTexture()), toRayLibRectangle((boss)->getPosition() * Vec2D(48, 48) + Vec2D(70, 70), Vec2D(192, 192)), Vec2D(96, 96), (boss)->getRotation() * RAD2DEG - 90.0f, Fade(BLACK,0.5));
            DrawTexturePro(in.textures.boss, in.lists.tiles.tileCrops.at(boss->getTexture()), toRayLibRectangle((boss)->getPosition() * Vec2D(48, 48) + Vec2D(50, 50), Vec2D(192, 192)), Vec2D(96, 96), (boss)->getRotation() * RAD2DEG - 90.0f, WHITE);
            DrawRectangleRec(toRayLibRectangle((boss)->getPosition() * Vec2D(48, 48) + Vec2D(6, -8), Vec2D(88, 18)), BLACK);
            DrawRectangleRec(toRayLibRectangle((boss)->getPosition() * Vec2D(48, 48) + Vec2D(7, -7), Vec2D(86, 16)), RED);
            DrawRectangleRec(toRayLibRectangle((boss)->getPosition() * Vec2D(48, 48) + Vec2D(7, -7), Vec2D(86.0f * ((boss)->getHealth()), 16)), GREEN);
        }
        if (in.selectedTower != nullptr)
        {
            DrawCircleV(in.selectedTower->getPosition() * Vec2D(48, 48) + Vec2D(50, 50), in.selectedTower->getRange() * 48.0f, Fade(RED, 0.2f));
            DrawTexturePro(in.textures.tileTexture, in.lists.tiles.tileCrops.at(153), toRayLibRectangle(in.selectedTower->getPosition() * Vec2D(48, 48) + Vec2D(50, 50), Vec2D(48, 48)), Vec2D(24, 24), 0, LIGHTGRAY);
            DrawTexturePro(in.textures.tileTexture, in.lists.tiles.tileCrops.at(in.selectedTower->getTexture()), toRayLibRectangle(in.selectedTower->getPosition() * Vec2D(48, 48) + Vec2D(50, 50), Vec2D(80, 80)), Vec2D(40, 40), in.selectedTower->getRotation() * RAD2DEG + 90.0f, GetColor(in.selectedTower->getColor()));
        }
    }
    EndMode2D();
    DrawTexture(in.textures.gameUI, 0, 0, WHITE);
}

void drawTowerUpgradeMenu(DataHolder &in, int &button)
{
    if (in.selectedTower != nullptr)
    {
        DrawRectangleRec(toRayLibRectangle(Vec2D(1265, 70), Vec2D(320, 500)), GRAY);
        DrawTextEx(in.fontButton, in.selectedTower->getName(), Vec2D(1280, 100), 20, 0,BLACK);
        DrawTextEx(in.fontButton, TextFormat("Level: %d", in.selectedTower->getLevel()), Vec2D(1380, 145), 20, 0, BLACK);
        if (drawButton(in, "Sell", Vec2D(1330, 330), Vec2D(200, 100), Vec2D(GetMouseX(), GetMouseY())))
        {
            button = 1;
        }
        DrawTextEx(in.fontButton, TextFormat("Profit: %d", in.selectedTower->getCost() * in.selectedTower->getLevel() / 4), Vec2D(1380, 400), 20, 0,BLACK);
        if (in.selectedTower->getLevel() < 4)
        {
            if (drawButton(in, "Upgrade", Vec2D(1330, 200), Vec2D(200, 100), Vec2D(GetMouseX(), GetMouseY())))
            {
                button = 2;
            }
            DrawTextEx(in.fontButton, TextFormat("Cost: %d", in.selectedTower->getCost()), Vec2D(1380, 265), 20,0,  BLACK);
        }
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            DrawTexturePro(in.textures.tileTexture, in.lists.tiles.tileCrops.at(in.lists.towerHolders.holders[i].getTexture()), toRayLibRectangle(in.lists.towerHolders.holders[i].getPosition(), Vec2D(128, 128)), Vec2D(), 0, GRAY);
            DrawRectangleRec(toRayLibRectangle(in.lists.towerHolders.holders[i].getPosition(), Vec2D(128, 128)), Fade(BLACK, 0.5));
            DrawTextEx(in.fontButton, TextFormat("Cost: %d", in.lists.towerHolders.holders[i].getCost()), Vec2D(in.lists.towerHolders.holders[i].getPosition().x + 150, in.lists.towerHolders.holders[i].getPosition().y + 50), 20, 0,BLACK);
        }
    }
}
