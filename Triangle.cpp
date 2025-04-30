#include "Triangle.h"

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

double cross(const Point &P, const Point &A, const Point &B) {
    return (A.x - P.x) * (B.y - P.y) - (A.y - P.y) * (B.x - P.x);
}

bool Triangle::containsVector(const Point &P) const {
    if (isDegenerate()) {
        return isPointOnSegment(P, A, B) || isPointOnSegment(P, B, C) || isPointOnSegment(P, C, A);
    }
    double d1 = cross(P, A, B);
    double d2 = cross(P, B, C);
    double d3 = cross(P, C, A);

    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

bool isPointInTriangle_Heron(const Triangle &t, const Point &p, bool &onEdge) {
    Triangle T1 = {t.A, t.B, p};
    Triangle T2 = {t.B, t.C, p};
    Triangle T3 = {t.C, t.A, p};

    double S_main = t.area();
    double S1 = T1.area();
    double S2 = T2.area();
    double S3 = T3.area();
    double S_sum = S1 + S2 + S3;

    onEdge = fabs(S1) < 1e-9 || fabs(S2) < 1e-9 || fabs(S3) < 1e-9;

    return fabs(S_main - S_sum) < 1e-9;
}

bool isPointInTriangle_Cross(const Triangle &t, const Point &p, bool &onEdge) {
    if (t.isDegenerate()) {
        onEdge = isPointOnSegment(p, t.A, t.B) || isPointOnSegment(p, t.B, t.C) || isPointOnSegment(p, t.C, t.A);
        return onEdge;
    }

    double d1 = cross(p, t.A, t.B);
    double d2 = cross(p, t.B, t.C);
    double d3 = cross(p, t.C, t.A);

    onEdge = fabs(d1) < 1e-9 || fabs(d2) < 1e-9 || fabs(d3) < 1e-9;

    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

bool isPointOnSegment(const Point &P, const Point &A, const Point &B) {
    double d1 = distance(P, A);
    double d2 = distance(P, B);
    double d3 = distance(A, B);

    return fabs(d1 + d2 - d3) < 1e-9;
}

void print_menu() {

    Triangle t;
    vector<Point> points;

    cout << "Введіть координати трикутника (Ax Ay Bx By Cx Cy): ";
    cin >> t.A.x >> t.A.y >> t.B.x >> t.B.y >> t.C.x >> t.C.y;

    if (t.isDegenerate()) {
        cout << "Трикутник є виродженим.\n";
    } else {
        cout << "Трикутник не є виродженим.\n";
    }

    int n;
    cout << "Введіть кількість точок: ";
    cin >> n;
    points.resize(n);
    for (int i = 0; i < n; ++i) {
        cout << "Координати точки " << i + 1 << " (x y): ";
        cin >> points[i].x >> points[i].y;
    }

    while (true) {
        cout << "\nОберіть метод перевірки:\n";
        cout << "0 — Вийти\n";
        cout << "1 — Герон\n";
        cout << "2 — Векторний добуток\n";
        cout << "Ваш вибір: ";
        int method;
        cin >> method;

        if (method == 0) {
            cout << "Завершення програми...\n";
            break;
        }

        cout << "\nРезультати перевірки:\n";
        for (size_t i = 0; i < points.size(); ++i) {
            const Point &p = points[i];
            cout << "Точка " << i + 1 << ": ";
            bool onEdge = false;
            bool inside = false;

            if (method == 1) {
                if (t.isDegenerate()) {
                    inside = isPointOnSegment(p, t.A, t.B) || isPointOnSegment(p, t.B, t.C) || isPointOnSegment(p, t.C, t.A);
                    onEdge = inside;
                } else {
                    inside = isPointInTriangle_Heron(t, p, onEdge);
                }
            } else if (method == 2) {
                inside = isPointInTriangle_Cross(t, p, onEdge);
            } else {
                cout << "Невірний метод.\n";
                break;
            }

            if (onEdge) {
                cout << "Точка лежить на межі трикутника\n";
            } else if (inside) {
                cout << "Точка належить трикутнику\n";
            } else {
                cout << "Точка не належить трикутнику\n";
            }
        }
    }
}