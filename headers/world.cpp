#include "world.h"
#include "resourses.h"

#include <iostream>

using namespace std;

World::World(const string& FilePath,vector<string> c){
         if(!this->texture.loadFromFile(FilePath)){
             cerr << "Filed in bg class" << endl;

         }
         sprite.setTexture(this->texture);
         sprite.setScale(5.5,5.5);
         this->width = texture.getSize().x;
         this->height = texture.getSize().y;
         this->decorates_pathes = c;
     }

float World::getWidth() const {
         return this->width;
     }

float World::getHeight() const {
         return this->height;
     }

void World::draw(RenderWindow &window) {
         window.draw(this->sprite);

         for(auto& x : this->unlife_objects){
            x->draw(window);
         }

         for(auto& x : this->life_objects){
            x->draw(window);
         }

         for(auto& x : this->item_lists){
            x->draw_item(window);
         }
         Sprite spr;
         
         for(auto x : this->objects){
            spr.setTexture(this->decorates_list[x.objType]);
            spr.setPosition(x.x,x.y);
            window.draw(spr);
         }

}

void World::generate(int numObjects){
    srand(static_cast<unsigned int>(time(nullptr)));
    
    for(int i = 0 ; i < this->decorates_pathes.size() ; ++i){
         if(!this->decorates_list[i].loadFromFile(this->decorates_pathes[i])){
            cerr << this->decorates_pathes[i] + "Error" << endl;
         }
    }

    
    for(int i = 0;i <= numObjects;++i){
        decoration_point p;
        float x = static_cast<float>(rand() % this->width);
        float y = static_cast<float>(rand() % this->height);
        int ObjectType = rand() % this->decorates_pathes.size();
        
        p.objType = ObjectType;
        p.x = x;
        p.y = y;

        this->objects.push_back(p);
    }
    
    
};

RenderWindow window(VideoMode(WIDTH,HEIGHT),"Work");

 
World world(path_to_img::level_1_background,path_to_img::level_1_decorates);
