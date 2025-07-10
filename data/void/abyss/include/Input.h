#pragma once

#ifndef UNICODE
#define UNICODE
#endif 

#include <unordered_map>


using Vector2 = std::pair<float,float>;

class Keyboard{

public:
    static bool IsKeyPressed(int vk);
    static bool IsKeyUp(int vk);
    static bool IsKeyDown(int vk);

    static void setKey(int vk,bool pressed);
    static void update();
private:
static std::unordered_map<int,bool> keys;
static std::unordered_map<int,bool> PrevKeys;

};

class Mouse{
public:
static void setMouseButton(int btn,bool pressed);
static bool IsMousePressed(int btn);
static Vector2 getPosition();


private:
static std::unordered_map<int,bool> keys;

};


enum WindowEvents {
    EVENT_CLOSE = 1,
    EVENT_RESIZE = 2,
    EVENT_FOCUS_GAINED = 3,
    EVENT_FOCUS_LOST = 4,
    EVENT_PAINT = 5,
    EVENT_DROPFILE = 6,
};

class WindowEvent{
private:
static std::unordered_map<int,bool> events;  

public:
static bool IsWindowEvent(int event_key);
static void setWindowEvent(int event_key,bool happened);
static void reset();
};

class Timer{

};