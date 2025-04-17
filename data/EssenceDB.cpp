#include "EssenceDB.h" 


unordered_map<int,function<void(Essence& self)>> EssencesLambdaDB = {};



void init_essence_lambdas(){
   
    EssencesLambdaDB[1] = [](Essence& self){
        self.flag = false;
        if (Keyboard::isKeyPressed(Keyboard::W)) {
                self.counter1 = 0;
                self.flag = true;
                self.spr.move(0,-self.speed.value);
            }
    
        if (Keyboard::isKeyPressed(Keyboard::S)) {
                self.counter1 = 1;
                self.flag = true;
                self.spr.move(0,self.speed.value);
                
            }    
        if (Keyboard::isKeyPressed(Keyboard::A)) {
               self.counter1 = 2;
                self.flag = true;
               self.spr.move(-self.speed.value,0);
            }
            
        if (Keyboard::isKeyPressed(Keyboard::D)) {
               self.counter1 = 3;
                self.flag = true;
               self.spr.move(self.speed.value,0);
        }
        
        if(self.flag){
            if(self.c1.getElapsedTime().asSeconds() > self.speed.time){
              if(self.counter1 == 2){
                self.spr.setScale(-1.0 , 1);
                setSize(self.spr,-self.width,self.height);
              }else{
                setSize(self.spr,self.width,self.height);
            }
            
            if(self.counter >= self.images_numbers.size() - 1){
                  self.counter = 0;
            }
            self.counter++;
            self.c1.restart();
            }
        }else{
            self.counter = 0;
        }

        

        self.light->circle.setPosition(self.spr.getPosition());
        self.light->circle.setRadius(self.sight);
        self.light->circle.setOrigin(self.light->circle.getRadius(), self.light->circle.getRadius());
        self.light->circle.setScale(1.f, 1.f);
        self.light->circle.setFillColor(Color(255,255,255,100));
        
 
    };
}



