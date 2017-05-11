#include "score.h"
#include "game.h"
#include <QFont>

extern Game* game;

Score::Score(QGraphicsItem *parent):QGraphicsTextItem(parent){
    score=0;

    setPlainText(""+ QString::number(score));
    setDefaultTextColor(Qt::darkGray);
    setFont(QFont("comic sans",30));

}

void Score::inc(){
   score++;
   setPlainText(""+QString::number(score));
}

int Score::getScore(){
    return score;
}

