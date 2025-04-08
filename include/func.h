#ifndef FUNC_H
#define FUNC_H

#include "Vector2D.h"

constexpr double G = 6.6743e-11;
constexpr double Ms = 1.989e30;
constexpr double Mz = 5.972e24;
constexpr double Mk = 7.347e22;
constexpr double Rzs = 1.5e11;
constexpr double Rzk = 3.844e8;

struct Body {
    double mass;
    Vector2D position;
    Vector2D velocity;
    constexpr Body(const double mass, const Vector2D p, const Vector2D v)
        : mass(mass), position(p), velocity(v) {};
};

Vector2D compute_acceleration(const Body&, const Body&);
void midpoint_step(Body&, const Vector2D&, double);
void simulate(const char*, double, int);

#endif //FUNC_H
