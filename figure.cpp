#include "figure.h"
#include "game.h"

#include <iostream>
#include <QDebug>

using namespace std;

extern Game *game;

Figure::Figure(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/slike/Untitled.png"));
    _owner = "NONE";
}

void Figure::setOwner(QString owner){
    _owner = owner;

    if(owner == "PLAYER1")
        setPixmap(QPixmap(":/slike/aaa.png"));
    else if(owner == "PLAYER2")
        setPixmap(QPixmap(":/slike/coin.png"));
    else if(owner == "NONE")
        setPixmap(QPixmap(":/slike/Untitled.png"));
    else
        setPixmap(QPixmap(":/slike/que.png"));
}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(game->ind == 2)
        klikMrezni();
    else
        leviklik();
}

void Figure::leviklik(){
    if(game->whosTurn == getOwner() && game->f == NULL){
        game->pickUpFigure(this);
        koord(this);
        game->f->setZValue(100);

        if(game->checkIfKonflikt(game->whosTurn)){
            if(this->hasConf())
                game->validan(this, this->getX(), this->getY());
            else
                return;
        }
        else
           game->validan(this, this->getX(), this->getY());
    }
    else if(getOwner() == "h"){
        koord(this);

        if(game->f)
            game->placeFigure(this);
        else
            qDebug() << "ne prolazi";

        for(int i = 0; i < game->table->figures.length(); i++){
            if(game->table->figures[i]->getOwner() == "h")
                game->table->figures[i]->setOwner("NONE");

            if(notEmpty(game->table->figures[i]) && game->table->figures[i]->getOwner() == "NONE")
                    game->scene->removeItem(game->table->figures[i]);
        }

        game->end();
        game->setWhosTurn();
    }
    else{

    }
}

void Figure::klikMrezni(){
    if(game->whosTurn==getOwner() && getOwner() == "PLAYER1" && game->f == NULL){
        game->pickUpFigure(this);
        koord(this);
        game->f->setZValue(100);

        game->poruka.append(QString::number(game->f->getX()));
        game->poruka.append(",");
        game->poruka.append(QString::number(game->f->getY()));
        game->poruka.append(",");

        if(game->checkIfKonflikt(game->whosTurn)){
            if(this->hasConf())
                game->validan(this, this->getX(), this->getY());
            else
                return;
        }
        else
           game->validan(this, this->getX(), this->getY());
    }
    else if(getOwner() == "h"){
        koord(this);

        if(game->f)
            game->placeFigure(this);
        else
            qDebug() << "ne prolazi";

        game->poruka.append(QString::number(this->getX()));
        game->poruka.append(",");
        game->poruka.append(QString::number(this->getY()));

        for(int i = 0; i < game->table->figures.length(); i++){
            if(game->table->figures[i]->getOwner() == "h")
                game->table->figures[i]->setOwner("NONE");

            if(notEmpty(game->table->figures[i]) && game->table->figures[i]->getOwner() == "NONE")
                game->scene->removeItem(game->table->figures[i]);
        }

        game->end();

        game->server->socket->write(game->poruka.toUtf8());
        //game->server->socket->flush();

        game->setWhosTurn();
    }
    else{
    }
}

QString Figure::getOwner(){
    return _owner;
}

void Figure::koord(Figure *f){
    int k = f->x();
    int j = f->y();

    setX(k);
    setY(j);
}

bool Figure::notEmpty(Figure *f){
    for(int i = 0; i < game->table->figures.length(); i++)
        if((game->table->figures[i]->pos() == f->pos()) && (game->table->figures[i]->getOwner() != f->getOwner()))
            return true;
    return false;
}

void Figure::setX(int x){
    k = x;
}

void Figure::setY(int y){
    j = y;
}

int Figure::getX(){
    return k;
}

int Figure::getY(){
    return j;
}

int Figure::hasConf(){
    if((this->getOwner() == "PLAYER1" && !game->konflikt1(this->getX() - 74, this->getY() - 74)
            && game->free(this->getX() - 148, this->getY() - 148))
       || (this->getOwner() == "PLAYER1" && !game->konflikt1(this->getX() + 74, this->getY() - 74)
            && game->free(this->getX() + 148, this->getY() - 148)))
        return 1;
    if((this->getOwner() == "PLAYER1" && this->isQueen && !game->konflikt1(this->getX() - 74, this->getY() + 74))
        || (this->getOwner() == "PLAYER1" && this->isQueen && !game->konflikt1(this->getX() + 74, this->getY() + 74)))
        return 1;

    if((this->getOwner() == "PLAYER2" && !game->konflikt2(this->getX() - 74, this->getY() + 74)
            && game->free(this->getX() - 148, this->getY() + 148))
       || (this->getOwner() == "PLAYER2" && !game->konflikt2(this->getX() + 74, this->getY() + 74)
            && game->free(this->getX() + 148, this->getY() + 148)))
        return 1;
    if((this->getOwner() == "PLAYER2" && this->isQueen && !game->konflikt2(this->getX() - 74, this->getY() - 74))
        || (this->getOwner() == "PLAYER2" && this->isQueen && !game->konflikt2(this->getX() + 74, this->getY() - 74)))
        return 1;
    return 0;
}
