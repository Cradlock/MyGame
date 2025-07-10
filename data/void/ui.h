#pragma once 

#include "./pack.h"
#include "./base.h"


enum class Direction {Horisontal,Vertical};
enum class Justify {Start,Center,End,SpaceAround};

class UI_element {

public:

~UI_element() = default;
protected:
virtual void setPosition(float x,float y) = 0;
virtual void update() = 0;


};



class AnimatedWindow : public UI_element{
private:

   
    int idx;
    
    float frameDelay = 0.1f;
    
public:
    inline void setFrameDelay(float s){
          this->frameDelay = s;
    };

    inline void setPosition(float x,float y) override {
       
    };

 
    AnimatedWindow();




    inline void update() override {
      
    }
    


};




class Carcass{
private:
// Info 
  


// Childs
  

// childControl
    Direction direction;
    Justify alignItems;    
    Justify justifyContent;    


public:
    

    Carcass();

    inline bool add(unique_ptr<UI_element> elem,string className){
        return true;
    }

    inline void setDirection(Direction tp){
        this->direction = tp;
    }

    inline void setAlignItems(Justify justify){ this->alignItems = justify; }

    inline void setJustifyContent(Justify justify) { this->justifyContent = justify; }

    inline void remove(string className){}

  
    inline void update(){
        
    }

    inline void layout(){
        // установка всех координат для детей
        
        switch(this->direction){
           case Direction::Horisontal:
           {
           
           break;
           }
           case Direction::Vertical:
           {
           
            break;
           } 
           default:break;
        }
       

    }
};




class Button : public UI_element{
private:
   
    function<void()> onTap;
    float hoverDuration;
    function<void()> onHover;

public:
    
  
};

