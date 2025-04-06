#ifndef ITEMBASECLASS_H
#define ITEMBASECLASS_H


#include "../resourses.h"
#include "../Effects/Effects.h"



#define Food 2001
#define Weapon 2002
#define Poison 2003
#define Armer 2003
#define Accessory 2004



class Item : public Base{
public:
    int counter;
    Sprite spr;
    int level;
    vector<int> slots;
    vector<Effect> effects;
    vector<int>  images_numbers;

    int UseFunction;
    int InInventoryFunction;
    int InSlotFunction; 

    Light light;
    
};

class Projectile : public Base{};

extern unordered_map<int,Item> GLOBAL_ITEM_list;

#endif