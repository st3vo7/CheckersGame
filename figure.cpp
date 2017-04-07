#include "figure.h"

Figure::Figure(QGraphicsItem* parent):QGraphicsPixmapItem(parent){

 setPixmap(QPixmap(":/slike/ponovo.png"));

}
void Figure::setOwner(QString owner){
    _owner=owner;
    if(owner=="PLAYER1");
    else if(owner=="PLAYER2")
        setPixmap(QPixmap(":/slike/j.png"));
    else
        setPixmap(QPixmap());

}
