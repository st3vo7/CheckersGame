#include "field.h"


Field::Field(int x, int y){
    _x=x;
    _y=y;
}
Field::Field(){}
int Field::getx(){
    return _x;
}
int Field::gety(){
    return _y;
}
