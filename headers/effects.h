#ifndef EFFECTS_H
#define EFFECTS_H



#include "baseClass.h"



class HealthBoost : public Effect{
public:
    HealthBoost(String icon,float duration,float delay,float impact);
    
    void func(RenderWindow& screen,Player& player);
};


class MagicBoost : public Effect{
public:
    MagicBoost(String icon,float duration,float delay,float impact);

    void func(RenderWindow& screen,Player& player);
};




#endif