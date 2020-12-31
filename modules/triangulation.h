#ifndef TRIANGULATION_H
#define TRIANGULATION_H

class Point {
    public:
        Point() :
            x(0),
            y(0)
        {
        }

        Point(float x, float y) :
            x(x),
            y(y)
        {
        }

        float x;
        float y;
};

class Circle : public Point {
    public:
        Circle(float x, float y, float r) :
            Point(x, y),
            r(r)
        {
        }

        float r;
};

Point triangulation(Circle circ1, Circle circ2, Circle circ3);

#endif
