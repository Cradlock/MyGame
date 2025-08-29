#pragma once

#ifndef UNICODE
#define UNICODE
#endif 


#include "windows.h"
#include "tchar.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;




class PanarchonWindow{
private:
// данные IN
HINSTANCE hinstance; HINSTANCE prevInstance; LPSTR cmdLine; int showCmd;

// Запрет копирования
PanarchonWindow(const PanarchonWindow&) = delete;
PanarchonWindow& operator=(const PanarchonWindow&) = delete;

// Запрет Перемешения
PanarchonWindow(PanarchonWindow&&) = delete;
PanarchonWindow& operator=(PanarchonWindow&&) = delete;

    int state_window;
    WNDCLASSEX info;
    HWND window;
    int width;
    int height;    
    
    static LRESULT CALLBACK Interactions( HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam );
    
   
public:
bool isInit;
const wchar_t* className;
const wchar_t* szTitle;

PanarchonWindow(HINSTANCE h, HINSTANCE hP, LPSTR l, int n,const wchar_t* t);
PanarchonWindow();
HWND getMainWindow();
inline pair<int,int> getSizeWindow(){

#ifdef _WIN32
RECT rect;
if(GetClientRect(this->window,&rect)){
   int width = rect.right - rect.left;
   int height = rect.bottom - rect.top;
   return {width,height};
}else{
    return {0,0};
}

#endif 


#ifdef __linux__
    ::Display* display = XOpenDisplay(nullptr);
    if (!display) {
        return {0, 0};
    }

    XWindowAttributes attributes;
    if (XGetWindowAttributes(display, this->window, &attributes) == 0) {
        XCloseDisplay(display);
        return {0, 0};
    }

    int width = attributes.width;
    int height = attributes.height;

    XCloseDisplay(display);
    return {width, height};
    
#endif 


}
inline HINSTANCE gethInstance(){return this->hinstance;};

void showWindow();
void updateWindow();
void msgLoop();


};





