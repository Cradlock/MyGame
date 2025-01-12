#include "World.h"
#include "../Locations/location.h"

World::World(){};

World::World(String title,int numMap,vector<Essence> essnc){
    this->title = title;
    this->map = getLocation(numMap);
    this->essences = essnc;
};

