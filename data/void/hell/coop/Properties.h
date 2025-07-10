#pragma once 

#include "../../base.h"


struct mms{
   fint min = 0,max = 0,value = 0;
   
   mms();
   mms(fint min,fint max,fint value);
};

class Properties{
private:
   mms stamina;
   mms mind;
   mms mana;
   mms speed;
   mms bioParts;
public:
   enum class PropTypes{Stamina,Mind,Mana,Speed,bioParts};
   
   Properties(unordered_map<PropTypes, mms> data);

};



