#ifndef WINDOWS_H
#define WINDOWS_H


#include "../resourses.h"




void OnCursor(Text& b,bool& t,Vector2i mousePos);

void OnCursor(Text& b,bool& t,Vector2i mousePos);

void SetWhite(Text& t,bool& b);

class MainMenu{
public:
    bool isInPlay = false;
    bool isInSaves = false;
    bool isInSetting = false;
    bool isInExit = false;
    Font pixel_l_font;

    Sprite background_sprite;
    Texture background_texture;
    Text title;
    Text button_play;
    Text button_saves;
    Text button_settings;
    Text button_exit;

    MainMenu(int randomNumber);
    

    int update(Vector2i mousePos);
    
    int updateSettings(Vector2i mousePos);

    int updateSaves(Vector2i mousePos,string& path_to_save,bool& isGame);

    void BackgroundRender();
};










#endif