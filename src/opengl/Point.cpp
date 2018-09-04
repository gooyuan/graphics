//
// Created by Sophimp on 2018/9/2.
//

#include <cmath>
#include "Point.h"

Point::Point() : x(0), y(y) {}

Point::Point(double x, double y) : x(x), y(y) {}

Point Point::rotate(double angle) {
    Point result;
    result.x = x * cos(angle) - y * sin(angle);
    result.y = x * sin(angle) + y * cos(angle);
    return result;
}

Point Point::operator+(Point p) {
    Point result;
    result.x = x + p.x;
    result.y = y + p.y;
    return result;
}

Point Point::operator-(Point p) {
    Point result;
    result.x = x - p.x;
    result.y = y - p.y;
    return result;
}
