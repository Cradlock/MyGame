#ifndef SETTINGS_H
#define SETTINGS_H


#include "base.h"
#include "ui.h"




class SettingManager{
private:
   fs::path setting_path;  
   json setting_json;
   

public:  
    SettingManager();

    void init();


    inline int getFps(){ return this->setting_json["fps"].get<int>(); };


};





#endif