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

class Light : public Base{
    public:
      CircleShape circle;
     
    Light(float rad,Color color);

    Light();
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

class MainMenu{
    public:
        Font pixel_l_font;
    
        Sprite background_sprite;
        Texture background_texture;
        Text title;
        Text button_play;
        Text button_saves;
        Text button_settings;
        Text button_exit;
    
        MainMenu(int randomNumber);
        
    
        int update(Vector2f mousePos);
        
        int updateSettings(Vector2f mousePos);
    
        int updateSaves(Vector2f mousePos,string& path_to_save,bool& isGame);
    
        void BackgroundRender();
    };
    
    

extern vector<Light> Global_light_list;

class PathManager{
    
};

#endif