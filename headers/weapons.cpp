#include "weapons.h"


KatanSword::KatanSword(float masse, float size, float damage,float defend,string& path, vector<string>& images_path,float w,float h,Vector2f pos)
{
         this->sprite_size = Vector2f(w,h);
         this->masse = masse;
         this->size = size;
         this->defend = defend;
         this->damage = damage;
         this->slash_pathes = images_path;
         if(!texture.loadFromFile(path)){
             cerr << "in katana img" << endl;
         }
         sprite.setTexture(texture);
         this->set_position(pos);
}

void KatanSword::func(RenderWindow& window,Vector2i& mousePos,vector<unique_ptr<Essence>>& life_objects,vector<unique_ptr<Boundary>>& unlife_objects,Player& player)
{
          if(anim_count > 3) anim_count = 0;
          string path = this->slash_pathes[anim_count];
          if(!slash_texture.loadFromFile(path)){
             cerr << "error animation attack" << endl;
          }
          slash_sprite.setTexture(slash_texture);
          if(!player.is_left) {
                slash_sprite.setPosition(player.getPosition().x + 50, player.getPosition().y);
                slash_sprite.setScale(-1.0f,1.0f);
          } else {
              slash_sprite.setScale(1.0f,1.0f);
              slash_sprite.setPosition(player.getPosition().x - 25, player.getPosition().y);
             }

          if(clock1.getElapsedTime().asSeconds() > 0.1){
               anim_count++;

               clock1.restart();
          }


          window.draw(slash_sprite);


}

unique_ptr<KatanSword> katanaDefault = make_unique<KatanSword>(20.0,100.0,25.0,100,path_to_img::katana_path,path_to_img::katana_slash_pathes,55.0,10.0,Vector2f(267.0,200.0));






