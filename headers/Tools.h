#ifndef TOOLS_H
#define TOOLS_H

#include "resourses.h"

class TextObj{
private:
    Text text;
    Font font_family;
    int font_size;
    Color font_color;

public:  

    TextObj(string& f,int size,Color color);
    
    void Setter(string text,float x,float y);

    void draw(RenderWindow& window);

    void setSize(int s);

    void setColor(Color c);
};



int random(long long int start,long long int end);






#endif