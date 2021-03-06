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
    Field getField(int i, int j);
    void ispisiPolja(QVector<QVector<Field>> f);
    void figureRow(int red,int x, int y, int z, int k, QString owner);

    QVector< QVector<Field> > fields;
    QList<Figure *> figures;
};

#endif // TABLE_H
