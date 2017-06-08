#include "robot.h"
#include "game.h"
#include "potez.h"
#include "figure.h"

#include <vector>
#include <QtTest/QTest>
#include <QString>
#include <string>
#include <bits/stdc++.h>

using namespace std;
extern Game *game;

Potez Robot::vratiNajboljiPotez(){
    std::vector<Potez> moguciPotezi = generisiPoteze("PLAYER2");

    for(unsigned i = 0; i < moguciPotezi.size(); i++){
        probajPotez(moguciPotezi[i]);
        int sc = 0;
        sc += AlfaBeta(0, MIN_SCORE, MAX_SCORE, true);
        moguciPotezi[i].postaviRezultat(sc);
        inverzPotez(moguciPotezi[i]);
    }

    if(moguciPotezi.size() != 0){
        int max = moguciPotezi[0].vratiRezultat();
        for(unsigned i = 1; i < moguciPotezi.size(); i++)
            if(moguciPotezi[i].vratiRezultat() >= max)
                max = moguciPotezi[i].vratiRezultat();

        for(unsigned i = 1; i < moguciPotezi.size(); i++)
            if(moguciPotezi[i].vratiRezultat() == max)
                return moguciPotezi[i];
    }
    else
        game->displayEndWindow("Player1");
}

Potez Robot::vratiNajboljiPotez2(){
    std::vector<Potez> moguciPotezi = generisiPoteze("PLAYER2");

    if(moguciPotezi.size() == 0)
        game->displayEndWindow("Player1");
    else
        return moguciPotezi[qrand()%moguciPotezi.size()];
}

void Robot::odigraj(){
    Potez p = vratiNajboljiPotez();
    Figure *f1 = p.vratiFiguru();
    Field *p1 = p.vratiNovoPolje();

    game->placeFigure1(f1, p1);

    for(int i = 0; i < game->table->figures.length(); i++){
        if(game->table->figures[i]->getOwner() == "h")
            game->table->figures[i]->setOwner("NONE");

        if(game->table->figures[i]->notEmpty(game->table->figures[i]) && game->table->figures[i]->getOwner() == "NONE")
            game->scene->removeItem(game->table->figures[i]);
    }
}

void Robot::odigraj2(){
    Potez p = vratiNajboljiPotez2();
    Figure *f1 = p.vratiFiguru();

    Field *p1 = p.vratiNovoPolje();

    game->placeFigure1(f1, p1);

    for(int i = 0; i < game->table->figures.length(); i++){
        if(game->table->figures[i]->getOwner() == "h")
            game->table->figures[i]->setOwner("NONE");

        if(game->table->figures[i]->notEmpty(game->table->figures[i]) && game->table->figures[i]->getOwner() == "NONE")
            game->scene->removeItem(game->table->figures[i]);
    }
}

void Robot::probajPotez(Potez p){
    p.vratiFiguru()->setX(p.vratiNovoPolje()->getx());
    p.vratiFiguru()->setY(p.vratiNovoPolje()->gety());
}

void Robot::inverzPotez(Potez p){
    p.vratiFiguru()->setX(p.vratiStaroPolje()->getx());
    p.vratiFiguru()->setY(p.vratiStaroPolje()->gety());
}

bool Robot::skrozokej(Figure *f){
    if ((f->getX() == 4 || f->getX() == 78 || f->getX() == 152 || f->getX() == 226 || f->getX() == 300 || f->getX() == 374 || f->getX() == 448 || f->getX() == 522) && (f->getY() == 4 || f->getY() == 78 || f->getY() == 152 || f->getY() == 226 || f->getY() == 300 || f->getY() == 374 || f->getY() == 448 || f->getY() == 522))
        return true;
    return false;
}

std::vector<Potez> Robot::generisiPoteze(string igrac){
    std::vector<Potez> v;

    int i = 0;
    for(i; i < game->table->figures.size(); i++){
        QString qigrac = QString::fromStdString(igrac);
        if(game->table->figures[i]->getOwner() == qigrac){
            if(game->checkIfKonflikt(game->whosTurn)){
                if(game->table->figures[i]->hasConf())
                    game->postaviH(game->table->figures[i], game->table->figures[i]->getX(), game->table->figures[i]->getY());
            else
                continue;
            }
            game->postaviH(game->table->figures[i], game->table->figures[i]->getX(), game->table->figures[i]->getY());

            int j = 0;
            for(j; j < game->table->figures.size(); j++){
                if(game->table->figures[j]->getOwner() == "h"){
                    if(skrozokej(game->table->figures[j])){
                        Field *f1 = new Field(game->table->figures[i]->getX(), game->table->figures[i]->getY());
                        Field *f2 = new Field();
                        f2->setx(game->table->figures[j]->getX());
                        f2->sety(game->table->figures[j]->getY());
                        Potez *p = new Potez(game->table->figures[i], f1, f2, 0);
                        v.push_back(*p);
                    }

                    if(j != game->table->figures.size() - 1)
                        if(skrozokej(game->table->figures[j + 1])){
                            Field *f1 = new Field(game->table->figures[i]->getX(), game->table->figures[i]->getY());
                            Field *f2 = new Field();
                            f2->setx(game->table->figures[j + 1]->getX());
                            f2->sety(game->table->figures[j + 1]->getY());
                            Potez *p = new Potez(game->table->figures[i], f1, f2, 0);
                            v.push_back(*p);
                        }

                    game->pobrisiHove();
                }
            }

            game->pobrisiHove();
        }
    }

    return v;
}

int Robot::AlfaBeta(int depth, int alfa, int beta, bool max){
    if(depth == 1)
        return evaluate("PLAYER2");

    if(game->end())
        return max ? MAX_SCORE : MIN_SCORE;

    std::vector<Potez> detePotezi;

    if(max)
        detePotezi = generisiPoteze("PLAYER1");
    else
        detePotezi = generisiPoteze("PLAYER2");

    if(detePotezi.empty())
        return max ? MAX_SCORE : MIN_SCORE;

    int vr;

    if(max){
        vr = MIN_SCORE;

        for(unsigned i = 0; i < detePotezi.size(); i++){
            probajPotez(detePotezi[i]);

            vr = std::max(vr, AlfaBeta(depth + 1, alfa, beta, !max));
            alfa = std::max(alfa, vr);
            inverzPotez(detePotezi[i]);

            if(beta <= alfa)
                break;
        }

        return vr;
    }
    else{
        vr = MAX_SCORE;

        for(unsigned i = 0; i < detePotezi.size(); i++){
            probajPotez(detePotezi[i]);

            vr = std::min(vr, AlfaBeta(depth + 1, alfa, beta, max));
            beta = std::min(beta, vr);
            inverzPotez(detePotezi[i]);

            if(beta <= alfa)
                break;
        }

        return vr;
    }

    return 0;
}

int Robot::evaluate(string igrac){
    int score = 0;
    int brFiguraRobot = 0, brFiguraIgrac = 0;
    int brKraljicaRobot = 0, brKraljicaIgrac = 0;

    QString qkomp = QString::fromStdString(igrac);
    QString qprotivnik = QString::fromStdString("PLAYER1");

    for(int i = 0; i < game->table->figures.size(); i++){
        if(game->table->figures[i]->getOwner() == qkomp){
            if(game->table->figures[i]->isQueen)
                brKraljicaRobot++;
            else brFiguraRobot++;
        }
        if(game->table->figures[i]->getOwner() == qprotivnik){
            if(game->table->figures[i]->isQueen)
                brKraljicaIgrac++;
            else brFiguraIgrac++;
        }
    }

    if (brFiguraIgrac+brKraljicaIgrac == 0)
        return MAX_SCORE;

    if(brFiguraRobot+brKraljicaRobot == 0)
        return MIN_SCORE;

    score = brFiguraRobot + 2*brKraljicaRobot - brFiguraIgrac - 2*brKraljicaIgrac;
    return score;
}
