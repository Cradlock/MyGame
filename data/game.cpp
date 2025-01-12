#include <SFML/Audio.hpp>
#include "files/resourses.h"
#include "files/Abstract/World.h"
#include "files/System/windows.h"
#include "files/Locations/location.h"


float randint(float start,float end){
    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<> dis(start,end);
    return dis(gen);
}

void generate(unordered_map<string , Texture>& textures,vector<PartWorld>& partes,vector<Object>& objects_top,vector<Object>& objects_bottom,
              World& w){
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
              if(!obj.IsExactSize){

                  uniform_real_distribution<> dis1(obj.wmin,obj.wmax);
                  uniform_real_distribution<> dis2(obj.hmin,obj.hmax);

                  float w = dis1(gen);
                  float h = dis2(gen);
                  obj.width = w;
                  obj.height = h; 
              }
              
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
    bool IsNotGenerate = true;
    string path_to_save;
    int page = 0;
    
    
    World world;
    Texture background_texture;
    Sprite background_sprite;

    unordered_map<string,Texture> textures;
    vector<PartWorld> partes;

    vector<Object> objects_top;
    vector<Object> objects_bottom;
    
    vector<Item> items;

    vector<Essence> essences;

    srand(time(0));
    
    int randomNumber = rand() % 3 + 1; 
    MainMenu mainmenu{randomNumber};


    Sprite cObject;
    cObject.setPosition(0,0); 
    View camer{FloatRect(0, 0, 800, 600)};
    // camer.zoom(NORMAL_ZOOM);

    
    
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
                    IsNotGenerate = false;                    
               } 

               

                for(auto& p : partes){
                  window.draw(p.spr);                 
                }
                
                for(auto& obj : objects_bottom){
                    window.draw(obj.spr);
                }

                //Essences and items - start
                
                
                for(auto& i : world.essences){
                    i.spr.setTexture(textures[ path_to_img::Player_images[ i.images_numbers[i.counter] ] ]);
                    setSize(i.spr,i.width,i.height);
                    i.behaivor(window);    
                }                       
                                       
                world.player.spr.setTexture(textures[ path_to_img::Player_images[ world.player.images_numbers[world.player.counter] ] ]);
                setSize(world.player.spr,world.player.width,world.player.height);
                world.player.behaivor(window);

                //Essences and items - end


                for(auto& obj : objects_top){
                    window.draw(obj.spr);
                }
                

                camer.setCenter(world.player.spr.getPosition());
                
                window.draw(cObject);
            
                window.setView(camer);


            }else{
                
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