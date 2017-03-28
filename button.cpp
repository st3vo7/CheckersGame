#include "button.h"
#include <QBrush>
#include <QFont>
#include <QGraphicsTextItem>

Button::Button(QString name, QGraphicsItem *parent):QGraphicsRectItem(parent){
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);

    text= new QGraphicsTextItem(name,this);
    int xPos= rect().width()/3-text->boundingRect().width()/2;
    int yPos= rect().width()/4-text->boundingRect().height()*2;
    QFont titleFont("comic sans",20);
    text->setFont(titleFont);
    text->setPos(xPos,yPos);

    //dozvoli uzvracanje hove eventima
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
    //aktivira se kada je signal kada se klikne misem
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkBlue);
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);
}
