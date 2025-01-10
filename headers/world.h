#ifndef WORLD_H
#define WORLD_H


#include <SFML/Graphics.hpp>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>  
#include "baseClass.h" 

using namespace sf;
using namespace std;


struct decoration_point
{
    int objType;
    float x;
    float y;
};


class World{
private:
     Sprite sprite;
     Texture texture;
     int width,height;
     vector<string> decorates_pathes;
     vector<Texture> decorates_list;
     vector<unique_ptr<Boundary>> unlife_objects;
     vector<unique_ptr<Essence>> life_objects;
     vector<unique_ptr<Item>> item_lists;
     vector<decoration_point> objects;
public:
    World(const string& FilePath,vector<string> c);
    float getWidth() const;
    float getHeight() const;
    void generate(int numObjects);
    void draw(RenderWindow &window);
};

extern RenderWindow window;
extern World world;

#endif