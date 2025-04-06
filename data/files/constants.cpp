#include "constants.h"



int WIDTH = VideoMode::getDesktopMode().width ;
int HEIGHT = VideoMode::getDesktopMode().height;
float NORMAL_ZOOM =  WIDTH / HEIGHT - 0.65f;  
float NORMAL_SPEED = NORMAL_ZOOM / 4;
float standart_size = 25.f;

int experience = 0;
unsigned int counterID =  0;
float DAY_LENGTH = 24;
float DELTA_TIME = 255 / DAY_LENGTH;
const float timeSpeed = 1;

RenderWindow window(VideoMode(WIDTH,HEIGHT),Title);


void setSize(Sprite& s,float w,float h){
    float originalWidth = s.getLocalBounds().width;
    float originalHeight = s.getLocalBounds().height;
        
    float scaleX = w / originalWidth;
    float scaleY = h / originalHeight;
           
    s.setScale(scaleX,scaleY);
}


static const auto renderLambda = [window=&window](auto&&... args) {
    (window->draw(std::forward<decltype(args)>(args)), ...);
};





