#include "linker.h"


unordered_map<int,Object> localObjects;
vector<shared_ptr<Light>> localLight;

vector<int> objects_top;
vector<int> objects_bottom;




unordered_map<string,Texture> textures;
vector<PartWorld> partes;

vector<Item> items;

vector<Essence> essences;

vector<Projectile> projectiles;


void init_db(){

// Essences
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
        cout << self.light->circle.getPosition().x << '-' << self.light->circle.getPosition().y << endl;
        window.draw(self.spr);
    };






//Objects 

ObjectsDB[1] = [](Object& self,Essence& esse){
    if(self.spr.getGlobalBounds().intersects(esse.spr.getGlobalBounds())){

        if(self.hitbox.top < esse.spr.getPosition().y){
           auto it = find_if(objects_top.begin(),objects_top.end(),[&](int num){
               return self.id == num;
           });
           
           if(it != objects_top.end()){
               objects_bottom.push_back(*it);
               objects_top.erase(it);
           }
             
        }else{
           auto it = find_if(objects_bottom.begin(),objects_bottom.end(),[&](int num){
               return self.id == num;
           });
           
           if(it != objects_bottom.end()){
               objects_top.push_back(*it);
               objects_bottom.erase(it);

           }

           
        }


        
    }
    Vector2f cameraOffset(self.spr.getPosition().x - WIDTH / 2, self.spr.getPosition().y - HEIGHT / 2);

    self.light->circle.setPosition(960,510);
    
    self.light->circle.setFillColor(Color::White);

};





ObjectsDB[2] = [](Object& self,Essence& esse){
   
    
};










//Items

};