#include "Tools.h"

TextObj::TextObj(string& f,int size,Color color){
    if(!font_family.loadFromFile(f)){
        cerr << "Error in load font" + f << endl;
    }
    this->font_size = size;
    this->font_color = color;
    text.setFont(font_family);
}

void TextObj::Setter(string title,float x,float y){
    text.setString(title);
    text.setPosition(x,y);
}

void TextObj::draw(RenderWindow& window){
    text.setCharacterSize(this->font_size);
    text.setFillColor(this->font_color);
    window.draw(this->text);
}


void TextObj::setSize(int s){
    this->font_size = s;
}

void TextObj::setColor(Color c){
    this->font_color = c;
}


