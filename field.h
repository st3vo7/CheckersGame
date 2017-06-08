#ifndef FIELD_H
#define FIELD_H

class Field{
public:
    Field(int x, int y);
    Field();

    int getx();
    int gety();

    void setx(int x);
    void sety(int y);

private:
    int _x;
    int _y;
};

#endif // FIELD_H
