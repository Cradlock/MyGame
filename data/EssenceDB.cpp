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

        
        Vector2f cameraOffset(self.spr.getPosition().x - WIDTH / 2, self.spr.getPosition().y - HEIGHT / 2);

        self.light->circle.setPosition(self.spr.getPosition() -   cameraOffset);
        self.light->circle.setFillColor(Color::White);
        
        window.draw(self.spr);
    };
}



