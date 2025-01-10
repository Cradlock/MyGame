
#include "windows.h"



void OnCursor(Text& b,bool& t,Vector2i mousePos){
    if(b.getGlobalBounds().contains(mousePos.x, mousePos.y)){
        t = true;
    }else{
        t = false;
    }
}

bool OnClick(Text& b,Vector2i mousePos){
    if(b.getGlobalBounds().contains(mousePos.x, mousePos.y)){
           if(Mouse::isButtonPressed(Mouse::Left))
           return true;
           else{
            return false;
           }
    }
    return false;
}

void SetWhite(Text& t,bool& b){
    if(b){
        t.setFillColor(Color::White);
        
    }else{
        t.setFillColor(Color(0,0,0));

    }
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
    
    this->isInPlay = false;
    this->isInSaves = false;
    this->isInSetting = false;
    this->isInExit = false;
}

void MainMenu::BackgroundRender(){
    renderObject(this->background_sprite);
}

int MainMenu::update(Vector2i mousePos){
    renderObject(title,button_play,button_saves,button_settings,button_exit);
        
    OnCursor(button_play,isInPlay,mousePos);
    OnCursor(button_saves,isInSaves,mousePos);
    OnCursor(button_settings,isInSetting,mousePos);
    OnCursor(button_exit,isInExit,mousePos);
        
    SetWhite(button_play,isInPlay);
    SetWhite(button_saves,isInSaves);
    SetWhite(button_settings,isInSetting);
    SetWhite(button_exit,isInExit);
        

    if(OnClick(button_play,mousePos)){
        return 1;
    }
    if(OnClick(button_saves,mousePos)){
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

int MainMenu::updateSettings(Vector2i mousePos){
    Text inMainMenu{" <-- ",this->pixel_l_font,100};
    Text titlePage("Settings",pixel_l_font,75);
    titlePage.setPosition( (WIDTH - titlePage.getLocalBounds().width * titlePage.getScale().x) / 2, 0);
    
    renderObject(inMainMenu,titlePage);
    
   
    if(OnClick(inMainMenu,mousePos)){
        return 0;
    }
    return 3;

}


int MainMenu::updateSaves(Vector2i mousePos,string& path_to_save,bool& isGame){
    Text inMainMenu{" <-- ",this->pixel_l_font,100};
    Text titlePage("All saves",pixel_l_font,75);
    titlePage.setPosition( (WIDTH - titlePage.getLocalBounds().width * titlePage.getScale().x) / 2, 0);
    
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFileA("files\\System\\saves\\*",&findFileData);
    
    
    int y = titlePage.getLocalBounds().height * 2;
    int c = 0;
    while (FindNextFile(hFind,&findFileData) != 0)
    {   
        if (findFileData.cFileName[0] != '.') {
        Text obj(findFileData.cFileName  ,this->pixel_l_font,60);
        obj.setFillColor(Color(100,100,100));
        obj.setPosition( WIDTH  / 5 , y);    

        if(obj.getGlobalBounds().contains(mousePos.x,mousePos.y)){
             obj.setFillColor(Color(250,250,250));     
        }
        if(OnClick(obj,mousePos)){
            isGame = true;
            path_to_save = findFileData.cFileName;
            return 2;
        }
        renderObject(obj);
        y += obj.getGlobalBounds().height * 2;
        c++;
        }
    }
    FindClose(hFind);
    if(c == 0){
        Text obj("Not saves",this->pixel_l_font,150);
        obj.setFillColor(Color(20,20,20));
        obj.setPosition((WIDTH - obj.getLocalBounds().width * obj.getScale().x) / 2, titlePage.getGlobalBounds().height * 2);
        renderObject(obj);
    }

    renderObject(inMainMenu,titlePage);
    
   
    if(OnClick(inMainMenu,mousePos)){
        return 0;
    }
    return 2;
}