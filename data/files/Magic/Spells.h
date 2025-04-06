#ifndef SPELLS_H
#define SPELLS_H

#include "../resourses.h"
#include "../Abstract/Influence.h"




class Spell : public Base{
    Sprite icon;
    int counter;
    int cost_magic;
    Influence influence;
    vector<int> images_numbers;


    int cost_spell_id;
    int update_id;
    int onCollision_id;
    
    Spell();
};


#endif
