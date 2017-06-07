#include "game.h"
#include "table.h"
#include <QTime>
#include <QBrush>
#include <QImage>
#include "button.h"
#include <QFont>
#include <QString>
#include <QGraphicsTextItem>
#include <iostream>
#include <QFontDatabase>
#include <QThread>
#include <QMessageBox>

using namespace std;

class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};
/* TO DO LIST:
 * završetak igre-prozor i dalje reference
*/


Game::Game(QWidget* parent){
    //podesavamo ekran

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(600,700);

    //podesavamo scenu
    scene= new QGraphicsScene();
    scene->setSceneRect(0,0,600,700);
    setScene(scene);
    f=NULL;

}

void Game::start(){
    //Ocistimo ekran
    scene->clear();
    scene->setBackgroundBrush(QBrush(QImage(":/slike/chessboardtessellation.jpg")));

    table=new Table();
    scoreI=new Score();
    scoreII=new Score();

    scene->addItem(scoreI);
    scene->addItem(scoreII);

    scoreI->setPos(310,600);
    scoreII->setPos(310,660);

    t=new QGraphicsTextItem("TURN");
    QFont tG("Western",25);
    t->setDefaultTextColor(Qt::lightGray);
    tG.setBold(true);
    t->setFont(tG);
    scene->addItem(t);
    t->setPos(400,610);

    indikator=0;
}

void Game::start1()
{
    //Ocistimo ekran
    scene->clear();
    scene->setBackgroundBrush(QBrush(QImage(":/slike/chessboardtessellation.jpg")));

    table=new Table();
    scoreI=new Score();
    scoreII=new Score();

    scene->addItem(scoreI);
    scene->addItem(scoreII);

    scoreI->setPos(310,600);
    scoreII->setPos(310,660);

    t=new QGraphicsTextItem("TURN");
    QFont tG("Western",25);
    t->setDefaultTextColor(Qt::lightGray);
    tG.setBold(true);
    t->setFont(tG);
    scene->addItem(t);
    t->setPos(400,610);

    /*for(size_t i=0,n=table->figures.size();i<n;i++){
        if(table->figures[i]->getOwner()==QString("PLAYER2"))
            table->figures[i]->setAcceptedMouseButtons(false);//ne mozes da ih pomeras misem
    }*/
    cout<<"start1"<<endl;
    indikator=1;
}



void Game::mrezno(){
    ind = 2;

    scene->clear();
    scene->setBackgroundBrush(QBrush(QImage(":/slike/chessboardtessellation.jpg")));

    table = new Table();
    scoreI = new Score();
    scoreII = new Score();

    scene->addItem(scoreI);
    scene->addItem(scoreII);

    scoreI->setPos(310, 600);
    scoreII->setPos(310, 660);

    t = new QGraphicsTextItem("TURN");
    QFont tG("Western", 25);
    t->setDefaultTextColor(Qt::lightGray);
    tG.setBold(true);
    t->setFont(tG);
    scene->addItem(t);
    t->setPos(400, 610);

    qDebug() << QTime::currentTime();
    Server server;
    qDebug() << QTime::currentTime();

    QMessageBox::information(this, "Checkers", "Pokrenite checkers_client da bi se mogla igrati igrica!");
}


void Game::start2()
{
    //Ocistimo ekran
    scene->clear();
    scene->setBackgroundBrush(QBrush(QImage(":/slike/chessboardtessellation.jpg")));

    table=new Table();
    scoreI=new Score();
    scoreII=new Score();

    scene->addItem(scoreI);
    scene->addItem(scoreII);

    scoreI->setPos(310,600);
    scoreII->setPos(310,660);

    t=new QGraphicsTextItem("TURN");
    QFont tG("Western",25);
    t->setDefaultTextColor(Qt::lightGray);
    tG.setBold(true);
    t->setFont(tG);
    scene->addItem(t);
    t->setPos(400,610);

    /*for(size_t i=0,n=table->figures.size();i<n;i++){
        if(table->figures[i]->getOwner()==QString("PLAYER2"))
            table->figures[i]->setAcceptedMouseButtons(false);//ne mozes da ih pomeras misem
    }*/
    cout<<"start2"<<endl;
    indikator=2;
}


void Game::displayMainMenu(){
   //pravimo naslov
    scene->setBackgroundBrush(QBrush(QImage(":/slike/ss.jpg")));
    drawPanel(2,0,370,498,":/slike/svitak.png",110,150);

    drawPanel(0,0,300,100,":/slike/naslov.png",150,0);

    //pravimo play dugme

    Button* play=new Button(QString("1 vs 1"));
    int bxPos=this->width()/2- play->boundingRect().width()/2;
    int byPos=200;
    play->setPos(bxPos,byPos);
    connect(play,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(play);

    // pravimo quit dugme
    Button* help=new Button(QString("computer H"));
    int hxPos=this->width()/2-help->boundingRect().width()/2;
    int hyPos=275;
    help->setPos(hxPos,hyPos);
    //DODATA KONEKCIJA:
    connect(help,SIGNAL(clicked()),this,SLOT(start1()));
    scene->addItem(help);

    Button* quit2=new Button(QString("on network"));
    int q2xPos=this->width()/2-quit2->boundingRect().width()/2;
    int q2yPos=425;
    quit2->setPos(q2xPos,q2yPos);
    connect(quit2,SIGNAL(clicked()),this,SLOT(mrezno()));
    scene->addItem(quit2);

    Button* quit=new Button(QString("EXIT"));
    int qxPos=this->width()/2-quit->boundingRect().width()/2;
    int qyPos=500;
    quit->setPos(qxPos,qyPos);
     connect(quit,SIGNAL(clicked()),this,SLOT(close()));
     scene->addItem(quit);

     Button* compE=new Button(QString("computer E"));
     int cxPos=this->width()/2-help->boundingRect().width()/2;
     int cyPos=350;
     compE->setPos(cxPos,cyPos);
     //DODATA KONEKCIJA:
     connect(compE,SIGNAL(clicked()),this,SLOT(start2()));
     scene->addItem(compE);


}

void Game::mouseMoveEvent(QMouseEvent *event){
    if(f)
        f->setPos(event->pos());
    QGraphicsView::mouseMoveEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::RightButton){
        cukic2();
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
void Game::placeFigure1(Figure *f1, Field *p1){

    for(int i=0;i<table->figures.length();i++){
        if(table->figures[i]->getX()==p1->getx() &&
                table->figures[i]->getY()==p1->gety())
            scene->removeItem(table->figures[i]);
    }

    f1->setPos(p1->getx(),p1->gety());

    if(p1->gety()==522 && f1->getOwner()=="PLAYER2"){
        f1->isQueen=true;
        f1->setPixmap(QPixmap(":/slike/A.png"));

    }


    for(int i=0;i<table->figures.length();i++){
        if(table->figures[i]->eaten && table->figures[i]->getOwner()!="NONE" && sused(table->figures[i], f1)){
            if(table->figures[i]->getOwner()!=whosTurn && whosTurn=="PLAYER2")
                scoreII->inc();
            table->figures[i]->setOwner("NONE");
        }
    }

    cout<<"Y koordinata pomerene: "<<p1->gety()<<endl;


    f1=NULL;
    demarkiraj();


}

void Game::placeFigure(Figure *f1){
    //f1 ti je upitnik figura
    for(int i=0;i<table->figures.length();i++){
        if(table->figures[i]->pos()==f1->pos())
            scene->removeItem(table->figures[i]);
    }

    f->setPos(f1->pos());

    if(f1->getY()==4 && f->getOwner()=="PLAYER1"){
        f->isQueen=true;
        f->setPixmap(QPixmap(":/slike/B.png"));
    }
    if(f1->getY()==522 && f->getOwner()=="PLAYER2"){
        f->isQueen=true;
        f->setPixmap(QPixmap(":/slike/A.png"));

    }
    table->figures.removeAll(f1);


    scene->removeItem(f1);
    for(int i=0;i<table->figures.length();i++){
        if(table->figures[i]->eaten && table->figures[i]->getOwner()!="NONE" && sused(table->figures[i],f1)){
            if(table->figures[i]->getOwner()!=whosTurn && whosTurn=="PLAYER1")
                scoreI->inc();
            if(table->figures[i]->getOwner()!=whosTurn && whosTurn=="PLAYER2")
                scoreII->inc();
            table->figures[i]->setOwner("NONE");
        }
    }
    f->setZValue(0);
    f=NULL;
    demarkiraj();
}

bool Game::sused(Figure *glavna, Figure *pom){
    if((glavna->getX()-pom->getX() == 74 || glavna->getX()-pom->getX() == -74) && (glavna->getY()-pom->getY() == 74 || glavna->getY()-pom->getY() == -74))
        return true;
    else return false;
}

void Game::demarkiraj()
{
    for(int i=0;i<table->figures.length();i++)
        table->figures[i]->eaten=false;
}



void Game::move(int i, int j){
    Figure* f1=new Figure();
    f1->setOwner("h");
    f1->setPos(i,j);
    f1->setX(i);
    f1->setY(j);
    scene->addItem(f1);
    //table->figures.append(f1);
    table->figures.push_back(f1);
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
    //else if(whosTurn=="PLAYER2")
      else  return "PLAYER1";
}

int Game::checkIfKonflikt(QString turn){
    if(turn=="PLAYER1"){
        for(int k=0;k<table->figures.length();k++){
           if(table->figures[k]->getOwner()=="PLAYER1"){
               if(table->figures[k]->isQueen){
                   if((!konflikt1(table->figures[k]->getX()-74,table->figures[k]->getY()+74) && free(table->figures[k]->getX()-148,table->figures[k]->getY()+148))
                   || (!konflikt1(table->figures[k]->getX()+74,table->figures[k]->getY()+74) && free(table->figures[k]->getX()+148,table->figures[k]->getY()+148)))
                       return 1;
                   }

               if((!konflikt1(table->figures[k]->getX()-74,table->figures[k]->getY()-74) && free(table->figures[k]->getX()-148,table->figures[k]->getY()-148))
               || (!konflikt1(table->figures[k]->getX()+74,table->figures[k]->getY()-74) && free(table->figures[k]->getX()+148,table->figures[k]->getY()-148)))
                   return 1;
           }
        }

        return 0;
    }
    else if(turn=="PLAYER2"){
        for(int k=0;k<table->figures.length();k++){
           if(table->figures[k]->getOwner()=="PLAYER2"){
               if(table->figures[k]->isQueen){
                   if((!konflikt2(table->figures[k]->getX()-74,table->figures[k]->getY()-74) && free(table->figures[k]->getX()-148,table->figures[k]->getY()-148))
                   || (!konflikt2(table->figures[k]->getX()+74,table->figures[k]->getY()-74) && free(table->figures[k]->getX()+148,table->figures[k]->getY()-148)))
                       return 1;
               }

               if((!konflikt2(table->figures[k]->getX()-74,table->figures[k]->getY()+74) && free(table->figures[k]->getX()-148,table->figures[k]->getY()+148))
               || (!konflikt2(table->figures[k]->getX()+74,table->figures[k]->getY()+74) && free(table->figures[k]->getX()+148,table->figures[k]->getY()+148)))
                   return 1;
           }
        }
        return 0;
    }
    else{
        return -1;
    }
}

int Game::end(){
    cout<<"Duzina figures je: "<<table->figures.size()<<endl;
    if(scoreI->getScore()==12){
        cout<<"Tralala"<<endl;
        displayEndWindow("Player1");
        //Sleeper::sleep(5);
        return 1;
    }
    //ispisiFigure();
    if(scoreII->getScore()==12){
        displayEndWindow("Player2");
        return 1;
    }


    return 0;
}

QGraphicsTextItem *Game::displayRazmisljam(QString message){
    QGraphicsTextItem *tp = new QGraphicsTextItem(message);
    tp->setPos(100+22,150+78+22);
    tp->setFont(QFont("Western",60));
    tp->setDefaultTextColor(Qt::lightGray);
    scene->addItem(tp);
    tp->setZValue(100);
    //tp->show();
    return tp;

}


void Game::displayEndWindow(QString message){

    cout<<"kraj kraj kraj"<<endl;
    for(int i=0;i<scene->items().size();i++){
        scene->items()[i]->setEnabled(false);
    }
    drawPanel(0,0,600,700);
    drawPanel(0,0,375,500,":/slike/ss.jpg",100,105);
    drawPanel(0,0,375,500,":/slike/svitak.png",100,105);


    QGraphicsTextItem* tp=new QGraphicsTextItem(message + " won!");
    tp->setPos(190,200);
    tp->setFont(QFont("comic sans",30));
    tp->setDefaultTextColor(Qt::white);
    scene->addItem(tp);

    Button* playAgain=new Button(QString("PLAY AGAIN"));
    playAgain->setPos(200,300);
    scene->addItem(playAgain);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(start()));

    Button* quit=new Button(QString("QUIT"));
    quit->setPos(200,400);
    scene->addItem(quit);
    connect(quit,SIGNAL(clicked()),this,SLOT(close()));



}



void Game::validan(Figure* f,int i, int j){
    postaviH(f,i,j);
}

void Game::postaviH(Figure* f,int i, int j){
    if(f->getOwner()=="PLAYER1"){

        int a=0;
        int b=0;
        int c=0;
        int d=0;

        if(konflikt1(i-74,j+74)!=-1 || konflikt1(i+74,j+74)!=-1 || konflikt1(i-74,j-74)!=-1 || konflikt1(i+74,j-74)!=-1){
            if(f->isQueen){
                a=eatLD(f,i-74,j+74,konflikt1(i-74,j+74));
                b=eatRD(f,i+74,j+74,konflikt1(i+74,j+74));
                c=eatLU(f,i-74,j-74,konflikt1(i-74,j-74));
                d=eatRU(f,i+74,j-74,konflikt1(i+74,j-74));

                if(a||b||c||d)
                    return;

            }

            c=eatLU(f,i-74,j-74,konflikt1(i-74,j-74));
            d=eatRU(f,i+74,j-74,konflikt1(i+74,j-74));

            if(c||d)
                return;
       }

       if(i!=4 && j!=522 && free(i-74,j+74) && f->isQueen)
          move(i-74,j+74);

       if(j!=522 && i!=522 && free(i+74,j+74) && f->isQueen)
         move(i+74,j+74);

       if(i!=4 && j!=4 && free(i-74,j-74))
         move(i-74,j-74);

       if(j!=4 && i!=522 && free(i+74,j-74))
         move(i+74,j-74);
    }

    else if(f->getOwner()=="PLAYER2"){

        int a=0;
        int b=0;
        int c=0;
        int d=0;

        if(konflikt2(i-74,j-74)!=-1 || konflikt2(i+74,j-74)!=-1 || konflikt2(i-74,j+74)!=-1 || konflikt2(i+74,j+74)!=-1){
            if(f->isQueen){
                a=eatLU(f,i-74,j-74,konflikt2(i-74,j-74));
                b=eatRU(f,i+74,j-74,konflikt2(i+74,j-74));
                c=eatLD(f,i-74,j+74,konflikt2(i-74,j+74));
                d=eatRD(f,i+74,j+74,konflikt2(i+74,j+74));

                if(a||b||c||d)
                    return;


            }
            c=eatLD(f,i-74,j+74,konflikt2(i-74,j+74));
            d=eatRD(f,i+74,j+74,konflikt2(i+74,j+74));

            if(c||d)
                return;


        }

       if(i!=4 && j!=4 && free(i-74,j-74) && f->isQueen)
           move(i-74,j-74);

       if(j!=4 && i!=522 && free(i+74,j-74) && f->isQueen)
           move(i+74,j-74);

       if(i!=4 && j!=522 && free(i-74,j+74))
           move(i-74,j+74);

       if(i!=522 && j!=522 && free(i+74,j+74))
           move(i+74,j+74);
    }
    else{

    }

}
void Game::setWhosTurn(){
    if(whosTurn=="PLAYER1"){
        cout <<"igra P1"<<endl;

        whosTurn="PLAYER2";

        cout <<"sad treba P2"<<endl;
        if(indikator==1){
            cout <<"robot jos nije odigrao"<<endl;
            //qgti = displayRazmisljam("Thinking");
            //Sleeper::sleep(3);
            robot->odigraj();
            //scene->removeItem(qgti);
            end();
            cout <<"robot je odigrao"<<endl;
            /*int brojac=0;

            for(int i=0;i<table->figures.size();i++)
                if(table->figures[i]->getOwner()=="PLAYER1")
                    brojac++;
            if(brojac<ostale){
                scoreII->inc();
                ostale-=1;
            }*/
            whosTurn="PLAYER1"; //kad robot odigra, vrati da igra player1 (nemam mouse event kad igra komp)
            t->setPos(400,660);
        }

        if(indikator==2){
             Sleeper::msleep(10);
             robot->odigraj2();
             cout<<"robot je odigrao2"<<endl;
             end();
             whosTurn="PLAYER1"; //kad robot odigra, vrati da igra player1 (nemam mouse event kad igra komp)
             t->setPos(400,660);

        }



        if(ind == 2){ // Ovde obradjuj poruku koju dobijes od klijenta
            QString odKlijenta(QString::fromUtf8(server->socket->readAll())); // Procitam sve iz soketa
            qDebug() << odKlijenta;
            QStringList lista = odKlijenta.split(","); // Parsiram poruku
            int fx = lista[1].toInt();
            int fy = lista[2].toInt();
            int px = lista[3].toInt();
            int py = lista[4].toInt();

            for(int i = 0; i < table->figures.length(); i++) // Prolazim kroz sve figure na tabli
                if(fx == table->figures[i]->getX() && fy == table->figures[i]->getY()) // Nadjem onu koju je klijent pomerio
                    for(int j = 0; j < 8; j++)
                        for(int k = 0; k < 8; k++)// Prolazim kroz sva polja na tabli
                            if(px == table->fields[j][k].getx() && py == table->fields[j][k].gety()) // Nadjem ono na koje je klijent pomerio figuru
                                placeFigure1(table->figures[i], &table->fields[j][k]);

            end();

            whosTurn = "PLAYER1";
        }
        t->setPos(400,660);
    }
    else{
        whosTurn="PLAYER1";
        t->setPos(400,610);
     //   cout<<"p1"<<endl;
    }
}

void Game::drawPanel(int x, int y, int width, int height){
    QGraphicsRectItem* panel=new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::lightGray);
    panel->setBrush(brush);
    scene->addItem(panel);
}

void Game::drawPanel(int x, int y, int width, int height, QString str, int k, int l){
    QGraphicsRectItem* panel=new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setTexture(QPixmap(str));
    panel->setBrush(brush);
    panel->setPos(k,l);
    scene->addItem(panel);
}

void Game::ispisiFigure()
{
    int i;

    for(i=0;i<table->figures.size();i++){
        cout<<i<<" ";
        cout<<table->figures[i]->getX()<<" "<<table->figures[i]->getY();
        if(table->figures[i]->getOwner()=="PLAYER1")
            cout<< "P1"<<endl;
        else if(table->figures[i]->getOwner()=="PLAYER2")
            cout<< "P2"<<endl;
        else if(table->figures[i]->getOwner()=="NONE")
            cout<< "N"<<endl;
        else{

        }

    }
    //ispisi i polja
    //table->ispisiPolja(table->fields);
}


void Game::pobrisiHove()
{
    for(int i=0;i<table->figures.length();i++){
        if(table->figures[i]->getOwner()=="h")
            table->figures[i]->setOwner("NONE");
    }
}


void Game::cukic2()
{

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
