#include "Influence.h"


Physic::Physic() : cutting(0), blunt(0), piercing(0), crushing(0) {}

Physic::Physic(float cutting, float blunt, float piercing, float crushing)
    : cutting(cutting), blunt(blunt), piercing(piercing), crushing(crushing) {}


Energy::Energy() : minus_t(0), plus_t(0), electricity(0), radiation(0) {}

Energy::Energy(float min, float pl, float ele, float rad)
    : minus_t(min), plus_t(pl), electricity(ele), radiation(rad) {}


Magic::Magic() : cost_magic(0), energy_impact(Energy()), physic_impact(Physic()) {}

Magic::Magic(float cost_magic, Energy energy_impact, Physic physic_impact)
    : cost_magic(cost_magic), energy_impact(energy_impact), physic_impact(physic_impact) {}


Bio::Bio() : micro_organic(0), toxic(0) {}

Bio::Bio(float micro_organic, float toxic)
    : micro_organic(micro_organic), toxic(toxic) {}


Influence::Influence()
    : magic(Magic()), energy(Energy()), physic(Physic()), bio(Bio()), soul(0), psycho(0), conceptual(0) {}

Influence::Influence(Magic magic, Energy energy, Physic physic, Bio bio, float soul, float psycho, float conceptual)
    : magic(magic), energy(energy), physic(physic), bio(bio), soul(soul), psycho(psycho), conceptual(conceptual) {}