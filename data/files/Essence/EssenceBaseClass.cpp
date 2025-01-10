#include "EssenceBaseClass.h"

Resistance::Resistance() : magic(Magic()),energy(Energy()),immunity(Bio()),psycho(0),soul(0)  {};

Resistance::Resistance(Magic mag,Physic phy,Energy ene,Bio immu,float pshyc,float soul) : magic(mag),energy(ene),immunity(immu),psycho(pshyc),soul(soul) {};

Property::Property() : value(0),count(0),max(0),time(0) {};

Property::Property(float v,float c,float m,float t) : value(v),count(c),max(m),time(t) {};

Essence::Essence(int pk,string name,string description,string group_name,
           int sight,int hearing,
           vector<int> imgs_numbrs,
           Resistance rest,
           float strength, float agility,float mana_control,float mana_reaction,float charisma,float max_temperature,float MaxAir,
           Property health,Property mana,Property stamina,Property mind,Property speed,
           float int_soul,
           int beh_id
    ){
        this->id = pk;
        this->name = name;
        this->description = description;
        this->GroupName = group_name;
        this->sight = sight;
        this->hearing = hearing;
        this->images_numbers = imgs_numbrs;
        this->resistance = rest;
        this->strength = strength;
        this->agility = agility;
        this->mana_control = mana_control;
        this->mana_reaction = mana_reaction;
        this->charisma = charisma;
        this->max_temperature = max_temperature;
        this->MaxAir = MaxAir;
        this->health = health;
        this->mana = mana;
        this->stamina = stamina;
        this->mind = mind;
        this->speed = speed;
        this->integrity_soul = int_soul;
        this->behavior_id = beh_id;

    };
