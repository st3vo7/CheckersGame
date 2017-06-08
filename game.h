#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QMouseEvent>
#include <QGraphicsRectItem>

#include "table.h"
#include "figure.h"
#include "score.h"
#include "robot.h"
#include "potez.h"
#include "server.h"

class Robot;

class Game : public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget *parent = NULL);
    void pickUpFigure(Figure *f1);
    void placeFigure(Figure *f1);
    void placeFigure1(Figure *f1, Field *p1);
    void setWhosTurn();
    void validan(Figure *f, int i, int j);
    void move(int i, int j);
    bool free(int i, int j);
    int eatLU(Figure *f, int i, int j, int k);
    int eatRU(Figure *f, int i, int j, int k);
    int eatLD(Figure *f, int i, int j, int k);
    int eatRD(Figure *f, int i, int j, int k);
    int konflikt1(int i, int j);
    int konflikt2(int i, int j);
    void mark(int i, int j);
    QString otherPlayer();
    int checkIfKonflikt(QString turn);
    int end();
    void displayEndWindow(QString message);
    void drawPanel(int x, int y, int width, int height);
    void drawPanel(int x, int y, int width, int height, QString str, int k, int l);
    void ispisiFigure();
    void cukic2();
    void postaviH(Figure *f, int i, int j);
    void pobrisiHove();
    bool sused(Figure *glavna, Figure *pom);
    void demarkiraj();
    QGraphicsTextItem *displayRazmisljam(QString message);

    Robot *robot;
    QGraphicsTextItem *t;
    bool eaten = false;
    QGraphicsScene *scene;
    QGraphicsTextItem *qgti;
    Potez *p1;
    Table *table;
    QPointF orignalPos;
    Figure *f;
    QString whosTurn = "PLAYER1";
    Score *scoreI;
    Score *scoreII;
    QString poruka = "";
    Server *server;
    int ind = 0;
    int indikator;
    int ostale = 12;

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

public slots:
    void displayMainMenu();
    void start();
    void start1();
    void start2();
    void mrezno();
    void primamKoordinateMrezno(int fx, int fy, int px, int py);
    void konektovan();
    void diskonektovan();
};

#endif // GAME_H
