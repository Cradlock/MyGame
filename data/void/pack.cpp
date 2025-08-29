#include "pack.h"



void ErrorNotiffication(const char* message,string file_name){
    
    char buffer[255];
    
    snprintf(buffer, sizeof(buffer) , "Error: %s",message);
    
    MessageBoxA(NULL,message, ("Error in "s + file_name).c_str() ,MB_ICONERROR | MB_OK);

}


void ErrorNotiffication(string message,string file_name){
    
    char buffer[255];
    
    snprintf(buffer, sizeof(buffer) , "Error: %s",message);
    
    MessageBoxA(NULL,message.c_str(), ("Error in "s + file_name).c_str() ,MB_ICONERROR | MB_OK);

}

