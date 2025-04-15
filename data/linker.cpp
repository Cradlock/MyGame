#include "linker.h"


unordered_map<int,Object> localObjects;
vector<shared_ptr<Light>> localLight;

vector<int> objects_top;
vector<int> objects_bottom;

unordered_map<string,Texture> textures;
vector<PartWorld> partes;

vector<Item> items;

vector<Essence> essences;

vector<Projectile> projectiles;


void init_db(){

// Essences
    
    init_essence_lambdas();


//Objects 
    init_objects_lambdas();



//Items

    init_items_lambdas();

};