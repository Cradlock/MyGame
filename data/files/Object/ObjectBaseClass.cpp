#include "ObjectBaseClass.h"


PartWorld::PartWorld(){}

PartWorld::PartWorld(int x,int y){
    this->spr.setPosition(x,y);
}

Object::Object(int l,string t,float e,vector<int> images,float w,float h,int IdTouch){
      this->position_level = l;
      this->endurance = e;
      this->images_numbers = images;
      this->title = t;


      this->width = w;
      this->height = h;

      this->IdFunc = IdTouch;

      FloatRect rect{1,1,1,1};
      this->hitbox = rect;
};


Object::Object(int l,string t,float e,vector<int> images,float w,float h,FloatRect rect ,int IdTouch){
      this->position_level = l;
      this->endurance = e;
      this->images_numbers = images;
      this->title = t;

      this->width = w;
      this->height = h;
      this->IdFunc = IdTouch;

     
      rect.width *= w;
      rect.height *= h;

      this->hitbox = rect;

};



Object::Object(int l,string t,float e,vector<int> images,float w,float h,vector<Effect> efs,vector<Item> its,int IdTouch){

      this->position_level = l;
      this->endurance = e;
      this->images_numbers = images;
      this->title = t;

      this->width = w;
      this->height = h; 
      this->IdFunc = IdTouch;

};

void Object::Func(Essence& esse,vector<Object>& Objects_top,vector<Object>& Objects_bottom,vector<Projectile>& projectiles,RenderWindow& window){
      if(IdFunc != 0){
         Objects_functions_DB[IdFunc](this,esse,Objects_top,Objects_bottom,projectiles,window);
      }
};


unordered_map<int,function<void(Object*,Essence&,vector<Object>&,vector<Object>&,vector<Projectile>&,RenderWindow&)>> 
Objects_functions_DB = {
   {1, [&](Object* self, Essence& esse,vector<Object>& Objects_top,vector<Object>& Objects_bottom,vector<Projectile>& projectiles,RenderWindow& window){
        if(self->spr.getGlobalBounds().intersects(esse.spr.getGlobalBounds())){
            if(self->hitbox.top < esse.spr.getPosition().y){
                  auto it = find_if(Objects_top.begin(),Objects_top.end(), [&](const Object& obj){
                        return &obj == self;
                  });
                  if(it != Objects_top.end()){
                        Objects_bottom.push_back(*it);
                        self = &Objects_bottom.back();
                        Objects_top.erase(it);  
                  }
                 
            }else{
                  auto it = find_if(Objects_bottom.begin(),Objects_bottom.end(), [&](const Object& obj){
                        return &obj == self;
                  });
                  
                  if(it != Objects_bottom.end()){
                        Objects_top.push_back(*it);
                        self = &Objects_top.back();
                        Objects_bottom.erase(it);  
                  }

              
            }
        }
   }}


}
;


vector<Object> Global_Objects_list = {
    Object{-1,"Void", 100000.086, { 0 } , 1 , 1 , 0},
//                                           HitBox - x   y    w    h  
    Object{1,"Tree ",25.5,{ 1 }, 40.f,60.f, FloatRect{2, 0.7, 0.2, 0.3} ,1},
    
    Object{0,"Grass ",1.5,{ 2 }, 25.f , 10.f,0},
    
    Object{0,"Brown mushroom",1.5,{ 3 }, 5.f , 6.f ,0},
    
    Object{0,"Brown mushrooms",3.0,{ 4 }, 5.f , 8.f ,0},
};