#include "resourses.h"






namespace fontes {
    string pixel_font = "fonts/pixel.ttf";
}

namespace path_to_img {
    string bg1 = "images/System/Backgrounds/bg1.jpeg";  
    string bg2 = "images/System/Backgrounds/bg2.jpeg";  
    string bg3 = "images/System/Backgrounds/bg3.jpeg";  
   
 
    unordered_map<int,string> Player_images = {
       {1 , "images/Essence/Player/GG.png"},
       {2 , "images/Essence/Player/GG_right1.png"},
       {3 , "images/Essence/Player/GG_right2.png"},
       {4 , "images/Essence/Player/GG_right3.png"},
       {5 , "images/Essence/Player/GG_right4.png"}
    };


   unordered_map<int,string> Essence_images = {};

   

    unordered_map<int,string> Objects = {
        {0,"Void"},
        {1,"images/Objects/Block/Average/tree001.png"},
        {2,"images/Objects/Block/Bottom/grass.png"},
        {3,"images/Objects/Block/Bottom/mushroom001.png"},
        {4,"images/Objects/Block/Bottom/mushrooms001.png"},
    };
   

   namespace PartWorld{
    vector<string> blockes = {"Void",
        "images/Objects/PartWorld/ground.jpg",
        "images/Objects/PartWorld/gravel.png",
        "images/Objects/PartWorld/grass.jpg",
        "images/Objects/PartWorld/stone.jpg",
        "images/Objects/PartWorld/cobblestone.jpg",
        "images/Objects/PartWorld/stoneTile.jpg",
        "images/Objects/PartWorld/Myceli.jpg",
        "images/Objects/PartWorld/OverGrownGrass.jpg",
        "images/Objects/PartWorld/OverGrownMyceli.jpg",
        "images/Objects/PartWorld/ShalloWater.jpg",
        "images/Objects/PartWorld/MediumWater.png",
        "images/Objects/PartWorld/DeepWater.jpg",
        "images/Objects/PartWorld/Dirt.jpg",
        "images/Objects/PartWorld/swamp.jpg",
        "images/Objects/PartWorld/lava.jpg",
        "images/Objects/PartWorld/sand.jpg",
        "images/Objects/PartWorld/magma.jpg",
        "images/Objects/PartWorld/darkWater.png",
        
    
    };

   }
}

