#include "../include/Window.h"
#include "../include/Input.h"
#include "../../pack.h"

#ifndef UNICODE
#define UNICODE
#endif 


PanarchonWindow::PanarchonWindow() : isInit(false){};

// default constructor
PanarchonWindow::PanarchonWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd,const wchar_t* title)
:
isInit(true),
width(500),height(100),className(L"Default class name"),szTitle(title),
hinstance(hInstance),prevInstance(hPrevInstance),cmdLine(lpCmdLine),showCmd(nShowCmd)

{
    
    this->width = GetSystemMetrics(SM_CXSCREEN);
    this->height = GetSystemMetrics(SM_CYSCREEN);
    this->state_window = nShowCmd;
    
    this->info.cbSize = sizeof(WNDCLASSEX);
    this->info.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    this->info.lpfnWndProc = this->Interactions; 
    this->info.cbClsExtra = 0;
    this->info.cbWndExtra = 0;
    this->info.hInstance = hInstance;
    this->info.hIcon = LoadIcon(info.hInstance, IDI_APPLICATION);
    this->info.hCursor = LoadCursor(NULL,IDC_ARROW);
    this->info.hbrBackground = (HBRUSH)(COLOR_BACKGROUND+1); 
    this->info.lpszMenuName = NULL;
    this->info.lpszClassName = className;
    this->info.hIconSm = LoadIcon(info.hInstance, IDI_APPLICATION);
    
    if(!RegisterClassEx(&this->info)){
       ErrorNotiffication("Call to reigister failed","Abyss/Window.cpp");
       exit(EXIT_FAILURE);
    }

    this->window = CreateWindowEx(
        WS_EX_APPWINDOW,
        this->className,
        this->szTitle,
        WS_POPUP,
        CW_USEDEFAULT,CW_USEDEFAULT,
        width,height,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if(!this->window){
      ErrorNotiffication("Call to create window failed","abyss/Window.cpp");
      exit(EXIT_FAILURE);
    }

};

void PanarchonWindow::msgLoop(){
  MSG msg;
  PeekMessage(&msg,NULL,0,0,PM_REMOVE);
  TranslateMessage(&msg);
  DispatchMessage(&msg);
}

void PanarchonWindow::showWindow(){
    ShowWindow(this->window,this->state_window);
}

void PanarchonWindow::updateWindow(){
  UpdateWindow(this->window);
  
}



HWND PanarchonWindow::getMainWindow(){
  return this->window; 
}

LRESULT PanarchonWindow::Interactions(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam){
 
  
  switch (message)
    {
      case WM_DESTROY:
          WindowEvent::setWindowEvent(EVENT_CLOSE, true);
          PostQuitMessage(0);
          return 0;

      case WM_PAINT:
          WindowEvent::setWindowEvent(EVENT_PAINT, true);
          break;

      case WM_SETFOCUS:
          WindowEvent::setWindowEvent(EVENT_FOCUS_GAINED, true);
          break;

      case WM_KILLFOCUS:
          WindowEvent::setWindowEvent(EVENT_FOCUS_LOST, true);
          break;

      case WM_SIZE:
          WindowEvent::setWindowEvent(EVENT_RESIZE, true);
          break;

      case WM_DROPFILES:
          
          WindowEvent::setWindowEvent(EVENT_DROPFILE,true);
          break;

      case WM_KEYDOWN:
      Keyboard::setKey((int)wParam,true);
      break;
      case WM_KEYUP:
      Keyboard::setKey((int)wParam,false);
      break;

      case WM_LBUTTONDOWN:
      Mouse::setMouseButton( VK_LBUTTON,true );
      break;
      case WM_RBUTTONDOWN:
      Mouse::setMouseButton( VK_RBUTTON,true );
      break;
    
      case WM_LBUTTONUP:
      Mouse::setMouseButton( VK_LBUTTON,false );
      break;
      case WM_RBUTTONUP:
      Mouse::setMouseButton( VK_RBUTTON,false );
      break;

    default:
      return DefWindowProc(hWnd,message,wParam,lParam);
      break;
    }


    return 0;
}


