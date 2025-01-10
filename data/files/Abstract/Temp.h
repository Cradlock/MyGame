#ifndef TEMP_H
#define TEMP_H

#include "resourses.h"
#include "Spells.h"
#include "Influence.h"
#include "Effects/Effects.h"

class Temp : public Base{
    Sprite spr;
    int counter,stock;
    vector<shared_ptr<Texture>> images;
    vector<Effect> effects;
    Influence influence;
    function<void()> update;
    function<void()> onCollision;
    
    Temp(vector<shared_ptr<Texture>> imgs,function<void()> upd,function<void()> onColl);

};


#endif