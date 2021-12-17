#pragma once
#include <stddef.h>

struct SaveData
{
    int maxLevel = 0;
    int maxWave = 0;
    size_t timePlayed = 0;
};

int saveFile(SaveData& data, char slot);
int loadFile(SaveData& data, char slot);