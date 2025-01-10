#ifndef ESSENCEBASECLASS_H
#define ESSENCEBASECLASS_H


#include "../resourses.h"
#include "../Effects/Effects.h"
#include "../Item/ItemBaseClass.h"
#include "../Magic/Spells.h"
#include "../Abstract/Group.h"

struct Resistance{
    Magic magic;
    Physic physic;
    Energy energy;
    Bio immunity;
    float psycho,soul;

    Resistance();

    Resistance(Magic mag,Physic phy,Energy ene,Bio immu,float pshyc,float soul);
};

struct Property{
    float value,count,max,time;

    Property();

    Property(float v,float c,float m,float t);
};

class Essence : public Base{
public:
    unsigned int id;

    string GroupName;
    string name;
    string description;

    int sight;
    int hearing;

    Sprite spr;
    vector<int> images_numbers;
    
    float Air,MaxAir;

    unordered_map<unsigned int , int> familiar;

    vector<Effect> effects_list;
    Resistance resistance;
    vector<Item> inventory;
    Item hand;
    vector<Spell> magic_spells;

    float strength,agility;
    float mana_control,mana_reaction; 
    float charisma;

    float tepmerature,max_temperature;

    Property health;
    Property mana;
    Property stamina;
    Property mind;

    float integrity_soul;
    float hunger,thirst;

    Property speed;


    int behavior_id;
    

    Essence(int pk,string name,string description,string group_name,
           int sight,int hearing,
           vector<int> imgs_numbrs,
           Resistance rest,
           float strength, float agility,float mana_control,float mana_reaction,float charisma,float max_temperature,float MaxAir,
           Property health,Property mana,Property stamina,Property mind,Property speed,
           float int_soul,
           int beh_id
    );

    void behaivor();
};


extern unordered_map<int,Essence> GLOBAL_ESSENCES_list;


#endif
