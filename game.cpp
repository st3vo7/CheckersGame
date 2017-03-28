#include "game.h"
#include "table.h"
#include <QBrush>
#include <QImage>
#include "button.h"
#include <QFont>
#include <QString>
#include <QGraphicsTextItem>


Game::Game(QWidget* parent){
    //podesavamo ekran

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(600,600);

    //podesavamo scenu
    scene= new QGraphicsScene();
    scene->setSceneRect(0,0,600,600);
    setScene(scene);
}

void Game::start(){
    //Ocistimo ekran
    scene->clear();
    scene->setBackgroundBrush(QBrush(QImage(":/slike/chessboardtessellation.jpg")));
    Table* table=new Table();
    table->placeFigures();
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
