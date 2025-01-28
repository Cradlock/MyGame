#include <SFML/Audio.hpp>
#include "files/resourses.h"
#include "files/Abstract/World.h"
#include "files/System/windows.h"
#include "files/Locations/location.h"



bool isVisibly(const FloatRect& objectsBounds,const FloatRect& viewBounds){
    return objectsBounds.intersects(viewBounds);
};

float randint(float start,float end){
    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<> dis(start,end);
    return dis(gen);
}

void generate(unordered_map<string , Texture>& textures,vector<PartWorld>& partes,vector<Object>& objects_top,vector<Object>& objects_bottom,World& w){
    float px = 0;
    float py = 0;

    random_device rd;
    mt19937 gen(rd());

    for(auto& n : w.player.images_numbers){
            string key = path_to_img::Player_images[n];
            if(textures.find(key) == textures.end()){
                Texture t1;
                t1.loadFromFile(key);
                textures[key] = t1;
            }
        }

    for(auto& i : w.map[0]){
        for(auto& x : i){
          int n = x;
          string key = path_to_img::PartWorld::blockes[n];
          if(key != "Void"){
            if(textures.find(key) == textures.end()){
               Texture t1;
               bool info = t1.loadFromFile(key);
               textures[key] = t1;
            }
            PartWorld t2;
            t2.spr.setTexture(textures[key]);

            setSize(t2.spr,standart_size,standart_size);
           
            t2.spr.setPosition(px,py); 
            partes.push_back(t2);
           }
           px += standart_size;
          
        }
        px = 0;
        py += standart_size;
        
    }
    w.width = w.map[0][0].size() * standart_size;
    w.height = w.map[0].size() * standart_size;
    w.height -= w.height / 3;

    px = 0;
    py = 0;

    for(auto& i : w.map[1]){
       for(auto& n : i){
          if(n != 0){
            for(int& idx : Global_Objects_list[n].images_numbers){
                string key = path_to_img::Objects[idx];
                if(textures.find(key) == textures.end()){
                    Texture t1;
                    t1.loadFromFile(key);
                    textures[key] = t1;
                }
                
              }
             
              Object obj = Global_Objects_list[n];
              Texture& txs = textures[path_to_img::Objects[obj.images_numbers[0]]];
              obj.spr.setTexture(txs);
              obj.spr.setPosition(px,py);
              
            
                
              obj.hitbox.left = obj.spr.getGlobalBounds().left + (obj.hitbox.width * obj.hitbox.left);
              obj.hitbox.top = obj.spr.getGlobalBounds().top + obj.height * obj.hitbox.top;

              setSize(obj.spr,obj.width,obj.height);
              
              if(obj.position_level == 1){
                 objects_top.push_back(obj);
              }else if(obj.position_level == 0){
                 objects_bottom.push_back(obj);
              }
           }
        
           px += standart_size;
       }
       py += standart_size;
       px = 0;
    }
    

    for(auto& i : w.essences){
        for(auto& n : i.images_numbers){
        string key = path_to_img::Essence_images[n];
            if(textures.find(key) == textures.end()){
                Texture t1;
                t1.loadFromFile(key);
                textures[key] = t1;
            }
        }
    }
}


int main() {
    
 
    bool isGame = false;
    bool isMenu = true;
    bool IsNotGenerate = true;
    string path_to_save;
    int page = 0;
    
    
    World world;
    Texture background_texture;
    Sprite background_sprite;

    unordered_map<string,Texture> textures;
    vector<PartWorld> partes;

    unordered_map<int,Object> objects;

    vector<Object> objects_top;
    vector<Object> objects_bottom;
    
    vector<Item> items;

    vector<Essence> essences;

    vector<Projectile> projectiles;

    srand(time(0));
    
    int randomNumber = rand() % 3 + 1; 
    MainMenu mainmenu{randomNumber};


    Sprite cObject;
    cObject.setPosition(0,0); 
    View camer{FloatRect(0, 0, 800, 600)};
    camer.zoom(NORMAL_ZOOM);


    
    RenderTexture lightTexture;
    lightTexture.create(WIDTH, HEIGHT);
    

    Sprite CoverSprite(lightTexture.getTexture());
    CoverSprite.setPosition(0,0);


    Clock T;

    
    
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
        }
        Vector2i mousePos = Mouse::getPosition(window);
        
        window.clear();
        
        if(isGame){
            
                if(path_to_save == "new"){    
                    
                    if(IsNotGenerate){
                       world = World{"Episode 0",1,{  }};
                       world.player = PLAYER;
                       generate(textures,partes,objects_top,objects_bottom,world);
                       setSize(world.player.spr,world.player.width,world.player.height);

                       IsNotGenerate = false;     
                    } 
                    

                    // Day <_> Night - start


                    // Day <_> Night - end


                    // 
                    if(world.player.spr.getPosition().x >= world.width){
                        world.player.spr.setPosition(0,world.player.spr.getPosition().y );     
                    }
                    if(world.player.spr.getPosition().x < 0){
                        world.player.spr.setPosition(world.width,world.player.spr.getPosition().y );
                    }

                    if(world.player.spr.getPosition().y >= world.height){
                        world.player.spr.setPosition(world.player.spr.getPosition().x,0);     
                    }
                    if(world.player.spr.getPosition().y < 0){
                        world.player.spr.setPosition(world.player.spr.getPosition().x,world.height);
                    }

                // Draw objects - start
                    FloatRect viewBounds(
                       camer.getCenter() - camer.getSize() / 2.f,
                       camer.getSize()                          
                    );
                    

                    if(world.essences.size() > 0){
                        for(auto& e : world.essences){
                        // Draw partes world - start
                        for(auto& p : partes){
                            if(isVisibly(p.spr.getGlobalBounds(),viewBounds)){
                                renderObject(p.spr);
                            }            
                        }
                        // Draw partes world - end
                        
                        // Draw objects_top - start
                        
                        for(auto& o : objects_top){
                            if ( isVisibly(o.spr.getGlobalBounds() , viewBounds) ) {
                                renderObject(o.spr);
                            }
                        }

                        // Draw object_top - end


                        // All essences (player) - start
                        e.spr.setTexture(textures[ path_to_img::Player_images[ e.images_numbers[e.counter] ] ]);
                        setSize(e.spr,e.width,e.height);
                        
                        if(isVisibly(e.spr.getGlobalBounds(),viewBounds)){
                            e.behaivor(window);
                        }

                        world.player.spr.setTexture(textures[ path_to_img::Player_images[ world.player.images_numbers[world.player.counter] ] ]);
                        world.player.behaivor(window);
                        
                        // All essences (player) - end

                        // Draw object_bottom - start 
                        for(auto& o : objects_bottom){
                            if ( isVisibly(o.spr.getGlobalBounds() , viewBounds) ) {
                                renderObject(o.spr);
                            }
                        }
                        // Draw object bottom - end
                    }                       
                    } else {
                        // Draw partes world - start
                        for(auto& p : partes){
                            if(isVisibly(p.spr.getGlobalBounds(),viewBounds)){
                                renderObject(p.spr);
                            }            
                        }
                        // Draw partes world - end
                         

                        // Draw object_bottom - start 
                        for(auto& o : objects_bottom){
                            if ( isVisibly(o.spr.getGlobalBounds() , viewBounds) ) {
                                renderObject(o.spr);
                                FloatRect bounds = o.hitbox;
                                RectangleShape border;
                                border.setSize(Vector2f(bounds.width,bounds.height));
                                border.setPosition(bounds.left,bounds.top);
                                border.setFillColor(Color::Transparent);
                                border.setOutlineColor(Color::Red);
                                border.setOutlineThickness(1.0f);
                                renderObject(border);
                                o.Func(world.player,objects_top,objects_bottom,projectiles,window);

                             }
                          }
                        // Draw object bottom - end
                                            
                        
                        // (player) - start

                        world.player.spr.setTexture(textures[ path_to_img::Player_images[ world.player.images_numbers[world.player.counter] ] ]);
                        world.player.behaivor(window);

                        // (player) - end
                        
                        // Draw objects_top - start
                        
                        for(auto& o : objects_top){
                            if ( isVisibly(o.spr.getGlobalBounds() , viewBounds) ) {
                                o.Func(world.player,objects_top,objects_bottom,projectiles,window);
                                FloatRect bounds = o.hitbox;
                                RectangleShape border;
                                border.setSize(Vector2f(bounds.width,bounds.height));
                                border.setPosition(bounds.left,bounds.top);
                                border.setFillColor(Color::Transparent);
                                border.setOutlineColor(Color::Red);
                                border.setOutlineThickness(1.0f);
                                renderObject(border);
                                renderObject(o.spr);
                            }
                        }
                        // Draw object_top - end

                        cout << "top - " << objects_top.size() << " --- "
                        << "bottom - " << objects_bottom.size() << endl;
                        
                    }



                // Draw objects - end

                    lightTexture.clear(Color(world.red ,world.green , world.blue, world.opacity));
                    
                    CoverSprite.setPosition(Vector2f(world.player.spr.getPosition().x - WIDTH / 2 , world.player.spr.getPosition().y - HEIGHT / 2));
                    window.draw(CoverSprite);

                    camer.setCenter(world.player.spr.getPosition());
                
                    window.draw(cObject);
            
                    window.setView(camer);

                }else{
                   // Load save world from bin file - start
                    
                   // end
                }
            

        }else{  
            mainmenu.BackgroundRender();
            if(page == 0){
                page = mainmenu.update(mousePos);
            }else if(page == 1){
                isGame = true;
                path_to_save = "new";
            }else if(page == 2){
                page = mainmenu.updateSaves(mousePos,path_to_save,isGame);
                
            }else if(page == 3){
                page = mainmenu.updateSettings(mousePos);
            }else if(page == 4){
                break;
            }
        }
        
        window.display();
    }
    return 0;
}