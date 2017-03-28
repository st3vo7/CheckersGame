#include "mainwindow.h"
#include <QApplication>
#include "game.h"

//globalni objekat tipa pokazivac
Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game=new Game();
    game->show();
    game->displayMainMenu();
    //on ce da pozove metod start() kao svoj slot


    return a.exec();
}
