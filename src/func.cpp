#include <cmath>
#include <fstream>
#include "func.h"
#include <iostream>

inline Vector2D compute_acceleration(const Body &target, const Body &source) {
    const Vector2D diff = source.position - target.position;
    const double distance = diff.length();
    if (distance == 0.0)
        return Vector2D { 0.0, 0.0 };
    const double acceleration = G * source.mass / (distance * distance);
    return diff / distance * acceleration;
}

inline void midpoint_step(Body &body, const Vector2D &acceleration, const double dt) {
    const Vector2D velocity_mid = body.velocity + (0.5 * dt) * acceleration;
    body.position += velocity_mid * dt;
    body.velocity += acceleration * dt;
}

void simulate(const char *file_name, double dt, int steps) {
    constexpr Body sun { Ms, Vector2D { 0.0, 0.0 }, Vector2D { 0.0, 0.0 } };

    const double earth_v0 = sqrt(G * Ms / Rzs);

    Body earth { Mz, Vector2D { Rzs, 0.0 }, Vector2D { 0.0, earth_v0 } };

    const double moon_v0 = sqrt(G * Mz / Rzk);

    Vector2D moon_pos = earth.position + Vector2D { Rzk, 0.0 };
    Vector2D moon_vel = earth.velocity + Vector2D { 0.0, moon_v0 };

    Body moon { Mk, moon_pos, moon_vel };

    std::ofstream out(file_name);
    if (!out.is_open()) {
        std::cerr << "Error opening file " << file_name << '\n';
        return;
    }

    out << "time,earth_x,earth_y,moon_x,moon_y\n";

    for (int i = 0; i < steps; ++i) {
        double t = i * dt;
        out << t << ","<< earth.position << "," << moon.position << "\n";

        Vector2D acc_earth = compute_acceleration(earth, sun);
        midpoint_step(earth, acc_earth, dt);

        Vector2D acc_moon = compute_acceleration(moon, earth) + compute_acceleration(moon, sun);
        midpoint_step(moon, acc_moon, dt);
    }
    out.close();
}
