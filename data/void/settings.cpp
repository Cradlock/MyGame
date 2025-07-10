#include "settings.h"
#include "./pack.h"






SettingManager::SettingManager(){
    this->setting_path = fs::path(Resources::path_setting);
    
    ifstream file(this->setting_path);
    if(!file.is_open()){
        ErrorNotiffication("Can not open setting config","Setting.cpp -> SettingManager");
    }
    file >> this->setting_json;

    file.close();
}


void SettingManager::init(){
   

}



