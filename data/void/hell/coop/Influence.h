#pragma once

#include "../../base.h"
#include "../BaseClass.h"


struct Physic{
    // mechanical
    unsigned int cut = 0,prick = 0,blunt = 0;
    // Electro
    unsigned int voltage = 0,power = 0;
    // Acoustic
    unsigned int frequency = 0,volume = 0;
    // Thermal
    signed int temperature = 0;
    // Radiation
    unsigned int rad = 0;
    // Force
    float impulse = 0;

    Physic(unordered_map<string,float> data);
    
};

struct Bio{
    // infection
    float infection = 0;
    // Dose
    float dose = 0;
    // toxin
    float toxin = 0;
   
};


struct Psycho{
    float fear = 0.0f;
    float confusion = 0.0f;
    float madness = 0.0f;
    float suggestion = 0.0f;
};


struct Mana{
    // Mana
    float rawMana = 0;
    unsigned int powerMana = 0;

    // Another Influence
    variant<Psycho,Bio,Physic> virtual_influence;
    
};

using type_influence = variant<Physic,Bio,Mana,Psycho>;

class Influence{
public:
 
   Influence(vector<type_influence> obj);
private:
   vector<type_influence> value; 
   
};




