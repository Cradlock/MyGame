#ifndef INFLUENCE_H
#define INFLUENCE_H

struct Physic{
    float cutting,blunt,piercing,crushing;
    
    Physic();
    Physic(float cutting, float blunt, float piercing, float crushing);
};

struct Energy{
    float minus_t,plus_t,electricity,radiation;
    
    Energy();
    Energy(float min,float pl,float ele,float);
};

struct Magic{
    float cost_magic;
    Energy energy_impact;
    Physic physic_impact;
    
    Magic();
    Magic(float cost_magic, Energy energy_impact, Physic physic_impact);

};

struct Bio{
    float micro_organic;
    float toxic;
    
    Bio();
    Bio(float micro_organic, float toxic);
};


class Influence{
    Magic magic;
    Energy energy;
    Physic physic;
    Bio bio;
    float soul,psycho;

    float conceptual;
    Influence();
    Influence(Magic magic, Energy energy, Physic physic, Bio bio,float soul, float psycho, float conceptual);
};







#endif