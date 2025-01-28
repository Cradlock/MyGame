#ifndef RESOURSES_H
#define RESOURSES_H


#include "Abstract/Influence.h"
#include "constants.h"

using namespace std;



class Base{
public:
    FloatRect hitbox;
    float width,height;
    Vector2f sprite_size;
    Clock c1,c2,c3,c4;
    int counter = 0;
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    int counter4 = 0;
    int id;
    bool flag = false;
    bool flag1 = false;

};

namespace path_to_audio{

};

namespace fontes {
    extern string pixel_font;
};

namespace path_to_img {
   extern string bg1;
   extern string bg2;
   extern string bg3;

   extern unordered_map<int,string> Player_images;

   extern unordered_map<int,string> Essence_images;

   extern unordered_map<int,string> Objects;

   namespace PartWorld{
      extern vector<string> blockes;
   }
};




#endif