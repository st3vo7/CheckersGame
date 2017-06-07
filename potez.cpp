#include "potez.h"
#include "field.h"


Potez::Potez(Figure *a_f, Field *a_staroPolje, Field *a_novoPolje, int a_score)
    :_f(a_f),_staroPolje(a_staroPolje),_novoPolje(a_novoPolje),_score(a_score)
{

}

void Potez::postaviRezultat(int score)
{
    _score=score;

}



