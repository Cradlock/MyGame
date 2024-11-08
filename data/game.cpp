#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <memory>


using namespace std;
using namespace sf;

ostream& operator<<(ostream& os, const sf::Vector2f& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

namespace fontes{
    string pixel_font = "fonts/pixel.ttf";

};
namespace path_to_img{
    string katana_path = "images/item/weapon/katana.png";
    string invBack_path = "images/backgrounds/inventory.png";
    vector<string> katana_slash_pathes = {
                "images/item/weapon/k_slash1.png",
                "images/item/weapon/k_slash2.png",
                "images/item/weapon/k_slash3.png",
                "images/item/weapon/k_slash4.png",
    };

    string stone_path = "images/objects/border.png";

    string player_left = "images/player_walk_left/1.png";
    string player_left1 = "images/player_walk_left/2.png";
    string player_left2 = "images/player_walk_left/3.png";
    string player_left3 = "images/player_walk_left/4.png";

    vector<string> player_lefts = {player_left3,player_left2,
                                 player_left1,player_left};

    string player_r  = "images/player_walk_right/1.png";
    string player_r1 = "images/player_walk_right/2.png";
    string player_r2 = "images/player_walk_right/3.png";
    string player_r3 = "images/player_walk_right/4.png";

    vector<string> player_rights = {player_r3,player_r2,
                                 player_r1,player_r};

    string world_bg1 = "images/backgrounds/background1.png";
};

static int WIDTH = (VideoMode::getDesktopMode().width * 70) / 100;
static int HEIGHT = (VideoMode::getDesktopMode().height * 80) / 100 ;
static float NORMAL_ZOOM =  WIDTH / HEIGHT - 0.65f; // 0.35
static float NORMAL_SPEED = NORMAL_ZOOM / 10;

// Classes

class Boundary{
private:
    Texture texture;
    string path;
    Sprite FSprite;
    Vector2f size;
    Vector2f position;
    float defend;


public:

    Boundary(const string& img_path, float width, float height, float x, float y)
    {

        size = Vector2f(width, height);
        position = Vector2f(x, y);
        this->path = img_path;

        if (!texture.loadFromFile(this->path)) {
            cerr << "Failed to load texture from path: " << this->path << endl;
            return;
        }
        FSprite.setTexture(texture);








        FSprite.setPosition(this->position);
    }


    void draw(RenderWindow &window) {

        FSprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);
        FSprite.setPosition(this->position);




        window.draw(FSprite);
    }


    FloatRect getBounds() const {
        return FSprite.getGlobalBounds();
    }


};

class Essence{
public:
    Vector2f position;
    float fps_walk;
    int walk_count = 0;

    Sprite sprite;
    Texture texture;

    vector<string> img_lists;

    float speed;
    float stamina,Max_stamina,regenerateS,regTimeS;
    float health,Max_health,regenerateH,regTimeH;
    float magic,Max_magic,regenerateM,regTimeM;

    Vector2f size;

    bool is_left;

    Clock clockH;
    Clock clockS;
    Clock clockM;

    Clock clock2;

public:
    void moveEsse(float oX,float oY, const vector<unique_ptr<Boundary>>& boundaries){
          Vector2f newPosition = position;
          newPosition.x += oX * speed;
          newPosition.y += oY * speed;

          Sprite tempSprite = this->sprite;
          tempSprite.setPosition(newPosition);

          for(const auto& boundary : boundaries){
                   if(tempSprite.getGlobalBounds().intersects(boundary->getBounds())){
                      FloatRect playerBounds = tempSprite.getGlobalBounds();
                      FloatRect boundaryBounds = boundary->getBounds();

                      float overlapLeft = playerBounds.left + playerBounds.width - boundaryBounds.left;
                      float overlapRight = boundaryBounds.left + boundaryBounds.width - playerBounds.left;
                      float overlapTop = playerBounds.top + playerBounds.height - boundaryBounds.top;
                      float overlapBottom = boundaryBounds.top + boundaryBounds.height - playerBounds.top;


                      if (overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom) {

                          newPosition.x -= overlapLeft / 2;
                      } else if (overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom) {

                          newPosition.x += overlapRight / 2;
                      } else if (overlapTop < overlapLeft && overlapTop < overlapRight && overlapTop < overlapBottom) {

                          newPosition.y -= overlapTop / 2;
                      } else if (overlapBottom < overlapLeft && overlapBottom < overlapRight && overlapBottom < overlapTop) {

                          newPosition.y += overlapBottom / 2;
                      }
               }
          }



          position = newPosition;

          this->sprite.setPosition(position);

    }



    void draw(RenderWindow& window){
          if (this->walk_count >= this->img_lists.size()) {
               this->walk_count = 0;
          }

          if(!texture.loadFromFile(this->img_lists[this->walk_count])){
              cerr << "Not download user img" << endl;
          }

          sprite.setTexture(texture);
          window.draw(this->sprite);
    }

    void update(const vector<unique_ptr<Boundary>>& boundaries){

            if(clockH.getElapsedTime().asSeconds() >= regTimeH){
                  if(this->health <= this->Max_health){
                      this->health += this->regenerateH;
                  }
                  clockH.restart();
            }


            if(clockS.getElapsedTime().asSeconds() >= regTimeS){
                  if(this->stamina <= this->Max_stamina){
                      this->stamina += this->regenerateS;
                  }
                  clockS.restart();
            }


            if(clockM.getElapsedTime().asSeconds() >= regTimeM){
                  if(this->magic <= this->Max_magic){
                      this->magic += this->regenerateM;
                  }
                  clockM.restart();
            }



        bool isMoving = false;

        if (Keyboard::isKeyPressed(Keyboard::A)) {

            isMoving = true;
            this->img_lists = path_to_img::player_lefts;
            this->is_left = true;
            moveEsse(-1.0f, 0.0f,boundaries);

        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            isMoving = true;
            this->is_left = false;
            this->img_lists = path_to_img::player_rights;
            moveEsse(1.0f, 0.0f,boundaries);


        }


        if (Keyboard::isKeyPressed(Keyboard::W)) {
            isMoving = true;
            moveEsse(0.0f, -1.0f,boundaries);

        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            isMoving = true;
            moveEsse(0.0f, 1.0f,boundaries);

        }

        if(isMoving){
            if(clock2.getElapsedTime().asSeconds() >= this->fps_walk){
                this->walk_count++;
                clock2.restart();
            }
        }else{
            walk_count = this->img_lists.size() - 1;

        }

    }

    Vector2f getPosition() const {
         return this->position;
    }
    FloatRect getBounds() const {
         return sprite.getGlobalBounds();
    }


};

class Player;

class Effect{
public:
    string title;
    string icon_path;
    Texture texture;
    Sprite sprite;
    Vector2f sprite_size;

    float duration;
    float delay;
    float impact;

    Clock clock;
    Clock clock1;

    virtual void func(Player& player){

    }

};



class Item{
public:
     string title;
     Texture texture;
     Sprite sprite;
     float size,masse;
     Vector2f position;
     Vector2f sprite_size;
     bool inInventory = false;
     int anim_count = 0;


     void set_position(Vector2f& pos){
         this->position = pos;
     }

     void draw_item(RenderWindow& window){
         sprite.setPosition(position);
         sprite.setScale((sprite_size.x / texture.getSize().x),sprite_size.y / texture.getSize().y);
         window.draw(sprite);
     }

     void item_draw(RenderWindow& window){
         sprite.setPosition(position);
         sprite.setScale(-(sprite_size.x / texture.getSize().x),sprite_size.y / texture.getSize().y);
         window.draw(sprite);
     }

     void setName(string newTitle){
         this->title = newTitle;
     }

     FloatRect get_bounds(){
         return sprite.getGlobalBounds();
     }

     virtual void func(RenderWindow& window,Vector2i& mousePos,
     vector<unique_ptr<Essence>>& life_objects,
     vector<unique_ptr<Boundary>>& unlife_objects,Player& player
     ) = 0;
};


class Player : public Essence{
public:
   float max_size = 150,max_weight = 50,inv_size = 0,inv_weight = 0;
   vector<Effect> effects;
   vector<unique_ptr<Item>> inventory;
   unique_ptr<Item> hand;
   Clock clock2;

   Player(void){}

   Player(const vector<string>& img_path_list,
          float x,float y,
          float speed,float fps_walk,float w,float h)
          {
          this->fps_walk = fps_walk;
          this->speed = speed;
          this->position = Vector2f(x,y);
          this->img_lists = img_path_list;
          this->size = Vector2f(w,h);
          }

   bool appendItem(unique_ptr<Item>&& item){
          float masse = item->masse;
          float size = item->size;
          float free_masse = max_weight - inv_weight;
          float free_size = max_size - inv_size;
          if(masse < free_masse && size < free_size){
              inventory.push_back(move(item));
              return true;
          }else{
              return false;
          }
      }

   void draw(RenderWindow& window){
             if (this->walk_count >= this->img_lists.size()) {
                  this->walk_count = 0;
             }

             if(!texture.loadFromFile(this->img_lists[this->walk_count])){
                 cerr << "Not download user img" << endl;
             }

             sprite.setTexture(texture);
             window.draw(this->sprite);
             // Draw Hand Object
             if(this->hand){
                  hand->position = this->position;
                  Vector2f newPos = Vector2f(position.x,position.y + (size.x / 2.5));
                  hand->set_position(newPos);
                  if(this->is_left){
                      hand->sprite.setScale(-1.0f,1.0f);

                      Vector2f newPos = Vector2f(position.x + hand->sprite_size.x / 2,position.y + (size.x / 2.5));
                      hand->set_position(newPos);
                      hand->item_draw(window);
                  }else{
                      hand->sprite.setScale(1.0f,1.0f);
                      hand->draw_item(window);
                  }

             }


      }
   void useHand(RenderWindow& window,Vector2i& mousePos,
        vector<unique_ptr<Essence>>& life_objects,
        vector<unique_ptr<Boundary>>& unlife_objects,Player& player){
            if(hand){
                 hand->func(window,mousePos,life_objects,unlife_objects,player);
            }
      }


   void setM(float reg,float time,float val,float max){
          this->regenerateM = reg;
          this->regTimeM = time;
          this->magic = val;
          this->Max_magic = max;
      }
   void setH(float reg,float time,float val,float max){
          this->regenerateH = reg;
          this->regTimeH = time;
          this->health = val;
          this->Max_health = max;
      }
   void setS(float reg,float time,float val,float max){
          this->regenerateS = reg;
          this->regTimeS = time;
          this->stamina = val;
          this->Max_stamina = max;
      }
};

class Arrow : public Item{};

class Bow : public Item{};

class KatanSword : public Item{
private:
   float damage;
   float speed_attack = 2;
   float defend;
   vector<string> slash_pathes;
   Texture slash_texture;
   Sprite slash_sprite;
   Clock clock1;

public:
   KatanSword(float masse, float size, float damage,float defend,
              string& path, vector<string>& images_path,
              float w,float h)
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
   }


   void func(RenderWindow& window,Vector2i& mousePos,
     vector<unique_ptr<Essence>>& life_objects,
     vector<unique_ptr<Boundary>>& unlife_objects,Player& player) override
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

};

class Potion_health : public Item{
public:
   vector<Effect> effects;

   Potion(vector<Effect> effects,float size,float weight,string& path,float w,float h){
        this->effects = effects;
        this->size = size;
        this->masse = weight;
        if(!texture.loadFromFile(path)){
            cerr << "Error in Potion class" << endl;
        }
        this->sprite.setTexture(texture);
        this->sprite_size = Vector2f(w,h);
   }

   void func(RenderWindow& window,Vector2i& mousePos,
     vector<unique_ptr<Essence>>& life_objects,
     vector<unique_ptr<Boundary>>& unlife_objects,Player& player)
   {

   }
};

class HealthBoost : public Effect{
public:
    void func(Player& player) override {

    }
};



class Human : public Essence{};

class Animal : public Essence{};

class Box : public Boundary{};


class World{
private:
     Sprite sprite;
     Texture texture;
     float width,height;
public:
     World(const string& FilePath){
         if(!this->texture.loadFromFile(FilePath)){
             cerr << "Filed in bg class" << endl;

         }
         sprite.setTexture(this->texture);
         this->width = texture.getSize().x;
         this->height = texture.getSize().y;
     }
     float getWidth(){
         return this->width;
     }
     float getHeight(){
         return this->height;
     }

     void draw(RenderWindow &window){
         window.draw(this->sprite);
     }

};

int main() {

    RenderWindow window(VideoMode(WIDTH,HEIGHT),"Work");

    World world(path_to_img::world_bg1);


    Player player(path_to_img::player_lefts,120.0f,40.0f,
                NORMAL_SPEED,0.1f,40.0f,40.0f);


    //          reg time val max
    player.setH(1.0,0.1,1.2,100.0);
    player.setS(1.0,0.1,1.2,100.0);
    player.setM(1.0,0.1,1.2,100.0);
    // Bars
    RectangleShape healthBar(Vector2f(80,5));
    healthBar.setFillColor(Color::Red);

    RectangleShape magicBar(Vector2f(80,5));
    magicBar.setFillColor(Color::Blue);

    RectangleShape staminaBar(Vector2f(80 ,5));
    staminaBar.setFillColor(Color::Green);

    unique_ptr<KatanSword> katanaDefault = make_unique<KatanSword>(20.0,100.0,25.0,100,
                                                    path_to_img::katana_path,path_to_img::katana_slash_pathes,55.0,10.0);

    Vector2f posKatan = Vector2f(231.0f,150.0f);
    katanaDefault->set_position(posKatan);


    vector<unique_ptr<Item>> items_lists;

    items_lists.push_back(move(katanaDefault));
    vector<unique_ptr<Boundary>> Boundaries;

// World boundary

    unique_ptr<Boundary> wall = make_unique<Boundary>(path_to_img::stone_path, world.getWidth(),50.0f,
                                           0.0f,0.0f
                                           );
    Boundaries.push_back(move(wall));

    unique_ptr<Boundary> wall1 = make_unique<Boundary>(path_to_img::stone_path, world.getWidth(),50.0f,
                                           0.0f,world.getHeight()
                                           );
    Boundaries.push_back(move(wall1));

    unique_ptr<Boundary> wall2 = make_unique<Boundary>(path_to_img::stone_path, 50.0f,world.getHeight(),
                                           0.0f,0.0f
                                           );
    Boundaries.push_back(move(wall2));

    unique_ptr<Boundary> wall3 = make_unique<Boundary>(path_to_img::stone_path, 50.0f,world.getHeight(),
                                           world.getWidth(),0.0f
                                           );
    Boundaries.push_back(move(wall3));
// World boundary

    vector<unique_ptr<Essence>> Essencies;

    View camera = window.getDefaultView();
    camera.setCenter(player.getPosition());
    camera.zoom(NORMAL_ZOOM);


    Font pixel_font;

    if (!pixel_font.loadFromFile("fonts/pixel.ttf")) {
         cerr << "Error loading font" << endl;
    }
    Text pixel_text;
    pixel_text.setFont(pixel_font);

    pixel_text.setCharacterSize(10);
    pixel_text.setFillColor(Color::White);

    bool IsOpenInventory = false;
    Texture backTex;
    Sprite backSpr;
    if(!backTex.loadFromFile(path_to_img::invBack_path)){
         cerr << "Inventory background" << endl;
    }
    backSpr.setTexture(backTex);



    while(window.isOpen()){
        bool game = true;
        //Event
        while(game){
           Event event;
           while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                  window.close();
                  game = false;
                  return 1;
            }
            if(event.type == Event::KeyPressed){
                 if(event.key.code == Keyboard::Tab){
                     if(IsOpenInventory){
                         IsOpenInventory = false;

                     }else{
                         IsOpenInventory = true;

                     }
                 }
            }

            }
        //Event

        window.clear();
        world.draw(window);


        for(auto& obj : items_lists){
            obj->draw_item(window);
            if(player.getBounds().intersects(obj->get_bounds())){
                 pixel_text.setString("Press E to pick up");
                 pixel_text.setPosition(player.position.x, player.position.y - player.size.y / 2);

                 if(Keyboard::isKeyPressed(Keyboard::E)){

                      if(player.appendItem(move(obj))){
                            pixel_text.setString("Success append item");
                            pixel_text.setPosition(player.position.x, player.position.y - player.size.y / 2);


                            auto it = find(items_lists.begin(),items_lists.end(),obj);
                            if(it != items_lists.end()){
                                 items_lists.erase(it);
                            }
                      } else {
                           pixel_text.setFillColor(Color::Red);
                           pixel_text.setString("not enough space or strength");
                           pixel_text.setPosition(player.position.x, player.position.y - player.size.y / 2);
                      }
                 }

                 window.draw(pixel_text);
            }
        }


        // PLAYER //
        player.draw(window);
        player.update(Boundaries);


        for(auto& obj : Boundaries){
            obj->draw(window);

        }

        if(player.health <= 0){
            game = false;
            break;
        }
        window.draw(healthBar);
        window.draw(magicBar);
        window.draw(staminaBar);


        // PLAYER//





        // SYSTEM //
        if(IsOpenInventory){
             Vector2i mouse_pos = Mouse::getPosition(window);
             Vector2f world_pos = window.mapPixelToCoords(mouse_pos);

             Sprite hand_back;
             hand_back.setTexture(backTex);
             float h_x = -150.0f ,h_y = 50.0f;

             h_x += player.getPosition().x;
             h_y += player.getPosition().y;
             hand_back.setPosition(h_x,h_y);

             if(player.hand){
                          hand_back.setScale(player.hand->sprite_size.x / 100,
                                player.hand->sprite_size.y / 100);
                          Sprite hand_obj = player.hand->sprite;
                          hand_obj.setPosition(h_x ,h_y);
                          hand_obj.setScale(1.0f,1.0f);
                          hand_obj.setScale((player.hand->sprite_size.x / player.hand->texture.getSize().x),
                                             player.hand->sprite_size.y / player.hand->texture.getSize().y);
                          window.draw(hand_back);
                          window.draw(hand_obj);
                          if(hand_obj.getGlobalBounds().contains(world_pos)){
                                  if (Mouse::isButtonPressed(Mouse::Left)) {
                                       player.inventory.push_back(move(player.hand));
                                  }else if(Mouse::isButtonPressed(Mouse::Right)){
                                       player.hand->position = player.position;
                                       items_lists.push_back(move(player.hand));
                                  }
                          }

             }else{
                  hand_back.setScale(0.3f,0.3f);
                  window.draw(hand_back);
             }


             float item_spacing = 10.0f;
             float start_x = -150.0f;
             float start_y = -150.0f;


             float inv_w = player.max_size / 100;
             float inv_h = player.max_size / 100;

             backSpr.setPosition(Vector2f(start_x + player.getPosition().x,start_y + player.getPosition().y));
             backSpr.setScale(inv_w,inv_h);
             window.draw(backSpr);

             for(auto& item : player.inventory){
                  for (size_t i = 0; i < player.inventory.size(); ++i) {

                      float x = start_x;
                      float y = start_y + i * item_spacing;
                      x += player.getPosition().x;
                      y += player.getPosition().y;
                      if (player.inventory[i]) {

                          Sprite item_sprite;
                          item_sprite.setTexture(player.inventory[i]->texture);


                          item_sprite.setPosition(x, y);
                          item_sprite.setScale((player.inventory[i]->sprite_size.x / player.inventory[i]->texture.getSize().x / 2),
                          player.inventory[i]->sprite_size.y / player.inventory[i]->texture.getSize().y / 2);

                          window.draw(item_sprite);


                          if (item_sprite.getGlobalBounds().contains(world_pos)) {
                               if (Mouse::isButtonPressed(Mouse::Right)) {
                                   player.inventory[i]->position = player.position;
                                   items_lists.push_back(move(player.inventory[i]));
                                   player.inventory.erase(player.inventory.begin() + i);
                                   break;
                               }else if(Mouse::isButtonPressed(Mouse::Left)){
                                   player.hand = move(player.inventory[i]);
                                   player.inventory.erase(player.inventory.begin() + i);
                                   break;
                               }
                           }
                      }

                  }
             }
        }
        // SYSTEM //



        // Bars
        healthBar.setSize(Vector2f((80 * ((player.health * 100) / player.Max_health)) / 100,10));
        magicBar.setSize(Vector2f((80 * ((player.magic * 100) / player.Max_magic)) / 100,10));
        staminaBar.setSize(Vector2f((80 * ((player.stamina * 100) / player.Max_stamina)) / 100,10));

        Vector2f healthBarOffset(-220, -(HEIGHT / 7.5));

        healthBar.setPosition(player.getPosition() + healthBarOffset);

        Vector2f staminaBarOffset(-25, -(HEIGHT / 7.5));

        staminaBar.setPosition(player.getPosition() + staminaBarOffset);

        Vector2f magicBarOffset(170, -(HEIGHT / 7.5));

        magicBar.setPosition(player.getPosition() + magicBarOffset);
        // Bars



        //Camera
        camera.setCenter(player.getPosition());
        window.setView(camera);
        //Camera

        if(Mouse::isButtonPressed(Mouse::Left)){
              Vector2i mousePos = Mouse::getPosition(window);
              if(!IsOpenInventory) player.useHand(window,mousePos,Essencies,Boundaries,player);
        }


        window.display();
        }
    }
    return 0;
}