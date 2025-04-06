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
   vector<matrixMap> map;
   vector<PartWorld> world_objects;
   unordered_map<string , function<void()> > ConditionsWorld;   
   vector<Essence> essences;
   Essence player;

   float red;
   float green;
   float blue;
   float opacity;

   bool PosL = true;

   float timeOfDay;
   float elapsedTime;
   
   World();

   World(String title,int numMap,vector<Essence> essnc);

   void generate(unordered_map<string,Texture>& txs);

   void render(RenderWindow& window);
   
   void useConditions();

   void serializers();
   
   void deserilailzers();
   
};





#endif