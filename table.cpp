#include "table.h"
#include "game.h"

extern Game* game;

Table::Table(){}

QList<Figure*> Table::getFigures(){
    return figures;
}

void Table::placeFigures(){
    figureRow(4,0,4);
    figureRow(79,74.75,4);
    figureRow(4,149.5,4);

    figureRow(79,5*74.75,4);
    figureRow(4,6*74.75,4);
    figureRow(79,7*74.75,4);

}

void Table::figureRow(int x, int y, int number){
    //pravimo red figura
    for(size_t i=0; i<number ; i++){
        Figure* figura=new Figure();
        figura->setPos(x+148*i,y);
        figures.append(figura);
        game->scene->addItem(figura);
    }
}


















