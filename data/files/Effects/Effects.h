#ifndef EFFECTS_H
#define EFFECTS_H


#include "../resourses.h"


//Existing
#define Passive 1000
#define Time  1001
#define Trigger  1002
#define IfHaveItem 1003

//Activate
#define GetInfluence 1004
//Passive
#define IfTime 1005

class Effect : public Base{
public:
    float delay,duration,impact;
    int type_activate;
    int type_existing;
    String title,description;
    Sprite spr_icon;
    string tex_icon;
    function<void()> func;
    bool isView;

    Effect();
};


extern unordered_map<int,Effect> GLOBAL_EFFECT_list;


#endif