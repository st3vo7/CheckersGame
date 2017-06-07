#include "figure.h"
#include "game.h"

extern Game * game;

Figure::Figure(QGraphicsItem* parent):QGraphicsPixmapItem(parent){
 setPixmap(QPixmap(":/slike/Untitled.png"));
 _owner="NONE";

}
void Figure::setOwner(QString owner){
    _owner=owner;
    if(owner=="PLAYER1"){
        setPixmap(QPixmap(":/slike/aaa.png"));

    }

    else if(owner=="PLAYER2"){
        setPixmap(QPixmap(":/slike/coin.png"));
    }

    else if(owner=="NONE") {
        setPixmap(QPixmap(":/slike/Untitled.png"));
    }
    else
        setPixmap(QPixmap(":/slike/que.png"));
}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent *event){
    cukic();

}
/*void Figure::probna(){
    if(game->whosTurn==getOwner() && game->f==NULL){
    game->pickUpFigure(this);
    koord(this);

    if(game->checkIfKonflikt(game->whosTurn)){
        if(this->hasConf()){
            game->postaviH(this, this->getX(), this->getY());
        }
        else{
            return;
        }
    }
    else
       game->postaviH(this, this->getX(), this->getY());
    }

}*/

void Figure::cukic()
{
    if(game->whosTurn==getOwner() && game->f==NULL){

        game->pickUpFigure(this);
        koord(this);
        game->f->setZValue(100);



        if(game->ind == 2){ // Ako je mrezno, pamtim koordinate figure koja se pomera
            game->poruka.append(QString::number(game->f->getX()));
            game->poruka.append(",");
            game->poruka.append(QString::number(game->f->getY()));
            game->poruka.append(",");
        }


        if(game->checkIfKonflikt(game->whosTurn)){
            if(this->hasConf()){
                game->validan(this, this->getX(), this->getY());
            }
            else{
                return;
            }
        }
        else
           game->validan(this, this->getX(), this->getY());

    }
    else if(getOwner()=="h"){
        koord(this);
        cout<<"X koordinata polja gde sam je smestio:"<<this->getX()<<" i Y: "<<this->getY()<<endl;
        if(game->f){
            game->placeFigure(this);
        }
        else
            cout<<"ne prolazi";


        if(game->ind == 2){ // Pamtim i koordinate polja na koje je figura pomerena
            game->poruka.append(QString::number(this->getX()));
            game->poruka.append(",");
            game->poruka.append(QString::number(this->getY()));
        }


        for(int i=0;i<game->table->figures.length();i++){
            if(game->table->figures[i]->getOwner()=="h")
                game->table->figures[i]->setOwner("NONE");
                if(notEmpty(game->table->figures[i]) && game->table->figures[i]->getOwner()=="NONE")
                    game->scene->removeItem(game->table->figures[i]);
        }

        game->end();

        if(game->ind == 2){ // Sve se pise u soket servera i flush() to odmah salje klijentu
            game->server->socket->write(game->poruka.toUtf8());
            game->server->socket->flush();
            qDebug() << game->ind;
        }

        game->setWhosTurn();

    }

    else{

    }

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
    if((this->getOwner()=="PLAYER1" && this->isQueen && !game->konflikt1(this->getX()-74,this->getY()+74))
        || (this->getOwner()=="PLAYER1" && this->isQueen && !game->konflikt1(this->getX()+74,this->getY()+74)))
        return 1;

    if((this->getOwner()=="PLAYER2" && !game->konflikt2(this->getX()-74,this->getY()+74)
            && game->free(this->getX()-148,this->getY()+148))
       || (this->getOwner()=="PLAYER2" && !game->konflikt2(this->getX()+74,this->getY()+74)
            && game->free(this->getX()+148,this->getY()+148)))
        return 1;
    if((this->getOwner()=="PLAYER2" && this->isQueen && !game->konflikt2(this->getX()-74,this->getY()-74))
        || (this->getOwner()=="PLAYER2" && this->isQueen && !game->konflikt2(this->getX()+74,this->getY()-74)))
        return 1;
    return 0;
}


void Figure::setX(int x){
    k=x;
}
