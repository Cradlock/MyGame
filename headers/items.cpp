#include "items.h"


//Potions
Potion::Potion(float size,float weight,string& path,float w,float h){
        this->size = size;
        this->masse = weight;
        if(!texture.loadFromFile(path)){
            cerr << "Error in Potion class" << endl;
        }
        this->sprite.setTexture(texture);
        this->sprite_size = Vector2f(w,h);
}

void Potion::func(RenderWindow& window,Vector2i& mousePos,vector<unique_ptr<Essence>>& life_objects,vector<unique_ptr<Boundary>>& unlife_objects,Player& player)
{
      for(auto& x : this->effects){
          player.effects.push_back(move(x));
      }
      this->effects.clear();
}

//End





