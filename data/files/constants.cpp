#include "constants.h"



int WIDTH = VideoMode::getDesktopMode().width ;
int HEIGHT = VideoMode::getDesktopMode().height;
float NORMAL_ZOOM =  WIDTH / HEIGHT - 0.65f;  
float NORMAL_SPEED = NORMAL_ZOOM / 4;
float standart_size = 25.f;

int experience = 0;
unsigned int counterId = 0;

RenderWindow window(VideoMode(WIDTH,HEIGHT),Title);


void setSize(Sprite& s,float w,float h){
    float originalWidth = s.getLocalBounds().width;
    float originalHeight = s.getLocalBounds().height;
        
    float scaleX = w / originalWidth;
    float scaleY = h / originalHeight;
           
    s.setScale(scaleX,scaleY);
}


