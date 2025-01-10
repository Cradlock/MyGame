#ifndef SPELLS_H
#define SPELLS_H

#include "../resourses.h"
#include "../Abstract/Influence.h"




class Spell : public Base{
    Sprite icon;
    int counter;
    int cost_magic;
    Influence influence;
    vector<string> images;

    function<void()> update;
    function<void()> onCollision;
    
    Spell(string icon_path,int c_m,vector<string> imgsl,Influence infl,function<void()> up,function<void()> onColl);
};


#endif
