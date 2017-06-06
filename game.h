#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "table.h"
#include "figure.h"
#include "score.h"
#include <QMouseEvent>
#include <QGraphicsRectItem>


class Game: public QGraphicsView{
    Q_OBJECT
    //neophodno prilikom koriscenja signala i slotova
public:
    Game(QWidget* parent =NULL);
    void displayMainMenu();
    void pickUpFigure(Figure* f1);
    void placeFigure(Figure* f1);
    void setWhosTurn();
    void validan(Figure* f, int i, int j);
    void move(int i, int j);
    bool free(int i, int j);
    int eatLU(Figure* f,int i, int j, int k);
    int eatRU(Figure* f,int i, int j, int k);
    int eatLD(Figure* f,int i, int j, int k);
    int eatRD(Figure* f,int i, int j, int k);
    int konflikt1(int i, int j);
    int konflikt2(int i, int j);
    void mark(int i, int j);
    bool eaten=false;
    QString otherPlayer();
    int checkIfKonflikt(QString turn);
    QGraphicsTextItem *t;
    void end();
    bool sused(Figure* glavna, Figure* pom);
    void displayEndWindow(QString message);
    void demarkiraj();
    void drawPanel(int x,int y, int width, int height);
    void drawPanel(int x,int y, int width, int height, QString str, int k, int l);


    QGraphicsScene* scene;

    Table* table;
    QPointF orignalPos;
    Figure* f;
    QString whosTurn="PLAYER1";
    Score* scoreI;
    Score* scoreII;

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);


public slots:
    void start();
};

#endif // GAME_H
