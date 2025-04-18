#include "linker.h"


bool isVisibly(const FloatRect& objectsBounds,const FloatRect& viewBounds){
    return objectsBounds.intersects(viewBounds);
};

float randint(float start,float end){
    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<> dis(start,end);
    return dis(gen);
}

void generate(World& w){
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
              obj.id = counterID;
              

              if(obj.position_level == 1){
                 objects_top.push_back(obj.id);
              }else if(obj.position_level == 0){
                 objects_bottom.push_back(obj.id);
              }


              auto light_obj = make_shared<Light>(0,Color::White);
              obj.light = light_obj;
              
              localLight.push_back(light_obj);

             
              localObjects[obj.id] = obj;

              
              counterID++;
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


    Shader shader;
    if (!shader.loadFromFile("shaders/standart/glow.frag", sf::Shader::Fragment))
    std::cerr << "Ошибка при загрузке шейдера!" << std::endl;


    bool isGame = false;
    bool isMenu = true;
    bool IsNotGenerate = true;
    string path_to_save;
    int page = 0;

    
    
    World world;
    Texture background_texture;
    Sprite background_sprite;


    srand(time(0));
    
    int randomNumber = rand() % 3 + 1; 
    MainMenu mainmenu{randomNumber};



    Sprite cObject;
    cObject.setPosition(0,0); 
    View camer{FloatRect(0, 0, 800, 600)};
    camer.zoom(NORMAL_ZOOM);


    
    RenderTexture lightTexture;
    lightTexture.create(100,100);
   
    Sprite CoverSprite(lightTexture.getTexture());
    
    CoverSprite.setPosition(0,0);


    Clock clockT;
    Clock counterTime;
    
    window.setFramerateLimit(120);

    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
        }
        Vector2f mousePos = Vector2f(Mouse::getPosition(window));

        window.clear();

        if(isGame){
            if(path_to_save == "new"){  
// World parametrs - start


  //init functions start

  init_db();

  //init functions end
                    if(IsNotGenerate){ 
                        world = World{"Episode 0",1,{  }};
                       
                        world.player = PLAYER;
                        world.player.id = counterID;
                        
                        
                        auto lig = make_shared<Light>(10,Color::White); 

                        world.player.light = lig;

                        localLight.push_back(lig);
                        
                        counterID++;
                        generate(world);

                        lightTexture.create(world.width,world.height);
                        CoverSprite.setTexture(lightTexture.getTexture());
                        CoverSprite.setTextureRect(IntRect(0, 0, world.width, world.height));
                        
                        world.player.spr.setPosition(0,0);
                        setSize(world.player.spr,world.player.width,world.player.height);
                        IsNotGenerate = false; 
                        counterTime.restart();   
                        world.red = 25;
                        world.green = 25;
                        world.blue = 25;
                        world.opacity = 255; 

                    } 
                
// World parametrs - end


// Draw objects - start
                    FloatRect viewBounds(camer.getCenter() - camer.getSize() / 2.f,camer.getSize());
                    
                    if(world.essences.size() > 0){
                        for(auto& e : world.essences){
                        // Draw partes world - start
                        for(auto& p : partes){
                            if(isVisibly(p.spr.getGlobalBounds(),viewBounds)){
                                window.draw(p.spr);
                            }            
                        }
                        // Draw partes world - end
                        
                        // Draw objects_top - start
                        
                        for(auto& i : objects_top){
                            Object o = localObjects[i];
                            if ( isVisibly(o.spr.getGlobalBounds() , viewBounds) ) {
                               window.draw(o.spr);
                            }
                            ObjectsDB[o.IdFunc](o,e);
                        }

                        //  Draw object_top - end


// All essences (player) - start
                        e.spr.setTexture(textures[ path_to_img::Player_images[ e.images_numbers[e.counter] ] ]);
                        setSize(e.spr,e.width,e.height);
                        
                        if(isVisibly(e.spr.getGlobalBounds(),viewBounds)){
                            EssencesLambdaDB[e.behavior_id](e);
                        }
                        EssencesLambdaDB[e.behavior_id](e);

                        world.player.spr.setTexture(textures[ path_to_img::Player_images[ world.player.images_numbers[world.player.counter] ] ]);
                        
                        
// All essences (player) - end

// Draw object_bottom - start 
                        for(auto& i : objects_bottom){
                            Object o = localObjects[i];
                            if ( isVisibly(o.spr.getGlobalBounds() , viewBounds) ) {
                                window.draw(o.spr);
                            }
                            ObjectsDB[o.IdFunc](o,e);
                        }
                    }
// Draw object bottom - end                      
                    } else {              
// Draw partes world - start
                        for(auto& p : partes){
                            if(isVisibly(p.spr.getGlobalBounds(),viewBounds)){
                                window.draw(p.spr);
                            }            

                        }
// Draw partes world - end
            
// Draw object_bottom - start 
                        for(auto& i : objects_bottom){
                            Object o = localObjects[i];
                            if ( isVisibly(o.spr.getGlobalBounds() , viewBounds) ) {
                                window.draw(o.spr);
                             }
                             ObjectsDB[o.IdFunc](o,world.player);
                          }
// Draw object bottom - end
                                            
                        
// (player) - start
                  
                        world.player.spr.setTexture(textures[ path_to_img::Player_images[ world.player.images_numbers[world.player.counter] ] ]);
                        EssencesLambdaDB[world.player.behavior_id](world.player);
                        window.draw(world.player.spr);

// (player) - end
                        
// Draw objects_top - start
                        
                        for(auto& i : objects_top){
                            Object o = localObjects[i];
                            if ( isVisibly(o.spr.getGlobalBounds() , viewBounds) ) {
                                window.draw(o.spr);
                            }
                            ObjectsDB[o.IdFunc](o,world.player);
                        }
// Draw object_top - end
                        
                    }
                    
// Day <_> Night - start
                    lightTexture.clear(Color(world.red,world.green,world.blue,world.opacity));
                   
                    for(auto& light : localLight){
                        if(light->circle.getRadius() != 0){
                            shader.setUniform("resolution",Vector2f(window.getSize()));
                            shader.setUniform("texture",Shader::CurrentTexture);
                            Vector2f center = light->circle.getPosition() + sf::Vector2f(light->circle.getRadius(), light->circle.getRadius());
                            shader.setUniform("center",center);
                            shader.setUniform("radius",light->circle.getRadius());
                            Color c = light->circle.getFillColor();
                            shader.setUniform("color",Glsl::Vec4( c.r / 255.f ,c.g / 255.f ,c.b / 255.f  ,c.a / 255.f ));
                            lightTexture.draw(light->circle,&shader);

                        }  
                    }

                    lightTexture.display();
                    window.draw(CoverSprite, BlendMultiply);

// Day <_> Night - end

                    camer.setCenter(world.player.spr.getPosition());
                 
                    window.draw(cObject);
            
                    window.setView(camer);

            }else{

            }
        }else{  
            mainmenu.BackgroundRender();
            if(page == 0){
                page = mainmenu.update(mousePos);
            }
            else if(page == 1){
                isGame = true;
                path_to_save = "new";
            }else if(page == 2){
                page = mainmenu.updateSaves(mousePos,path_to_save,isGame);
            }else if(page == 3){
                page = mainmenu.updateSettings(mousePos);
            }else if(page == 4)break;
        
        }
        window.display();

    }
    return 0;
}