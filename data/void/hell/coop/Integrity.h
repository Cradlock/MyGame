#pragma once 

#include "Influence.h"
#include "../../base.h"
#include "./Properties.h"



class Entity;


struct PhysicPart{
   float endurance = 1;
   
   float refractory = 0;
   float conducivity = 0;
   float WaveAbsorption = 0;
   float RadAbsorption = 0;
   float inertia = 0;

   float resCut = 0,resPrick = 0,resBlunt = 0;

   float masse = 1;
   float density = 1;
   
   PhysicPart();
   // ...
};

struct BioPart{
   mms Q = mms{10,1,5};
   float bioMaterial = 1;
   float immunity = 1;
   float regenerate = 0;
   float resToxin = 0;
   PhysicPart body;
   
   BioPart();
   // ...
   
};

struct ManaPart{
   mms amount = mms(1,1,1);
   float absorption;
   float power;
   variant<BioPart,PhysicPart> body;
   
   ManaPart();
   // ...
};

using type_integrity = variant<BioPart,ManaPart,PhysicPart>;

class Integrity{
public:
  
   Integrity(float bio,float physic,float mana);

private:
   
// Needs
   void need(Entity& self);

// Influences
   void receive(Entity& self,Influence& obj);
   
// Value
   unordered_map<type_integrity,float> value;

   inline float integrity(){ 
      float total = 0.0f;
      for(const auto& [key,value] : this->value){
         total += value;
      }
      return total;
   };

};



