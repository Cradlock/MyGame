#ifndef INFLUENCE_H
#define INFLUENCE_H

struct Physic{
    float cutting,blunt,piercing,crushing;
    
    Physic(float cutting = 0.0f, float blunt = 0.0f, float piercing = 0.0f, float crushing = 0.0f)
        : cutting(cutting), blunt(blunt), piercing(piercing), crushing(crushing) {}
};

struct Energy{
    float minus_t,plus_t,electricity,radiation;


};

struct Magic{
    float cost_magic;
    Energy energy_impact;
    Physic physic_impact;

    Magic(float cost_magic = 0.0f, Energy energy_impact = Energy(), Physic physic_impact = Physic())
        : cost_magic(cost_magic), energy_impact(energy_impact), physic_impact(physic_impact) {}

};

struct Bio{
    float micro_organic;
    float toxic;

 Bio(float micro_organic = 0.0f, float toxic = 0.0f)
        : micro_organic(micro_organic), toxic(toxic) {}
};


class Influence{
    Magic magic;
    Energy energy;
    Physic physic;
    Bio bio;
    float soul,psycho;

    float conceptual;

};







#endif