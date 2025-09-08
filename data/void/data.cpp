#include "./data.h"
#include "./pack.h"




GameManager::GameManager(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) 
: window(hInstance,hPrevInstance,lpCmdLine,nShowCmd, Resources::Title.c_str() )
,artifex(window)
{
   this->lua.open_libraries(sol::lib::base);
   this->running = true;
   this->window.showWindow();
}


void GameManager::start_init(){
   this->memory_manager.init();
   this->settings_manager.init();  
   this->mod_manager.init();

}


void GameManager::proccessEvent(){
   Keyboard::update();
   this->window.updateWindow();
   this->window.msgLoop();

   if(WindowEvent::IsWindowEvent(EVENT_CLOSE) ){
      this->running = false;
   }
}

void GameManager::resets(){
   WindowEvent::reset();
}



void GameManager::splashScreen(){
  
}

void GameManager::game(){
   

   this->artifex.targets.push_back({{ 0.0f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f }});
   this->artifex.targets.push_back({{ 0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }});
   this->artifex.targets.push_back({{ -0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }});

   this->artifex.createStagingBuffer();
   this->artifex.createVertexBuffer();
   this->artifex.createUniformBuffer();
   
   while(running){
      this->proccessEvent();
      this->artifex.update();
      
      this->resets();
   }


   this->end_game();
}


void GameManager::end_game(){
   this->artifex.destroy();
}