#ifndef TABLE_H
#define TABLE_H

#include <QList>
#include "figure.h"

class Table{
public:
    Table();
    QList<Figure*> getFigures();
    void placeFigures();
private:
    void figureRow(int x, int y, int number);
    QList<Figure*> figures;
};


#endif // TABLE_H
