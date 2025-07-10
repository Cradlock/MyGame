#pragma once

#include "base.h"


class ModManager{
public:

unordered_map<string,fs::path> mods;


ModManager();

void init();



private:
void checkMods();

void getAllMods();

void loadBeforeMod();

void loadAfterMod();



};
