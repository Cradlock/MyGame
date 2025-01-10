#ifndef BASECLASS_H
#define BASECLASS_H


#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace sf;
using namespace std;



class Boundary{
private:
    Texture texture;
    string path;
    Sprite FSprite;
    Vector2f size;
    Vector2f position;
    float defend;


public:
    Boundary(const string& img_path,float width,float height,float x,float y);
    void draw(RenderWindow &window);
    FloatRect getBounds() const;
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
    void moveEsse(float oX,float oY, const vector<unique_ptr<Boundary>>& boundaries);

    void draw(RenderWindow& window);

    void update(const vector<unique_ptr<Boundary>>& boundaries);

    Vector2f getPosition() const;

    FloatRect getBounds() const;

};

class Player;

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

     void set_position(Vector2f& pos);

     void draw_item(RenderWindow& window);

     void item_draw(RenderWindow& window);

     void setName(string newTitle);

     FloatRect get_bounds() const;

     virtual void func(RenderWindow& window,Vector2i& mousePos,
     vector<unique_ptr<Essence>>& life_objects,
     vector<unique_ptr<Boundary>>& unlife_objects,Player& player
     ) = 0;
};

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
    Clock clock2;

    virtual void func(RenderWindow& screen,Player& player){}

};

class Player : public Essence{
public:
   float max_size = 250,max_weight = 50,inv_size = 0,inv_weight = 0;
   vector<unique_ptr<Effect>> effects;
   vector<unique_ptr<Item>> inventory;
   unique_ptr<Item> hand;
   Clock clock2;

    

   Player(void){}
   
   Player(const vector<string>& img_path_list,
          float x,float y,
          float speed,float fps_walk,float w,float h);

   
    
   bool appendItem(unique_ptr<Item>&& item);

   void draw(RenderWindow& window);

    void useHand(RenderWindow& window,Vector2i& mousePos,
        vector<unique_ptr<Essence>>& life_objects,
        vector<unique_ptr<Boundary>>& unlife_objects,Player& player);

   void setM(float reg,float time,float val,float max);
 

   void setH(float reg,float time,float val,float max);    

   
    
   void setS(float reg,float time,float val,float max);

   
};

#endif