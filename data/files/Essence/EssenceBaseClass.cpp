#include "EssenceBaseClass.h"

Resistance::Resistance() : magic(Magic()),energy(Energy()),immunity(Bio()),psycho(0),soul(0)  {};

Resistance::Resistance(Magic mag,Physic phy,Energy ene,Bio immu,float pshyc,float soul) : magic(mag),energy(ene),immunity(immu),psycho(pshyc),soul(soul) {};

Property::Property() : value(0),count(0),max(0),time(0) {};

Property::Property(float v,float c,float m,float t) : value(v),count(c),max(m),time(t) {};


Essence::Essence(){};

Essence::Essence(int pk,float x,float y,float w,float h,string name,string description,string group_name,
           int sight,int hearing,
           vector<int> imgs_numbrs,
           Resistance rest,
           float strength, float agility,float mana_control,float mana_reaction,float charisma,float max_temperature,float min_temp,float MinAir,
           Property health,Property mana,Property stamina,Property mind,Property speed,
           float int_soul,float hun,float th,
           int beh_id
    ) {
        this->spr.setPosition(Vector2f(x,y));
        this->width = w;
        this->height = h;
        this->id = pk;
        this->name = name;
        this->description = description;
        this->GroupName = group_name;
        this->sight = sight;
        this->hearing = hearing;
        this->images_numbers = imgs_numbrs;
        this->resistance = rest;
        this->strength = strength;
        this->agility = agility;
        this->mana_control = mana_control;
        this->mana_reaction = mana_reaction;
        this->charisma = charisma;
        this->max_temperature = max_temperature;
        this->min_temperature = min_temp;
        this->MinAir = MinAir;
        this->health = health;
        this->mana = mana;
        this->stamina = stamina;
        this->mind = mind;
        this->speed = speed;
        this->hunger_min = hun;
        this->thirst_min = th;
        this->integrity_soul = int_soul;
        this->behavior_id = beh_id;

    };

void Essence::behaivor(RenderWindow& window){
    if(this->behavior_id){
       EssencesLambdas[behavior_id](this,window);
    }
}


unordered_map<int,function<void(Essence*,RenderWindow&)>> EssencesLambdas = {
    {1,[](Essence* self,RenderWindow& window){
        
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            self->counter = 1;
            self->spr.move(0, -self->speed.value);  
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            self->counter = 2;
            self->spr.move(0, self->speed.value);  
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            self->counter = 3;
            self->spr.move(-self->speed.value, 0);  
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            self->counter = 4;
            self->spr.move(self->speed.value, 0);  
        }
        
        window.draw(self->spr);
    }} 
};


Essence PLAYER = {1, 0,0, 5,15, 
        "Wan",
        "????????????????????????????",
        "None",
        250,100, 
        { 1,2,3,4 } ,
        Resistance{ Magic(),Physic(),Energy(),Bio(),0.f,15.f },
        25.f,
        10.f,
        5.f,
        25.f,
        5.f,
        40.f,
        0.f,
        100.f,
        Property{50.f,1,100,0.1},
        Property{50.f,1,100,0.1},
        Property{50.f,1,100,0.1},
        Property{50.f,1,100,0.1},
        Property{5,0,15,0.1},
        89.f,0.f,0.f,
        1};


unordered_map<int,Essence> GLOBAL_ESSENCES_list = {};