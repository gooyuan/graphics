//
// Created by Sophimp on 2018/9/2.
//

#include <cmath>
#include "Point.h"

Point::Point() : x(0), y(y) {}

Point::Point(double x, double y) : x(x), y(y) {}

Point Point::rotate(double angle) {
    Point result;
    result.x = result.x * cos(angle) - result.y * sin(angle);
    result.y = result.x * sin(angle) + result.y * cos(angle);
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
