#include "table.h"
#include "game.h"
#include <iostream>

using namespace std;
extern Game* game;

Table::Table(){
    setFields();
    placeFigures();
}

void Table::ispisiPolja(QList<Figure*> f){
    for(int i=0;i<f.length();i++){
        cout<<f[i]->getX()<<" , ";
        cout<<f[i]->getY()<<endl;
    }
}


void Table::placeFigures(){
    figureRow(0,0,2,4,6,"PLAYER2");
    figureRow(1,1,3,5,7,"PLAYER2");
    figureRow(2,0,2,4,6,"PLAYER2");

    figureRow(3,1,3,5,7,"NONE");
    figureRow(4,0,2,4,6,"NONE");

    figureRow(5,1,3,5,7,"PLAYER1");
    figureRow(6,0,2,4,6,"PLAYER1");
    figureRow(7,1,3,5,7,"PLAYER1");
}

void Table::setFields(){
    fields.resize(8);
    for(int k=0;k<8;k++)
        fields[k].resize(8);

    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++){
           Field *f=new Field(4+i*74,4+j*74);
           fields[i][j]=*f;
        }
}


void Table::figureRow(int red, int x, int y,int z, int k ,QString owner){
    //pravimo red figura

        Figure* figura=new Figure();
        Figure* figura1=new Figure();
        Figure* figura2=new Figure();
        Figure* figura3=new Figure();

        figura->setOwner(owner);
        figura1->setOwner(owner);
        figura2->setOwner(owner);
        figura3->setOwner(owner);

        figura->setPos(fields[x][red].getx(),fields[x][red].gety());
        figura1->setPos(fields[y][red].getx(),fields[y][red].gety());
        figura2->setPos(fields[z][red].getx(),fields[z][red].gety());
        figura3->setPos(fields[k][red].getx(),fields[k][red].gety());

        figures.append(figura);
        figures.append(figura1);
        figures.append(figura2);
        figures.append(figura3);

        game->scene->addItem(figura);
        game->scene->addItem(figura1);
        game->scene->addItem(figura2);
        game->scene->addItem(figura3);

}
