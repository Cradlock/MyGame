#ifndef OBJECTBASECLASS_H
#define OBJECTBASECLASS_H

#include "../resourses.h"
#include "../Effects/Effects.h"
#include "../Item/ItemBaseClass.h"
#include "../Essence/EssenceBaseClass.h"


#define Void 0

#define Ground 1
#define Gravel 2
#define Grass 3
#define Stone 4
#define Cobblestone 5
#define StoneTile 6
#define Myceli 7
#define OvergrownGrass 8
#define OvergrownMushroom 9
#define ShallowWater 10
#define MediumWater 11
#define DeepWater 12
#define Dirt 13
#define Swamp 14   
#define Lava 15
#define Sand 16
#define Magma 17 
#define darkWater 18 

#define Tree 1

class Object : public Base{
public:
    float endurance;
    string title;
    vector<int> images_numbers;
    Sprite spr;
    vector<Effect> effects;
    vector<Item> items;
    function<void()> TouchFunc;
    function<void()> destructionFunc;
    int position_level;
    bool IsExactSize;
    float wmin,wmax;
    float hmin,hmax;
    
    Object(int l,string t,float e,vector<int> images,float w,float h);

    Object(int l,string t,float e,vector<int> images,float ws,float we,float hs,float he);

    Object(int l,string t,float e,vector<int> images,function<void()> f,vector<Effect> efs,vector<Item> ite);

};


extern vector<Object> Global_Objects_list;


class Build : public Base{
    Sprite spr;
    vector<Object> objects;
    vector<Item> items;
    vector<Effect> effects;
    vector<Essence> essences;
    function<void()> func;
    
};


class PartWorld : public Base{
public:
    Sprite spr;
    function<void()> onCollision;
    PartWorld();
    PartWorld(int x,int y);
    
};









#endif