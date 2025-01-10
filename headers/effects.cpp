#include "effects.h"


HealthBoost::HealthBoost(String icon,float duration,float delay,float impact){
        this->title = "Health boost";
        this->icon_path = icon;
        if(!texture.loadFromFile(icon_path)){
           cerr << "Error in load Health boost icon path" << endl;
        }
        this->sprite.setTexture(texture);
        this->duration = duration;
        this->delay = delay;
        this->impact = impact;
}

void HealthBoost::func(RenderWindow& screen, Player& player) {
    if (player.health < player.Max_health) {
        player.health += this->impact;
    }
}




MagicBoost::MagicBoost(String icon,float duration,float delay,float impact){
        this->title = "Magic boost";
        this->icon_path = icon;
        if(!texture.loadFromFile(icon_path)){
           cerr << "Error in load Health boost icon path" << endl;
        }
        this->sprite.setTexture(texture);
        this->duration = duration;
        this->delay = delay;
        this->impact = impact;
}



void MagicBoost::func(RenderWindow& screen,Player& player) {
        if(player.magic < player.Max_magic)player.magic += this->impact;
}


