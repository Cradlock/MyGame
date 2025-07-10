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
inline HINSTANCE gethInstance(){return this->hinstance;};
void showWindow();
void updateWindow();
void msgLoop();


};





