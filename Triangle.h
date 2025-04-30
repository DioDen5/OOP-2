#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Point {
    double x, y;
};

struct Triangle {
    Point A, B, C;

    double area() const;
    bool isDegenerate() const;
    bool contains(const Point &P) const;
    bool containsVector(const Point &P) const;
};

double cross(const Point &P, const Point &A, const Point &B);
bool isPointOnSegment(const Point &P, const Point &A, const Point &B);
void print_menu();

#endif
