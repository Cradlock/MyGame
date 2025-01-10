#ifndef WEAPONS_H
#define WEAPONS_H


#include "baseClass.h"
#include "resourses.h"


class KatanSword : public Item{
private:
   float damage;
   float speed_attack = 2;
   float defend;
   vector<string> slash_pathes;
   Texture slash_texture;
   Sprite slash_sprite;
   Clock clock1;

public:
   KatanSword(float masse, float size, float damage,float defend,string& path, vector<string>& images_path,float w,float h,Vector2f pos);
   

   void func(RenderWindow& window,Vector2i& mousePos,vector<unique_ptr<Essence>>& life_objects,vector<unique_ptr<Boundary>>& unlife_objects,Player& player);

};

extern unique_ptr<KatanSword> katanaDefault; 



#endif