#ifndef TABLE_H
#define TABLE_H
#include <QVector>
#include <QList>
#include "field.h"
#include "figure.h"


class Table{
public:
    Table();
    void placeFigures();
    void setFields();
    QList<Figure*> figures;

    void ispisiPolja(QList<Figure*> f);
    void figureRow(int red,int x, int y, int z, int k, QString owner);


private:
    QVector< QVector<Field> > fields;
};


#endif // TABLE_H
