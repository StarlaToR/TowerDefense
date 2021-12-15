#pragma once
#include <stddef.h>
struct SaveData
{
    char maxLevel = 0;
    size_t timePlayed = 0;
};

int saveFile(SaveData& data, char slot);
int loadFile(SaveData& data, char slot);