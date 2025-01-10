#ifndef WORLD_H
#define WORLD_H

#include "../resourses.h"
#include "../Essence/EssenceBaseClass.h"
#include "../Object/ObjectBaseClass.h"
#include "../Item/ItemBaseClass.h"


class World{
public:
   unsigned long long int width,height;
   String title;
   matrixMap map;
   matrixMap mapObj;
   vector<PartWorld> world_objects;
   unordered_map<string , function<void()> > ConditionsWorld;   

   World();

   World(String title,matrixMap map,matrixMap objects);

   void generate(unordered_map<string,Texture>& txs);

   void render(RenderWindow& window);
   
   void useConditions();

   void serializers();
   
   void deserilailzers();
   
};





#endif