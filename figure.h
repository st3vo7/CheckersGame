#ifndef FIGURE_H
#define FIGURE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class Figure: public QGraphicsPixmapItem{
public:
    Figure(QGraphicsItem* parent=NULL);
    void setOwner(QString owner);
private:
    QString _owner;

};

#endif // FIGURE_H
