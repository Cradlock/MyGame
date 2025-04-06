#include "World.h"
#include "../Locations/location.h"

World::World(){};

World::World(String title,int numMap,vector<Essence> essnc){
    this->title = title;
    this->map = getLocation(numMap);
    this->essences = essnc;
    this->timeOfDay = 0.0f;

    this->red = 0;
    this->green = 0;
    this->blue = 0;
    this->opacity = 0;
};

