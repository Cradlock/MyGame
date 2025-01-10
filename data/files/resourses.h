#ifndef RESOURSES_H
#define RESOURSES_H


#include "constants.h"
#include "Abstract/Influence.h"

using namespace std;



class Base{
public:
    float width,height;
    Vector2f sprite_size;
    Clock c1,c2,c3,c4;
    int counter = 0;
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

   namespace Weapons{
        
   }

   namespace Items{

   }

   namespace Equipment{

   }

   namespace Essence{

   }

   namespace Spells{

   }

   extern unordered_map<int,string> Objects;

   namespace PartWorld{
      extern vector<string> blockes;
   }
};




#endif