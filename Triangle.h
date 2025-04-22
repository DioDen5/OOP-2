#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>

struct Point {
    double x, y;
};

struct Triangle {
    Point A, B, C;

    double area() const;
    bool contains(const Point &P) const;
    bool containsVector(const Point &P) const;
    bool isDegenerate() const;
};

double distance(const Point &p1, const Point &p2);

void inputTriangle(Triangle &t);
void inputPoints(std::vector<Point> &points);
void checkPointsInTriangle(const Triangle &t, const std::vector<Point> &points);

void print_menu();

#endif // TRIANGLE_H
