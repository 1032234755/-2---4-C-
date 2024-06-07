#include <iostream>
#include <cmath>
#include <tuple>

// ��������� ��� ������������� ����� � ������������
struct Point3D {
    double x;
    double y;
    double z;
};

// ������� ��� �������� �������������� ����� ���������
bool isPointOnHyperbola(double a, double b, Point3D p) {
    return std::abs((p.x * p.x) / (a * a) - (p.y * p.y) / (b * b) - 1) < 1e-6;
}

// ������� ��� �������� ����������� ��������� � ����������
bool doesPlaneIntersectHyperbola(double a, double b, double A, double B, double C, double D) {
    // ��������� ���������: Ax + By + Cz + D = 0
    // ����������� x � y �� ��������� � ��������� ��������� � ���������, ���������� �� ������� ��� z
    for (double x = -a; x <= a; x += 0.1) {
        for (double y = -b; y <= b; y += 0.1) {
            if (std::abs((x * x) / (a * a) - (y * y) / (b * b) - 1) < 1e-6) {
                double z = (-A * x - B * y - D) / C;
                return true;
            }
        }
    }
    return false;
}

// ������� ��� �������� ����������� ������ � ����������
bool doesLineIntersectHyperbola(double a, double b, std::function<double(double)> x_eq, std::function<double(double)> y_eq) {
    for (double t = -10; t <= 10; t += 0.1) {
        double x = x_eq(t);
        double y = y_eq(t);
        if (std::abs((x * x) / (a * a) - (y * y) / (b * b) - 1) < 1e-6) {
            return true;
        }
    }
    return false;
}

int main() {
    // ������������ ��������� ���������
    double a = 3, b = 2;

    // �������� �����
    Point3D p = { 1, 0, 0 };

    // �������� �������������� ����� ���������
    if (isPointOnHyperbola(a, b, p)) {
        std::cout << "����� (" << p.x << ", " << p.y << ", " << p.z << ") ����������� ���������." << std::endl;
    }
    else {
        std::cout << "����� (" << p.x << ", " << p.y << ", " << p.z << ") �� ����������� ���������." << std::endl;
    }

    // ������������ ��������� (������)
    double A = 1, B = -2, C = 1, D = -3;

    // �������� ����������� ��������� � ����������
    if (doesPlaneIntersectHyperbola(a, b, A, B, C, D)) {
        std::cout << "��������� ���������� ���������." << std::endl;
    }
    else {
        std::cout << "��������� �� ���������� ���������." << std::endl;
    }

    // ��������� ������ (������)
    auto x_eq = [](double t) { return 1 + 2 * t; };
    auto y_eq = [](double t) { return 3 + t; };

    // �������� ����������� ������ � ����������
    if (doesLineIntersectHyperbola(a, b, x_eq, y_eq)) {
        std::cout << "������ ���������� ���������." << std::endl;
    }
    else {
        std::cout << "������ �� ���������� ���������." << std::endl;
    }

    return 0;
}
