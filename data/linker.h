#ifndef LINKER_H
#define LINKER_H

#include <SFML/Audio.hpp>
#include "files/resourses.h"
#include "files/Abstract/World.h"
#include "files/Locations/location.h"
#include "files/constants.h"

#include "EssenceDB.h"
#include "itemsDB.h"
#include "ObjectsDB.h"




extern unordered_map<int,Object> localObjects;


extern vector<shared_ptr<Light>> localLight;



extern vector<int> objects_top;
extern vector<int> objects_bottom;

extern unordered_map<string,Texture> textures;
extern vector<PartWorld> partes;

extern vector<Item> items;

extern vector<Essence> essences;

extern vector<Projectile> projectiles;

extern void init_db();

#endif