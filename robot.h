#ifndef ROBOT_H
#define ROBOT_H

#include "table.h"
#include "game.h"
#include "potez.h"
#include "figure.h"
#include <string>
#include <vector>

#define MAX_SCORE 1000
#define MIN_SCORE -1000
#define DUBINA 4


class Robot{

public:
    //Robot (int _dubina = 2);

    Potez *sledeciPotez();
    Potez vratiNajboljiPotez();
    Potez vratiNajboljiPotez2();
    char vratiTip();
    void odigraj();
    void odigraj2();

private:

    void probajPotez(Potez p);
    void inverzPotez(Potez p);
    Figure vratiStatus(Field *polje, Table *t);
    bool skrozokej(Figure *f);

    std::vector<Potez> generisiPoteze(string igrac);

    int AlfaBeta(int depth, int alfa, int beta, bool max);
    int evaluate(string igrac);

    //Table *_tabla;

    //int _najvecaEfikasnost; //bice 0 na pocetku u konstr
    int _dubina;
   // char _protivnik;
    Potez *_trenutniNajboljiPotez;


};


#endif // ROBOT_H
