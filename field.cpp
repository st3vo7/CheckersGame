#include "field.h"

Field::Field(int x, int y){
    _x=x;
    _y=y;
}

Field::Field(){
}

int Field::getx(){
    return _x;
}

int Field::gety(){
    return _y;
}

void Field::setx(int x){
    _x = x;
}

void Field::sety(int y){
    _y = y;
}
