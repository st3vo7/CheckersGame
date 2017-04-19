#include "game.h"
#include "table.h"
#include <QBrush>
#include <QImage>
#include "button.h"
#include <QFont>
#include <QString>
#include <QGraphicsTextItem>
#include <iostream>

using namespace std;


Game::Game(QWidget* parent){
    //podesavamo ekran

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(600,600);

    //podesavamo scenu
    scene= new QGraphicsScene();
    scene->setSceneRect(0,0,600,600);
    setScene(scene);
    f=NULL;

}

void Game::start(){
    //Ocistimo ekran
    scene->clear();
    scene->setBackgroundBrush(QBrush(QImage(":/slike/chessboardtessellation.jpg")));
    table=new Table();

}

void Game::displayMainMenu(){
   //pravimo naslov
    scene->setBackgroundBrush(QBrush(QImage(":/slike/492555-43-1000-fbf6681ace-1488812954.jpg")));
    QGraphicsTextItem* title=new QGraphicsTextItem(QString("Dame (Checkers)"));
    QFont titleFont("comic sans",50);
    title->setFont(titleFont);
    int txPos=this->width()/2-title->boundingRect().width()/2;
    int tyPos=100;
    title->setPos(txPos,tyPos);
    scene->addItem(title);

    //pravimo play dugme

    Button* play=new Button(QString("1 na 1"));
    int bxPos=this->width()/2- play->boundingRect().width()/2;
    int byPos=200;
    play->setPos(bxPos,byPos);
    connect(play,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(play);

    // pravimo quit dugme
    Button* help=new Button(QString("Protiv kompjutera"));
    int hxPos=this->width()/2-help->boundingRect().width()/2;
    int hyPos=275;
    help->setPos(hxPos,hyPos);
    //DODATI KONEKCIJU: connect(quit,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(help);

    Button* quit2=new Button(QString("Preko mreze"));
    int q2xPos=this->width()/2-quit2->boundingRect().width()/2;
    int q2yPos=350;
    quit2->setPos(q2xPos,q2yPos);
     // DODATI KONEKCIJU: connect(quit,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quit2);

    Button* quit=new Button(QString("Zurim, cao!"));
    int qxPos=this->width()/2-quit->boundingRect().width()/2;
    int qyPos=425;
    quit->setPos(qxPos,qyPos);
     connect(quit,SIGNAL(clicked()),this,SLOT(close()));
     scene->addItem(quit);
}

void Game::mouseMoveEvent(QMouseEvent *event){
    if(f)
        f->setPos(event->pos());
    QGraphicsView::mouseMoveEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::RightButton){
     if(f){
        f->setPos(orignalPos);
        for(int i=0;i<table->figures.length();i++){
         if(table->figures[i]->getOwner()=="h")
            table->figures[i]->setOwner("NONE");
            if(f->notEmpty(table->figures[i]) && table->figures[i]->getOwner()=="NONE")
                scene->removeItem(table->figures[i]);
        }
        f=NULL;
        return;
     }
    }
    QGraphicsView::mousePressEvent(event);
}


void Game::pickUpFigure(Figure *f1){
    if(f==NULL){
        f=f1;
        orignalPos=f1->pos();
        return;
    }
}

void Game::placeFigure(Figure *f1){
    for(int i=0;i<table->figures.length();i++){
        if(table->figures[i]->pos()==f1->pos())
            scene->removeItem(table->figures[i]);
    }
    f->setPos(f1->pos());
    table->figures.removeAll(f1);
    table->figures.append(f);

    scene->removeItem(f1);
    for(int i=0;i<table->figures.length();i++){
        if(table->figures[i]->eaten && table->figures[i]->getOwner()!="NONE"){
            table->figures[i]->setOwner("NONE");
            table->figures[i]->eaten=false;
            cout<<"obrisano!"<<endl;
            eaten=true;
        }
    }
}

void Game::move(int i, int j){
    Figure* f1=new Figure();
    f1->setOwner("h");
    f1->setPos(i,j);
    scene->addItem(f1);
    table->figures.append(f1);
}

bool Game::free(int i, int j){
    if(i<4 || i>522 || j<4 || j>522)
        return false;
    for(int k=0;k<table->figures.length();k++){
        table->figures[k]->koord(table->figures[k]);
        if(table->figures[k]->getX()==i &&
           table->figures[k]->getY()==j){
           if(table->figures[k]->getOwner()=="PLAYER1" ||
               table->figures[k]->getOwner()=="PLAYER2"){

                return false;
           }
        }
    }
     return true;
}

int Game::eatLU(Figure* f,int i, int j, int k){
    if(k==-1)
        return 0;
   if(free(i-74,j-74)){
       move(i-74,j-74);
       mark(i,j);
       return 1;
    }
    return 0;
}

int Game::eatRU(Figure* f,int i, int j, int k){
    if(k==-1)
        return 0;
  if(free(i+74,j-74)){
      move(i+74,j-74);
      mark(i,j);
      return 1;
  }
  return 0;
}
int Game::eatLD(Figure* f,int i, int j, int k){
    if(k==-1)
        return 0;
   if(free(i-74,j+74)){
       move(i-74,j+74);
       mark(i,j);
       return 1;
   }
   return 0;
}

int Game::eatRD(Figure* f,int i, int j, int k){
if(k==-1)
    return 0;
  if(free(i+74,j+74)){
      move(i+74,j+74);
      mark(i,j);
      return 1;
  }
    return 0;
}

int Game::konflikt1(int i, int j){
    if(i<=4 || i>=522 || j<=4 || j>=522)
        return -1;
    for(int k=0;k<table->figures.length();k++){
        table->figures[k]->koord(table->figures[k]);
        if(table->figures[k]->getX()==i &&
           table->figures[k]->getY()==j){
           if(table->figures[k]->getOwner()=="PLAYER2"){
                return 0;
           }
        }
    }
    return -1;
}


int Game::konflikt2(int i, int j){
    if(i<=4 || i>=522 || j<=4 || j>=522)
        return -1;
    for(int k=0;k<table->figures.length();k++){
        table->figures[k]->koord(table->figures[k]);
        if(table->figures[k]->getX()==i &&
           table->figures[k]->getY()==j){
           if(table->figures[k]->getOwner()=="PLAYER1"){
                return 0;
           }
        }
     }
    return -1;
}

void Game::mark(int i, int j){
    for(int k=0;k<table->figures.length();k++){
        if(table->figures[k]->getX()==i && table->figures[k]->getY()==j){
                table->figures[k]->eaten=true;
        }
    }
}

QString Game::otherPlayer(){
    if(whosTurn=="PLAYER1")
        return "PLAYER2";
    if(whosTurn=="PLAYER2")
        return "PLAYER1";
}

int Game::checkIfKonflikt(QString turn){
    if(turn=="PLAYER1"){
        for(int k=0;k<table->figures.length();k++){
           if(table->figures[k]->getOwner()=="PLAYER1")
               if((!konflikt1(table->figures[k]->getX()-74,table->figures[k]->getY()-74) && free(table->figures[k]->getX()-148,table->figures[k]->getY()-148))
               || (!konflikt1(table->figures[k]->getX()+74,table->figures[k]->getY()-74) && free(table->figures[k]->getX()+148,table->figures[k]->getY()-148)))
                   return 1;
        }
        return 0;
    }
    else if(turn=="PLAYER2"){
        for(int k=0;k<table->figures.length();k++){
           if(table->figures[k]->getOwner()=="PLAYER2")
               if((!konflikt2(table->figures[k]->getX()-74,table->figures[k]->getY()+74) && free(table->figures[k]->getX()-148,table->figures[k]->getY()+148))
               || (!konflikt2(table->figures[k]->getX()+74,table->figures[k]->getY()+74) && free(table->figures[k]->getX()+148,table->figures[k]->getY()+148)))
                   return 1;
        }
        return 0;
    }
    else;
}



void Game::validan(Figure* f,int i, int j){
    if(f->getOwner()=="PLAYER1"){
       if(konflikt1(i-74,j-74)!=-1 || konflikt1(i+74,j-74)!=-1){
         if(eatLU(f,i-74,j-74,konflikt1(i-74,j-74)) || eatRU(f,i+74,j-74,konflikt1(i+74,j-74)))
          return;
       }
       if(i!=4 && j!=4 && free(i-74,j-74))
         move(i-74,j-74);
       if(j!=4 && i!=522 && free(i+74,j-74))
         move(i+74,j-74);
    }
    else if(f->getOwner()=="PLAYER2"){
       if(konflikt2(i-74,j+74)!=-1 || konflikt2(i+74,j+74)!=-1){
          if(eatLD(f,i-74,j+74,konflikt2(i-74,j+74)) || eatRD(f,i+74,j+74,konflikt2(i+74,j+74)))
             return;
       }
       if(i!=4 && j!=522 && free(i-74,j+74))
           move(i-74,j+74);
       if(j!=522 && i!=522 && free(i+74,j+74))
           move(i+74,j+74);
    }
    else;
}


void Game::setWhosTurn(){
    if(whosTurn=="PLAYER1"){
        whosTurn="PLAYER2";
        cout<<"p2"<<endl;
    }
    else{
        whosTurn="PLAYER1";
        cout<<"p1"<<endl;
    }
}
