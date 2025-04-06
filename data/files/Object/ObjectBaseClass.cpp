#include "ObjectBaseClass.h"




//Конструкторы - start


vector<Light> Global_light_list = {
    Light(20,Color(255,255,255,50)),
    Light(30,Color(0,255,0,100)),
 };


PartWorld::PartWorld(){}

PartWorld::PartWorld(int x,int y){
    this->spr.setPosition(x,y);
}

Object::Object(){};


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
      this->light = Light{};
};

Object Object::WithLightObject(int l,string t,float e,vector<int> images,float w,float h,int IdTouch,int light_num){
    Object obj;
    
    obj.position_level = l;
    obj.endurance = e;
    obj.images_numbers = images;
    obj.title = t;


    obj.width = w;
    obj.height = h;

    obj.IdFunc = IdTouch;

    FloatRect rect{1,1,1,1};
    obj.hitbox = rect;
    obj.light = Global_light_list[light_num];
    return obj;
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
      this->light = Light{};


};


Object::Object(int l,string t,float e,vector<int> images,float w,float h,vector<Effect> efs,vector<Item> its,int IdTouch){

      this->position_level = l;
      this->endurance = e;
      this->images_numbers = images;
      this->title = t;

      this->width = w;
      this->height = h; 
      this->IdFunc = IdTouch;
      this->light = Light{};



};
//Конструкторы - end
void Object::Func(Essence& esse,RenderWindow& window){};




vector<Object> Global_Objects_list = {

    Object{-1,"Void", 100000.086, { 0 } , 1 , 1 , 0},
//                                           HitBox - x   y    w    h  
    Object{1,"Tree ",25.5,{ 1 }, 40.f,60.f, FloatRect{2, 0.7, 0.2, 0.2} ,1}, //1
    
    Object{0,"Grass ",1.5,{ 2 }, 25.f , 10.f,1},  //2
    
    Object::WithLightObject(0,"Brown mushroom",1.5,{ 3 },  5.f , 6.f , 1 , 1), //3
     
    Object{0,"Brown mushrooms",3.0,{ 4 }, 5.f , 8.f ,1}, //4
};






