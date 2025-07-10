#include "../include/Input.h"
#include "windows.h"

#ifndef UNICODE
#define UNICODE
#endif 

std::unordered_map<int,bool> Mouse::keys;

std::unordered_map<int,bool> Keyboard::keys;
std::unordered_map<int,bool> Keyboard::PrevKeys;

std::unordered_map<int,bool> WindowEvent::events;

bool Keyboard::IsKeyDown(int vk){
    return Keyboard::keys[vk] && ! Keyboard::PrevKeys[vk]; 
}

bool Keyboard::IsKeyPressed(int vk){
    return Keyboard::keys[vk];
}

bool Keyboard::IsKeyUp(int vk){
    return !Keyboard::keys[vk] && Keyboard::PrevKeys[vk]; 

}

void Keyboard::setKey(int vk,bool pressed){
    Keyboard::keys[vk] = pressed;
}

void Keyboard::update(){
    Keyboard::PrevKeys = Keyboard::keys;
}


void Mouse::setMouseButton(int btn,bool pressed){
    Mouse::keys[btn] = pressed;
}

bool Mouse::IsMousePressed(int btn){
    return Mouse::keys[btn];
}

Vector2 Mouse::getPosition(){
    POINT ps;
    GetCursor();
    ScreenToClient(GetActiveWindow(),&ps);
    return Vector2(ps.x,ps.y);
}



bool WindowEvent::IsWindowEvent(int event_key) {
    return events[event_key];
}

void WindowEvent::setWindowEvent(int event_key, bool happened) {
    events[event_key] = happened;
}

void WindowEvent::reset() {
    events.clear();
}