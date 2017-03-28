#ifndef FIGURE_H
#define FIGURE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include "game.h"

class Figure: public QGraphicsPixmapItem{
public:
    Figure(QGraphicsItem* parent=NULL);
private:
    QString owner;

};

#endif // FIGURE_H
