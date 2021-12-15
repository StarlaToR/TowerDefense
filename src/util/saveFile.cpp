#include <fstream>
#include <iostream>
#include <string>
#include "saveFile.hpp"

int saveFile(SaveData& data, char slot)
{
    std::ofstream save;
    std::string path = "saves/save0.bin";
    path[10] = slot + '0';
    save.open(path, std::ios::out | std::ios::binary | std::ios::trunc);
    if (!save.is_open()) return -1;
    save.write((char*)(&data),sizeof(data));
    save.close();
    return 0;
}

int loadFile(SaveData& data, char slot)
{
    data.maxLevel = 0;
    data.timePlayed = 0;
    std::ifstream save;
    std::string path = "saves/save0.bin";
    path[10] = slot + '0';
    save.open(path, std::ios::in | std::ios::binary);
    if (!save.is_open()) return -1;
    save.read((char*)(&data),sizeof(data));
    save.close();
    return 0;
}