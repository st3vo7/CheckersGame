#include "game.h"
#include "table.h"
#include "button.h"

#include <QFont>
#include <QString>
#include <QGraphicsTextItem>
#include <iostream>
#include <QFontDatabase>
#include <QThread>
#include <QMessageBox>
#include <QTime>
#include <QBrush>
#include <QImage>

using namespace std;

class Sleeper : public QThread{
public:
    static void usleep(unsigned long usecs){
        QThread::usleep(usecs);
    }

    static void msleep(unsigned long msecs){
        QThread::msleep(msecs);
    }

    static void sleep(unsigned long secs){
        QThread::sleep(secs);
    }
};

Game::Game(QWidget *parent)
    : QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(600, 700);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 600, 700);
    setScene(scene);
    f = NULL;
}

void Game::displayMainMenu(){
    scene->setBackgroundBrush(QBrush(QImage(":/slike/ss.jpg")));
    drawPanel(2, 0, 370, 498, ":/slike/svitak.png", 110, 150);

    drawPanel(0, 0, 300, 100, ":/slike/naslov.png", 150, 0);

    Button *play1 = new Button(QString("1 vs 1"));
    int p1xPos = this->width()/2 - play1->boundingRect().width()/2;
    int p1yPos = 200;
    play1->setPos(p1xPos, p1yPos);
    connect(play1, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(play1);

    Button *play2 = new Button(QString("computer H"));
    int p2xPos = this->width()/2 - play2->boundingRect().width()/2;
    int p2yPos = 275;
    play2->setPos(p2xPos, p2yPos);
    connect(play2, SIGNAL(clicked()), this, SLOT(start1()));
    scene->addItem(play2);

    Button *play3 = new Button(QString("computer E"));
    int p3xPos = this->width()/2 - play3->boundingRect().width()/2;
    int p3yPos = 350;
    play3->setPos(p3xPos, p3yPos);
    connect(play3, SIGNAL(clicked()), this, SLOT(start2()));
    scene->addItem(play3);

    Button *play4 = new Button(QString("on network"));
    int p4xPos = this->width()/2 - play4->boundingRect().width()/2;
    int p4yPos = 425;
    play4->setPos(p4xPos, p4yPos);
    connect(play4, SIGNAL(clicked()), this, SLOT(mrezno()));
    scene->addItem(play4);

    Button *quit = new Button(QString("EXIT"));
    int qxPos = this->width()/2 - quit->boundingRect().width()/2;
    int qyPos = 500;
    quit->setPos(qxPos, qyPos);
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quit);
}

void Game::start(){
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

    indikator = 0;
}

void Game::start1(){
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

    cout << "start1" << endl;
    indikator = 1;
}

void Game::start2(){
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

    cout << "start2" << endl;
    indikator = 2;
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

    server = new Server();

    if(!server->server->listen(QHostAddress::Any, 1234))
        qDebug() << "Server ne osluskuje!";
    else
        qDebug() << "Server osluskuje!";

    QMessageBox::information(this, "Checkers", "Pokrenite checkers_client da bi se mogla igrati igrica!");

    connect(server, SIGNAL(dobijeneKoordinate(int, int, int, int)), this, SLOT(primamKoordinateMrezno(int,int, int, int)));
    connect(server->socket, SIGNAL(connected()), this, SLOT(konektovan()));
    connect(server->socket, SIGNAL(disconnected()), this, SLOT(diskonektovan()));
}

void Game::primamKoordinateMrezno(int fx, int fy, int px, int py){
    for(int i = 0; i < table->figures.length(); i++)
        if(fx == table->figures[i]->getX() && fy == table->figures[i]->getY())
            for(int j = 0; j < 8; j++)
                for(int k = 0; k < 8; k++)
                    if(px == table->fields[j][k].getx() && py == table->fields[j][k].gety())
                        placeFigure1(table->figures[i], &table->fields[j][k]);

    end();
}

void Game::konektovan(){
    qDebug() << "Soket se konektovao!";
}

void Game::diskonektovan(){
    qDebug() << "Soket se diskonektovao!";
}

void Game::mouseMoveEvent(QMouseEvent *event){
    if(f)
        f->setPos(event->pos());
    QGraphicsView::mouseMoveEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton)
        cukic2();

    QGraphicsView::mousePressEvent(event);
}

void Game::pickUpFigure(Figure *f1){
    if(f == NULL){
        f = f1;
        orignalPos = f1->pos();
        return;
    }
}

void Game::placeFigure(Figure *f1){
    for(int i = 0; i < table->figures.length(); i++)
        if(table->figures[i]->pos() == f1->pos())
            scene->removeItem(table->figures[i]);

    f->setPos(f1->pos());

    if(f1->getY() == 4 && f->getOwner() == "PLAYER1"){
        f->isQueen = true;
        f->setPixmap(QPixmap(":/slike/B.png"));
    }

    if(f1->getY() == 522 && f->getOwner() == "PLAYER2"){
        f->isQueen = true;
        f->setPixmap(QPixmap(":/slike/A.png"));
    }

    table->figures.removeAll(f1);

    scene->removeItem(f1);

    for(int i = 0; i < table->figures.length(); i++)
        if(table->figures[i]->eaten && table->figures[i]->getOwner() != "NONE" && sused(table->figures[i], f1)){
            if(table->figures[i]->getOwner()!=whosTurn && whosTurn == "PLAYER1")
                scoreI->inc();
            if(table->figures[i]->getOwner()!=whosTurn && whosTurn == "PLAYER2")
                scoreII->inc();
            table->figures[i]->setOwner("NONE");
        }

    f->setZValue(0);
    f = NULL;
    demarkiraj();
}

void Game::placeFigure1(Figure *f1, Field *p1){
    for(int i = 0; i < table->figures.length(); i++)
        if(table->figures[i]->getX() == p1->getx() && table->figures[i]->getY() == p1->gety())
            scene->removeItem(table->figures[i]);

    f1->setPos(p1->getx(), p1->gety());

    if(p1->gety() == 522 && f1->getOwner() == "PLAYER2"){
        f1->isQueen = true;
        f1->setPixmap(QPixmap(":/slike/A.png"));
    }

    for(int i = 0; i < table->figures.length(); i++)
        if(table->figures[i]->eaten && table->figures[i]->getOwner() != "NONE" && sused(table->figures[i], f1)){
            if(table->figures[i]->getOwner() != whosTurn && whosTurn == "PLAYER2")
                scoreII->inc();
            table->figures[i]->setOwner("NONE");
        }

    f1 = NULL;
    demarkiraj();
}

bool Game::sused(Figure *glavna, Figure *pom){
    if((glavna->getX()-pom->getX() == 74 || glavna->getX()-pom->getX() == -74) && (glavna->getY()-pom->getY() == 74 || glavna->getY()-pom->getY() == -74))
        return true;
    else
        return false;
}

void Game::demarkiraj(){
    for(int i = 0; i < table->figures.length(); i++)
        table->figures[i]->eaten = false;
}

void Game::move(int i, int j){
    Figure *f1 = new Figure();
    f1->setOwner("h");
    f1->setPos(i, j);
    f1->setX(i);
    f1->setY(j);
    scene->addItem(f1);
    table->figures.push_back(f1);
}

bool Game::free(int i, int j){
    if(i<4 || i>522 || j<4 || j>522)
        return false;

    for(int k = 0; k < table->figures.length(); k++){
        table->figures[k]->koord(table->figures[k]);
        if(table->figures[k]->getX() == i && table->figures[k]->getY() == j)
           if(table->figures[k]->getOwner() == "PLAYER1" || table->figures[k]->getOwner() == "PLAYER2")
                return false;
    }

     return true;
}

int Game::eatLU(Figure *f, int i, int j, int k){
    if(k == -1)
        return 0;

    if(free(i - 74, j - 74)){
        move(i - 74, j - 74);
        mark(i, j);
        return 1;
    }

    return 0;
}

int Game::eatRU(Figure *f, int i, int j, int k){
    if(k == -1)
        return 0;

    if(free(i + 74, j - 74)){
        move(i + 74, j - 74);
        mark(i, j);
        return 1;
    }

    return 0;
}

int Game::eatLD(Figure *f, int i, int j, int k){
    if(k == -1)
        return 0;

    if(free(i - 74, j + 74)){
        move(i - 74, j + 74);
        mark(i, j);
        return 1;
    }

    return 0;
}

int Game::eatRD(Figure *f, int i, int j, int k){
    if(k == -1)
        return 0;

    if(free(i + 74, j + 74)){
        move(i + 74, j + 74);
        mark(i, j);
        return 1;
    }

    return 0;
}

int Game::konflikt1(int i, int j){
    if(i <= 4 || i >= 522 || j <= 4 || j >= 522)
        return -1;

    for(int k = 0; k < table->figures.length(); k++){
        table->figures[k]->koord(table->figures[k]);
        if(table->figures[k]->getX() == i && table->figures[k]->getY() == j)
           if(table->figures[k]->getOwner() == "PLAYER2")
                return 0;
    }

    return -1;
}

int Game::konflikt2(int i, int j){
    if(i <= 4 || i >= 522 || j <= 4 || j >= 522)
        return -1;

    for(int k = 0; k < table->figures.length(); k++){
        table->figures[k]->koord(table->figures[k]);
        if(table->figures[k]->getX() == i && table->figures[k]->getY() == j)
           if(table->figures[k]->getOwner() == "PLAYER1")
                return 0;
    }

    return -1;
}

void Game::mark(int i, int j){
    for(int k = 0; k < table->figures.length(); k++)
        if(table->figures[k]->getX() == i && table->figures[k]->getY() == j)
                table->figures[k]->eaten = true;
}

QString Game::otherPlayer(){
    if(whosTurn == "PLAYER1")
        return "PLAYER2";
    else
        return "PLAYER1";
}

int Game::checkIfKonflikt(QString turn){
    if(turn == "PLAYER1"){
        for(int k = 0; k < table->figures.length(); k++)
           if(table->figures[k]->getOwner() == "PLAYER1"){
               if(table->figures[k]->isQueen)
                   if((!konflikt1(table->figures[k]->getX() - 74, table->figures[k]->getY() + 74) && free(table->figures[k]->getX() - 148, table->figures[k]->getY() + 148))
                   || (!konflikt1(table->figures[k]->getX() + 74, table->figures[k]->getY() + 74) && free(table->figures[k]->getX() + 148, table->figures[k]->getY() + 148)))
                       return 1;

               if((!konflikt1(table->figures[k]->getX() - 74, table->figures[k]->getY() - 74) && free(table->figures[k]->getX() - 148, table->figures[k]->getY() - 148))
               || (!konflikt1(table->figures[k]->getX() + 74, table->figures[k]->getY() - 74) && free(table->figures[k]->getX() + 148, table->figures[k]->getY() - 148)))
                   return 1;
           }

        return 0;
    }
    else if(turn == "PLAYER2"){
        for(int k = 0; k < table->figures.length(); k++)
           if(table->figures[k]->getOwner() == "PLAYER2"){
               if(table->figures[k]->isQueen)
                   if((!konflikt2(table->figures[k]->getX() - 74, table->figures[k]->getY() - 74) && free(table->figures[k]->getX() - 148, table->figures[k]->getY() - 148))
                   || (!konflikt2(table->figures[k]->getX() + 74, table->figures[k]->getY() - 74) && free(table->figures[k]->getX() + 148, table->figures[k]->getY() - 148)))
                       return 1;

               if((!konflikt2(table->figures[k]->getX() - 74, table->figures[k]->getY() + 74) && free(table->figures[k]->getX() - 148, table->figures[k]->getY() + 148))
               || (!konflikt2(table->figures[k]->getX() + 74, table->figures[k]->getY() + 74) && free(table->figures[k]->getX() + 148, table->figures[k]->getY() + 148)))
                   return 1;
           }

        return 0;
    }
    else{
        return -1;
    }
}

int Game::end(){
    if(scoreI->getScore() == 12){
        displayEndWindow("Player1");
        return 1;
    }

    if(scoreII->getScore() == 12){
        displayEndWindow("Player2");
        return 1;
    }

    return 0;
}

QGraphicsTextItem *Game::displayRazmisljam(QString message){
    QGraphicsTextItem *tp = new QGraphicsTextItem(message);
    tp->setPos(100 + 22, 150 + 78 + 22);
    tp->setFont(QFont("Western", 60));
    tp->setDefaultTextColor(Qt::lightGray);
    scene->addItem(tp);
    tp->setZValue(100);
    return tp;
}

void Game::displayEndWindow(QString message){
    for(int i = 0; i < scene->items().size(); i++)
        scene->items()[i]->setEnabled(false);

    drawPanel(0, 0, 600, 700);
    drawPanel(0, 0, 375, 500, ":/slike/ss.jpg", 100, 105);
    drawPanel(0, 0, 375, 500, ":/slike/svitak.png", 100, 105);

    QGraphicsTextItem *tp = new QGraphicsTextItem(message + " won!");
    tp->setPos(190, 200);
    tp->setFont(QFont("comic sans", 30));
    tp->setDefaultTextColor(Qt::white);
    scene->addItem(tp);

    Button *playAgain = new Button(QString("PLAY AGAIN"));
    playAgain->setPos(200, 300);
    scene->addItem(playAgain);
    connect(playAgain, SIGNAL(clicked()), this, SLOT(displayMainMenu()));

    Button *quit = new Button(QString("QUIT"));
    quit->setPos(200, 400);
    scene->addItem(quit);
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
}

void Game::validan(Figure *f, int i, int j){
    postaviH(f, i, j);
}

void Game::postaviH(Figure *f, int i, int j){
    if(f->getOwner() == "PLAYER1"){
        int a = 0;
        int b = 0;
        int c = 0;
        int d = 0;

        if(konflikt1(i - 74, j + 74) != -1 || konflikt1(i + 74, j + 74) != -1 || konflikt1(i - 74, j - 74) != -1 || konflikt1(i + 74, j - 74) != -1){
            if(f->isQueen){
                a = eatLD(f, i - 74, j + 74, konflikt1(i - 74, j + 74));
                b = eatRD(f, i + 74, j + 74, konflikt1(i + 74, j + 74));
                c = eatLU(f, i - 74, j - 74, konflikt1(i - 74, j - 74));
                d = eatRU(f, i + 74, j - 74, konflikt1(i + 74, j - 74));

                if(a ||b ||c || d)
                    return;
            }

            c = eatLU(f, i - 74, j - 74, konflikt1(i - 74, j - 74));
            d = eatRU(f, i + 74, j - 74, konflikt1(i + 74, j - 74));

            if(c || d)
                return;
       }

       if(i != 4 && j != 522 && free(i - 74, j + 74) && f->isQueen)
          move(i - 74, j + 74);

       if(j != 522 && i != 522 && free(i + 74, j + 74) && f->isQueen)
         move(i + 74, j + 74);

       if(i != 4 && j != 4 && free(i - 74, j - 74))
         move(i - 74, j - 74);

       if(j != 4 && i != 522 && free(i + 74, j - 74))
         move(i + 74, j - 74);
    }

    else if(f->getOwner() == "PLAYER2"){
        int a = 0;
        int b = 0;
        int c = 0;
        int d = 0;

        if(konflikt2(i - 74, j - 74) != -1 || konflikt2(i + 74, j - 74) != -1 || konflikt2(i - 74, j + 74) != -1 || konflikt2(i + 74, j + 74) != -1){
            if(f->isQueen){
                a = eatLU(f, i - 74, j - 74, konflikt2(i - 74, j - 74));
                b = eatRU(f, i + 74, j - 74, konflikt2(i + 74, j - 74));
                c = eatLD(f, i - 74, j + 74, konflikt2(i - 74, j + 74));
                d = eatRD(f, i + 74, j + 74, konflikt2(i + 74, j + 74));

                if(a || b ||c || d)
                    return;
            }

            c = eatLD(f, i - 74, j + 74, konflikt2(i - 74, j + 74));
            d = eatRD(f, i + 74, j + 74, konflikt2(i + 74, j + 74));

            if(c || d)
                return;
        }

       if(i != 4 && j != 4 && free(i - 74, j - 74) && f->isQueen)
           move(i - 74, j - 74);

       if(j != 4 && i != 522 && free(i + 74, j - 74) && f->isQueen)
           move(i + 74, j - 74);

       if(i != 4 && j != 522 && free(i - 74, j + 74))
           move(i - 74, j + 74);

       if(i != 522 && j != 522 && free(i + 74, j + 74))
           move(i + 74, j + 74);
    }
    else{
    }
}

void Game::setWhosTurn(){
    if(whosTurn == "PLAYER1"){
        whosTurn = "PLAYER2";
        t->setPos(400, 660);

        if(indikator == 1){
            robot->odigraj();
            end();

            whosTurn = "PLAYER1";
            t->setPos(400, 610);
        }

        if(indikator == 2){
             Sleeper::msleep(10);
             robot->odigraj2();
             end();

             whosTurn = "PLAYER1";
             t->setPos(400, 610);
        }
    }
    else{
        whosTurn = "PLAYER1";
        t->setPos(400, 610);
    }
}

void Game::drawPanel(int x, int y, int width, int height){
    QGraphicsRectItem *panel = new QGraphicsRectItem(x, y, width, height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::lightGray);
    panel->setBrush(brush);
    scene->addItem(panel);
}

void Game::drawPanel(int x, int y, int width, int height, QString str, int k, int l){
    QGraphicsRectItem *panel = new QGraphicsRectItem(x, y, width, height);
    QBrush brush;
    brush.setTexture(QPixmap(str));
    panel->setBrush(brush);
    panel->setPos(k, l);
    scene->addItem(panel);
}

void Game::ispisiFigure(){
    int i;

    for(i = 0; i < table->figures.size(); i++){
        cout << i << " ";
        cout << table->figures[i]->getX() << " " << table->figures[i]->getY();
        if(table->figures[i]->getOwner() == "PLAYER1")
            cout << "P1" << endl;
        else if(table->figures[i]->getOwner() == "PLAYER2")
            cout << "P2" << endl;
        else if(table->figures[i]->getOwner() == "NONE")
            cout << "N" << endl;
        else{
        }
    }
}

void Game::pobrisiHove(){
    for(int i = 0; i < table->figures.length(); i++)
        if(table->figures[i]->getOwner() == "h")
            table->figures[i]->setOwner("NONE");
}

void Game::cukic2(){
     if(f){
        f->setPos(orignalPos);
        for(int i = 0; i < table->figures.length(); i++){
         if(table->figures[i]->getOwner() == "h")
            table->figures[i]->setOwner("NONE");

         if(f->notEmpty(table->figures[i]) && table->figures[i]->getOwner() == "NONE")
             scene->removeItem(table->figures[i]);
        }

        f = NULL;
        return;
     }
}
