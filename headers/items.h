#ifndef ITEMS_H
#define ITEMS_H


#include "baseClass.h"
#include "resourses.h"



//Potions
class Potion : public Item{
public:
   vector<unique_ptr<Effect>> effects;
   
   Potion(float size,float weight,string& path,float w,float h);
  
   void func(RenderWindow& window,Vector2i& mousePos,vector<unique_ptr<Essence>>& life_objects,vector<unique_ptr<Boundary>>& unlife_objects,Player& player);
  
};



//End



//Meat




//End




#endif