#include "World.h"
#include "../Locations/location.h"



World::World(String title,matrixMap map,matrixMap objects){
    this->title = title;
    this->map = map;
    this->mapObj = objects;
};

