#include "ObjectsDB.h"


unordered_map<int,function<void(Object& self,Essence& esse)>> ObjectsDB;



void init_objects_lambdas(){
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
    
}