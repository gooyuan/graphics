//
// Created by Sophimp on 2018/9/2.
//

#ifndef CLIONOPENGL_POINT_H
#define CLIONOPENGL_POINT_H


class Point {

public:
    double x;
    double y;

    Point();
    Point(double x, double y);

    Point rotate(double angle);

    Point operator +(Point p);

    Point operator -(Point p);
};


#endif //CLIONOPENGL_POINT_H
