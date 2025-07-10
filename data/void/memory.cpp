#include "memory.h"
#include "pack.h"

MemoryManager::MemoryManager(){}



void MemoryManager::init(){
    fs::path mods_path = fs::path(Resources::path_mods);
    fs::path system_path  = fs::path(Resources::path_system);


    if(!fs::exists(mods_path) ){
        fs::create_directory(mods_path);     
    }

    if(!fs::exists(system_path)){
        ErrorNotiffication("Not found system catalog","Memory.cpp ");
        exit(EXIT_FAILURE);
    }


    

}