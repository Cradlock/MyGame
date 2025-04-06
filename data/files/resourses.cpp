#include "resourses.h"


Light::Light(float r,  Color col) {
    CircleShape circ;
    circle = circ;
    radius = r;
    this->color = col;
    circle.setFillColor(color);
    circle.setRadius(radius);
};

Light::Light(){
    this->radius = 0;
};



namespace fontes {
    string pixel_font = "fonts/pixel.ttf";
}

namespace path_to_img {
    string bg1 = "images/System/Backgrounds/bg1.jpeg";  
    string bg2 = "images/System/Backgrounds/bg2.jpeg";  
    string bg3 = "images/System/Backgrounds/bg3.jpeg";  
   
 
    unordered_map<int,string> Player_images = {
       {1 , "images/Essence/Player/GG.png"},
       {2 , "images/Essence/Player/GG_right1.png"},
       {3 , "images/Essence/Player/GG_right2.png"},
       {4 , "images/Essence/Player/GG_right3.png"},
       {5 , "images/Essence/Player/GG_right4.png"}
    };


   unordered_map<int,string> Essence_images = {};

    unordered_map<int,string> Objects = {
        {0,"Void"},
        {1,"images/Objects/Block/Average/tree001.png"},
        {2,"images/Objects/Block/Bottom/grass.png"},
        {3,"images/Objects/Block/Bottom/mushroom001.png"},
        {4,"images/Objects/Block/Bottom/mushrooms001.png"},
    };
   
   namespace PartWorld{
    vector<string> blockes = {"Void",
        "images/Objects/PartWorld/ground.jpg",
        "images/Objects/PartWorld/gravel.png",
        "images/Objects/PartWorld/grass.jpg",
        "images/Objects/PartWorld/stone.jpg",
        "images/Objects/PartWorld/cobblestone.jpg",
        "images/Objects/PartWorld/stoneTile.jpg",
        "images/Objects/PartWorld/Myceli.jpg",
        "images/Objects/PartWorld/OverGrownGrass.jpg",
        "images/Objects/PartWorld/OverGrownMyceli.jpg",
        "images/Objects/PartWorld/ShalloWater.jpg",
        "images/Objects/PartWorld/MediumWater.png",
        "images/Objects/PartWorld/DeepWater.jpg",
        "images/Objects/PartWorld/Dirt.jpg",
        "images/Objects/PartWorld/swamp.jpg",
        "images/Objects/PartWorld/lava.jpg",
        "images/Objects/PartWorld/sand.jpg",
        "images/Objects/PartWorld/magma.jpg",
        "images/Objects/PartWorld/darkWater.png",
    };

   }
}





    



bool OnCursor(Text& b,Vector2f mousePos){
    if(b.getGlobalBounds().contains(mousePos)){
        return true;
    }else{
        return false;
    }
}

bool OnClick(Text& b,Vector2f mousePos){
    if(b.getGlobalBounds().contains(mousePos)){
           if(Mouse::isButtonPressed(Mouse::Left))
           return true;
           else{
            return false;
           }
    }
    return false;
}

void SetWhite(Text& t){
        t.setFillColor(Color::White);
}

void SetBlack(Text& t){
    t.setFillColor(Color::Black);
}

MainMenu::MainMenu(int randomNumber){
    Font pxl;
    pxl.loadFromFile(fontes::pixel_font);
    this->pixel_l_font = pxl;

    switch (randomNumber)
    {
    case 1:
       if(!background_texture.loadFromFile(path_to_img::bg1)){
            cerr << "1" << endl;
        }
        break;
    case 2:
        if(!background_texture.loadFromFile(path_to_img::bg2)){
            cerr << "2" << endl;
        }
        
        break;
    case 3:
        if(!background_texture.loadFromFile(path_to_img::bg3)){
            cerr << "3" << endl;
        }
        break;
    default:
        break;
    }
  

    background_sprite.setTexture(background_texture);

    float scaleX = float(WIDTH) / background_texture.getSize().x;
    float scaleY = float(HEIGHT) / background_texture.getSize().y;
    
    background_sprite.setPosition(Vector2f(0,0));
    background_sprite.setScale(scaleX,scaleY);
    
    Text titl(Title,pixel_l_font,160);
    this->title = titl;
    title.setFillColor(Color(20 * randomNumber,20 * randomNumber,20 * randomNumber));
    title.setScale(2,1);
    title.setPosition( (WIDTH - title.getLocalBounds().width * title.getScale().x) / 2,HEIGHT / 10 );


    Text button_pla("Play",pixel_l_font,100);
    this->button_play = button_pla;
    button_play.setFillColor(Color(0,0,0));
    Text button_save("Load world",pixel_l_font,100);
    this->button_saves = button_save;
    button_saves.setFillColor(Color(0,0,0));
    Text button_setting("Settings",pixel_l_font,100);
    this->button_settings = button_setting;
    button_settings.setFillColor(Color(0,0,0));
    Text button_exi("Exit",pixel_l_font,100);
    this->button_exit = button_exi;
    button_exit.setFillColor(Color(0,0,0));

    
    float coordY =  HEIGHT / 6 + button_play.getGlobalBounds().height;
    button_play.setPosition((WIDTH - button_play.getLocalBounds().width) / 2,coordY);
    coordY += button_play.getLocalBounds().height * 1.5;
    button_saves.setPosition((WIDTH - button_saves.getLocalBounds().width) / 2,coordY);
    coordY += button_play.getLocalBounds().height * 1.5;
    button_settings.setPosition((WIDTH - button_settings.getLocalBounds().width) / 2,coordY);
    coordY += button_play.getLocalBounds().height * 1.5;
    button_exit.setPosition((WIDTH - button_exit.getLocalBounds().width) / 2,coordY);

}

void MainMenu::BackgroundRender(){
    window.draw(this->background_sprite);
}

int MainMenu::update(Vector2f mousePos){
    window.draw(title);window.draw(button_play);window.draw(button_saves);window.draw(button_settings); window.draw(button_exit);
        
    if(OnCursor(button_play,mousePos)){
        SetWhite(button_play);
    }else{
        SetBlack(button_play);
    }

    if(OnCursor(button_saves,mousePos)){
        SetWhite(button_saves);
    }else{
        SetBlack(button_saves);
    }

    if(OnCursor(button_settings,mousePos)){
        SetWhite(button_settings);
    }else{
        SetBlack(button_settings);
    }

    if(OnCursor(button_exit,mousePos)){
        SetWhite(button_exit);
    }else{
        SetBlack(button_exit);
    }
        
        

    if(OnClick(button_play,mousePos)){
        return 1;
    }
    if(OnClick(button_saves,mousePos)){
        sleep(seconds(0.5));
        return 2;
    }
    if(OnClick(button_settings,mousePos)){
        return 3;
    }
    if(OnClick(button_exit,mousePos)){
        return 4;
    }

    return 0;
}

int MainMenu::updateSettings(Vector2f mousePos){
    Text inMainMenu{" <-- ",this->pixel_l_font,100};
    Text titlePage("Settings",pixel_l_font,75);
    titlePage.setPosition( (WIDTH - titlePage.getLocalBounds().width * titlePage.getScale().x) / 2, 0);
    
    window.draw(inMainMenu);
    window.draw(titlePage);
    
    
   
    if(OnClick(inMainMenu,mousePos)){
        return 0;
    }
    return 3;

}

int MainMenu::updateSaves(Vector2f mousePos,string& path_to_save,bool& isGame){
    Text inMainMenu{" <-- ",this->pixel_l_font,100};
    Text titlePage("All saves",pixel_l_font,75);
    titlePage.setPosition( (WIDTH - titlePage.getLocalBounds().width * titlePage.getScale().x) / 2, 0);
    
   
    window.draw(inMainMenu);
    window.draw(titlePage);
    
    
   
    if(OnClick(inMainMenu,mousePos)){
        return 0;
    }
    if(inMainMenu.getGlobalBounds().contains(mousePos)){
        inMainMenu.setFillColor(Color::Red);
    }
    return 2;
}



