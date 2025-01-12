#include "ObjectBaseClass.h"


PartWorld::PartWorld(){}

PartWorld::PartWorld(int x,int y){
    this->spr.setPosition(x,y);
}



Object::Object(int l,string t,float e,vector<int> images,float w,float h){
      this->position_level = l;
      this->endurance = e;
      this->images_numbers = images;
      this->title = t;

      this->IsExactSize = true;

      this->width = w;
      this->height = h;

};

Object::Object(int l,string t,float e,vector<int> images,float ws,float we,float hs,float he){
      this->position_level = l;
      this->endurance = e;
      this->images_numbers = images;
      this->title = t;
      
      this->IsExactSize = false;
     
      this->wmin = ws;
      this->wmax = we;
      
      this->hmin = hs;
      this->hmax = he;

};



vector<Object> Global_Objects_list = {
    Object{-1,"Void", 100000.086, { 0 } , 1 , 1},
    Object{1,"Tree ",25.5,{ 1 }, 30.f,40.f,  60.f,80.f},
    Object{0,"Grass ",1.5,{ 2 },25.f,10.f},
    Object{0,"Brown mushroom",1.5,{ 3 }, 5.f,7.f, 5.f,6.f},
    Object{0,"Brown mushrooms",3.0,{ 4 }, 5.f,8.f, 5.f,8.f},
};