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
#include <thread>  
#include <chrono>
#include <utility>
#include <stdexcept>

#define Title "Nexus"

using namespace sf;
using namespace std;

using matrixMap = vector<vector<int>>;


extern int WIDTH;
extern int HEIGHT;
extern float NORMAL_ZOOM;
extern float NORMAL_SPEED;
extern float standart_size;

extern float DAY_LENGTH;
extern float DELTA_TIME;
extern const float timeSpeed;

extern int experience;

extern unsigned int counterID;

extern RenderWindow window;

void setSize(Sprite& s,float w,float h);


bool OnCursor(Text& b,Vector2f mousePos);

void OnCursor(Text& b,bool& t,Vector2f mousePos);

void SetWhite(Text& t);

void SetBlack(Text& t);




#endif