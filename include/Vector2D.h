#ifndef POSITION_H
#define POSITION_H

#include <ostream>

struct Vector2D {

    double x, y;

    constexpr Vector2D(const double x, const double y) : x(x), y(y) {};

    constexpr Vector2D operator+(const Vector2D &other) const {
        return Vector2D { this->x + other.x, this->y + other.y };
    }

    constexpr Vector2D& operator+=(const Vector2D &other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    constexpr Vector2D operator-(const Vector2D &other) const {
        return Vector2D { this->x - other.x, this->y - other.y };
    }

    constexpr Vector2D& operator-=(const Vector2D &other) {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    constexpr Vector2D operator*(const double scalar) const {
        return Vector2D { this->x * scalar, this->y * scalar };
    }

    constexpr Vector2D& operator*=(const double scalar) {
        this->x *= scalar;
        this->y *= scalar;
        return *this;
    }

    constexpr Vector2D operator/(const double scalar) const {
        return Vector2D { this->x / scalar, this->y / scalar };
    }

    constexpr Vector2D& operator/=(const double scalar) {
        this->x /= scalar;
        this->y /= scalar;
        return *this;
    }

    [[nodiscard]] double length() const;

    [[nodiscard]] Vector2D normalize() const;

};

inline std::ostream& operator<<(std::ostream &os, const Vector2D &position) {
    os << position.x << ", " << position.y;
    return os;
}

constexpr Vector2D operator*(const double scalar, const Vector2D &vector) {
    return Vector2D { scalar * vector.x, scalar * vector.y };
}

#endif //POSITION_H
