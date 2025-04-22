#include "Triangle.h"
#include <iostream>
#include <cmath>

using namespace std;

double distance(const Point &p1, const Point &p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double heronArea(const Triangle &t) {
    double a = distance(t.A, t.B);
    double b = distance(t.B, t.C);
    double c = distance(t.C, t.A);
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

double Triangle::area() const {
    return heronArea(*this);
}

bool Triangle::isDegenerate() const {
    double dx1 = B.x - A.x;
    double dy1 = B.y - A.y;
    double dx2 = C.x - A.x;
    double dy2 = C.y - A.y;
    double cross = dx1 * dy2 - dy1 * dx2;
    return fabs(cross) < 1e-9;
}

bool Triangle::contains(const Point &P) const {
    Triangle T1 = {A, B, P};
    Triangle T2 = {B, C, P};
    Triangle T3 = {C, A, P};

    double S_main = area();
    double S_sum = T1.area() + T2.area() + T3.area();

    return fabs(S_main - S_sum) < 1e-9;
}

bool Triangle::containsVector(const Point &P) const {
    auto cross = [](const Point &O, const Point &A, const Point &B) {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    };

    double d1 = cross(P, A, B);
    double d2 = cross(P, B, C);
    double d3 = cross(P, C, A);

    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

void inputTriangle(Triangle &t) {
    cout << "Введіть координати трикутника (Ax Ay Bx By Cx Cy): ";
    cin >> t.A.x >> t.A.y >> t.B.x >> t.B.y >> t.C.x >> t.C.y;

    if (t.isDegenerate()) {
        cout << "Трикутник є виродженим.\n";
    } else {
        cout << "Трикутник не є виродженим.\n";
    }
}

void inputPoints(vector<Point> &points) {
    int n;
    cout << "Введіть кількість точок: ";
    cin >> n;
    points.resize(n);
    for (int i = 0; i < n; ++i) {
        cout << "Координати точки " << i + 1 << " (x y): ";
        cin >> points[i].x >> points[i].y;
    }
}

void checkPointsInTriangle(const Triangle &t, const vector<Point> &points) {
    if (points.empty()) {
        cout << "Спочатку введіть точки!" << endl;
        return;
    }

    cout << "Оберіть метод перевірки:\n";
    cout << "1 — Герон\n";
    cout << "2 — Векторний добуток\n";
    cout << "0 — Вийти\n";
    cout << "Ваш вибір: ";

    int method;
    cin >> method;
    if (method == 0) return;

    cout << "\nРезультати перевірки:\n";
    for (size_t i = 0; i < points.size(); ++i) {
        const Point &p = points[i];
        cout << "Точка " << i + 1 << ": ";

        bool inside = false;
        if (method == 1) {
            inside = t.contains(p);
        } else if (method == 2) {
            inside = t.containsVector(p);
        } else {
            cout << "Невірний метод." << endl;
            return;
        }

        if (inside) {
            cout << "Належить трикутнику або лежить на його межі" << endl;
        } else {
            cout << "Не належить трикутнику." << endl;
        }
    }
}

void print_menu() {
    Triangle t;
    vector<Point> points;

    while (true) {
        cout << "\n===== МЕНЮ =====\n";
        cout << "1. Ввести координати трикутника\n";
        cout << "2. Ввести точки\n";
        cout << "3. Перевірити точки\n";
        cout << "4. Вихід\n";
        cout << "Ваш вибір: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                inputTriangle(t);
                break;
            case 2:
                inputPoints(points);
                break;
            case 3:
                checkPointsInTriangle(t, points);
                break;
            case 4:
                cout << "Завершення програми." << endl;
                return;
            default:
                cout << "Невірний вибір." << endl;
        }
    }
}
