#ifndef FIGURE_H
#define FIGURE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <iostream>

using namespace std;


class Figure: public QGraphicsPixmapItem{
public:
    Figure(QGraphicsItem* parent=NULL);
    void setOwner(QString owner);
    QString getOwner();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void cukic();
    void probna();
    void koord(Figure *f);
    bool notEmpty(Figure* f);
    void validanP1(int i, int j);
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();
    int hasConf();
    bool eaten=false;
    bool isQueen=false;

private:
    QString _owner;
    int k;
    int j;
};

#endif // FIGURE_H
