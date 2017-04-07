#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "table.h"
#include "figure.h"

class Game: public QGraphicsView{
    Q_OBJECT
    //neophodno prilikom koriscenja signala i slotova
public:
    Game(QWidget* parent =NULL);

    void displayMainMenu();

    QGraphicsScene* scene;
    QString whosTurn;
    Table* table;

public slots:
    void start();
};

#endif // GAME_H
