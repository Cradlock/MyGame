#include "baseClass.h"
#include "resourses.h"

// Boundary
Boundary::Boundary(const string& img_path, float width, float height, float x, float y)
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


void Boundary::draw(RenderWindow &window) {
        FSprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);
        FSprite.setPosition(this->position);

        window.draw(FSprite);
}


FloatRect Boundary::getBounds() const {
        return FSprite.getGlobalBounds();
}

// End




// Essence
void Essence::moveEsse(float oX,float oY, const vector<unique_ptr<Boundary>>& boundaries){
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

void Essence::draw(RenderWindow& window){
          if (this->walk_count >= this->img_lists.size()) {
               this->walk_count = 0;
          }

          if(!texture.loadFromFile(this->img_lists[this->walk_count])){
              cerr << "Not download user img" << endl;
          }

          sprite.setTexture(texture);
          window.draw(this->sprite);
}

void Essence::update(const vector<unique_ptr<Boundary>>& boundaries){

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

Vector2f Essence::getPosition() const {
         return this->position;
}
    
FloatRect Essence::getBounds() const {
         return sprite.getGlobalBounds();
}
// End



//Item

void Item::set_position(Vector2f& pos){
         this->position = pos;
}

void Item::draw_item(RenderWindow& window){
         sprite.setPosition(position);
         sprite.setScale((sprite_size.x / texture.getSize().x),sprite_size.y / texture.getSize().y);
         window.draw(sprite);
}

void Item::item_draw(RenderWindow& window){
         sprite.setPosition(position);
         sprite.setScale(-(sprite_size.x / texture.getSize().x),sprite_size.y / texture.getSize().y);
         window.draw(sprite);
}

void Item::setName(string newTitle){
         this->title = newTitle;
}

FloatRect Item::get_bounds() const {
         return sprite.getGlobalBounds();
}

//End





//Player

Player::Player(const vector<string>& img_path_list,float x,float y,float speed,float fps_walk,float w,float h)
{
          this->fps_walk = fps_walk;
          this->speed = speed;
          this->position = Vector2f(x,y);
          this->img_lists = img_path_list;
          this->size = Vector2f(w,h);
}

bool Player::appendItem(unique_ptr<Item>&& item){
          float masse = item->masse;
          float size = item->size;
          float free_masse = max_weight - inv_weight;
          float free_size = max_size - inv_size;
          if(masse < free_masse && size < free_size){
              inventory.push_back(move(item));
              this->inv_weight += masse;
              this->inv_size += size;
              return true;
          }else{
              return false;
          }
}

void Player::draw(RenderWindow& window){
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

void Player::useHand(RenderWindow& window,Vector2i& mousePos,vector<unique_ptr<Essence>>& life_objects,vector<unique_ptr<Boundary>>& unlife_objects,Player& player){
            if(hand){
                 hand->func(window,mousePos,life_objects,unlife_objects,player);
            }
}

void Player::setM(float reg,float time,float val,float max){
          this->regenerateM = reg;
          this->regTimeM = time;
          this->magic = val;
          this->Max_magic = max;
}

void Player::setH(float reg,float time,float val,float max){
          this->regenerateH = reg;
          this->regTimeH = time;
          this->health = val;
          this->Max_health = max;
      }

void Player::setS(float reg,float time,float val,float max){
          this->regenerateS = reg;
          this->regTimeS = time;
          this->stamina = val;
          this->Max_stamina = max;
}


//End