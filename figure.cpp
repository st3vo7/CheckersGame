#include "figure.h"
#include "game.h"

extern Game * game;

Figure::Figure(QGraphicsItem* parent):QGraphicsPixmapItem(parent){
 setPixmap(QPixmap(":/slike/Untitled.png"));
 _owner="NONE";

}
void Figure::setOwner(QString owner){
    _owner=owner;
    if(owner=="PLAYER1")
        setPixmap(QPixmap(":/slike/ponovo.png"));
    else if(owner=="PLAYER2")
        setPixmap(QPixmap(":/slike/ssss.png"));
    else if(owner=="NONE") {
        setPixmap(QPixmap(":/slike/Untitled.png"));
    }
    else
        setPixmap(QPixmap(":/slike/spirala.png"));
}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent *event){
       if(game->whosTurn==getOwner() && game->f==NULL){

           game->pickUpFigure(this);
           koord(this);
           if(game->checkIfKonflikt(game->whosTurn)){
               if(this->hasConf()){
                   game->validan(this, this->getX(), this->getY());
               }
               else
                   return;
           }
           else
              game->validan(this, this->getX(), this->getY());

       }
       else if(getOwner()=="h"){
           if(game->f)
               game->placeFigure(this);
           for(int i=0;i<game->table->figures.length();i++){
               if(game->table->figures[i]->getOwner()=="h")
                   game->table->figures[i]->setOwner("NONE");
                   if(notEmpty(game->table->figures[i]) && game->table->figures[i]->getOwner()=="NONE")
                       game->scene->removeItem(game->table->figures[i]);
           }
           /*
           if(game->f->hasConf() && game->eaten){
               game->f=NULL;
               cout<<"proba"<<endl;
               return;
            }

           cout<<game->f->getX();
           */
           game->f=NULL;
           game->setWhosTurn();

       }

       else;
}


QString Figure::getOwner(){
    return _owner;
}

void Figure::koord(Figure *f){
    int k=f->x();
    int j=f->y();
    setX(k);
    setY(j);

}

bool Figure::notEmpty(Figure *f){
    for(int i=0;i<game->table->figures.length();i++){
        if((game->table->figures[i]->pos()==f->pos()) && (game->table->figures[i]->getOwner()!=f->getOwner()))
            return true;
    }
    return false;
}

void Figure::setY(int y){
    j=y;
}

int Figure::getX(){
    return k;
}


int Figure::getY(){
    return j;
}

int Figure::hasConf(){
    if((this->getOwner()=="PLAYER1" && !game->konflikt1(this->getX()-74,this->getY()-74)
            && game->free(this->getX()-148,this->getY()-148))
       || (this->getOwner()=="PLAYER1" && !game->konflikt1(this->getX()+74,this->getY()-74)
            && game->free(this->getX()+148,this->getY()-148)))
        return 1;
    if((this->getOwner()=="PLAYER2" && !game->konflikt2(this->getX()-74,this->getY()+74)
            && game->free(this->getX()-148,this->getY()+148))
       || (this->getOwner()=="PLAYER2" && !game->konflikt2(this->getX()+74,this->getY()+74)
            && game->free(this->getX()+148,this->getY()+148)))
        return 1;
    return 0;
}

void Figure::setX(int x){
    k=x;
}
