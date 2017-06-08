#ifndef POTEZ_H
#define POTEZ_H

#include "field.h"
#include "table.h"

class Potez{
public:
    Potez(Figure *a_f, Field *a_staroPolje, Field *a_novoPolje, int a_score);

    Field *vratiNovoPolje(){
        return _novoPolje;
    }

    Field *vratiStaroPolje(){
        return _staroPolje;
    }

    int vratiRezultat(){
        return _score;
    }

    Figure *vratiFiguru(){
        return _f;
    }

    void postaviRezultat(int score);

    Potez operator <(const Potez &p1){
        if(this->_score < p1._score)
            return *this;
        else return p1;
    }

private:
    int _score;
    Figure *_f;
    Field *_novoPolje;
    Field *_staroPolje;
};

#endif // POTEZ_H
