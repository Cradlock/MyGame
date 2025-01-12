#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <windows.h>
#include <cwchar>  
#include <random>

#define Title "Nexus"

using namespace sf;
using namespace std;

using matrixMap = vector<vector<int>>;


extern int WIDTH;
extern int HEIGHT;
extern float NORMAL_ZOOM;
extern float NORMAL_SPEED;
extern float standart_size;


extern int experience;


extern RenderWindow window;


auto renderObject = [ ptrWindow = &window ]( auto&&... argc ){
     (ptrWindow->draw(std::forward<decltype(argc)>(argc)), ...);
};


void setSize(Sprite& s,float w,float h);


#endif