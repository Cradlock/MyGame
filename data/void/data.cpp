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
   

const int segments = 64;      // количество треугольников
const float radiusX = 0.3f;   // половина ширины экрана
const float radiusY = 0.5f;   // половина высоты экрана

Artifex::Vertex center = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}}; // белый центр
this->artifex.targets.push_back(center);

// вершины по эллипсу
for(int i = 0; i <= segments; i++) { // <= segments чтобы замкнуть круг
    float angle = i * 2.0f * 3.1415926f / segments;
    float x = cos(angle) * radiusX;
    float y = sin(angle) * radiusY;

    // случайный цвет для градиента
    float r = static_cast<float>(rand()) / RAND_MAX;
    float g = static_cast<float>(rand()) / RAND_MAX;
    float b = static_cast<float>(rand()) / RAND_MAX;

    this->artifex.targets.push_back({{x, y, 0.0f}, {r, g, b}});
}

// формируем индексы (TRIANGLE_FAN)
for(int i = 1; i <= segments; i++) {
    this->artifex.indices.push_back(0);       // центр
    this->artifex.indices.push_back(i);       // текущая вершина
    this->artifex.indices.push_back(i + 1);   // следующая вершина
}
   
   this->artifex.createStagingBuffer();
   this->artifex.createVertexBuffer();
   this->artifex.createIndexBuffer();
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