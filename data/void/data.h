#ifndef DATA_H
#define DATA_H


#include "./base.h"
#include "./settings.h"
#include "./ui.h"
#include "./mod.h"
#include "./memory.h"
#include "./hell/World/World.h"
#include "./abyss/include/Window.h"

class GameManager{
private:
    // Managers
    ModManager mod_manager;
    SettingManager settings_manager;
    MemoryManager memory_manager;
    // Variables
    PanarchonWindow window;
    Artifex artifex ;

    bool running;
   
    sol::state lua;
    Carcass skeleton;

  

    // methods
    
    void proccessEvent();

    void resets();

    void splashScreen();

    void end_game();

public:
    GameManager(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
    
    void start_init();

    void game();



};






#endif