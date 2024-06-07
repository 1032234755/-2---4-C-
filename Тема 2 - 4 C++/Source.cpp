#include <iostream>
#include <cmath>
#include <tuple>

// Структура для представления точки в пространстве
struct Point3D {
    double x;
    double y;
    double z;
};

// Функция для проверки принадлежности точки гиперболе
bool isPointOnHyperbola(double a, double b, Point3D p) {
    return std::abs((p.x * p.x) / (a * a) - (p.y * p.y) / (b * b) - 1) < 1e-6;
}

// Функция для проверки пересечения плоскости с гиперболой
bool doesPlaneIntersectHyperbola(double a, double b, double A, double B, double C, double D) {
    // Уравнение плоскости: Ax + By + Cz + D = 0
    // Подставляем x и y из гиперболы в уравнение плоскости и проверяем, существует ли решение для z
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

// Функция для проверки пересечения прямой с гиперболой
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
    // Коэффициенты уравнения гиперболы
    double a = 3, b = 2;

    // Заданная точка
    Point3D p = { 1, 0, 0 };

    // Проверка принадлежности точки гиперболе
    if (isPointOnHyperbola(a, b, p)) {
        std::cout << "Точка (" << p.x << ", " << p.y << ", " << p.z << ") принадлежит гиперболе." << std::endl;
    }
    else {
        std::cout << "Точка (" << p.x << ", " << p.y << ", " << p.z << ") не принадлежит гиперболе." << std::endl;
    }

    // Коэффициенты плоскости (пример)
    double A = 1, B = -2, C = 1, D = -3;

    // Проверка пересечения плоскости с гиперболой
    if (doesPlaneIntersectHyperbola(a, b, A, B, C, D)) {
        std::cout << "Плоскость пересекает гиперболу." << std::endl;
    }
    else {
        std::cout << "Плоскость не пересекает гиперболу." << std::endl;
    }

    // Уравнения прямой (пример)
    auto x_eq = [](double t) { return 1 + 2 * t; };
    auto y_eq = [](double t) { return 3 + t; };

    // Проверка пересечения прямой с гиперболой
    if (doesLineIntersectHyperbola(a, b, x_eq, y_eq)) {
        std::cout << "Прямая пересекает гиперболу." << std::endl;
    }
    else {
        std::cout << "Прямая не пересекает гиперболу." << std::endl;
    }

    return 0;
}
