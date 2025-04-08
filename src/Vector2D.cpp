#include <cmath>
#include "Vector2D.h"

double Vector2D::length() const {
    return sqrt(this->x * this->x + this->y * this->y);
}

Vector2D Vector2D::normalize() const {
    const double len = this->length();
    return (len > 0) ? *this / len : Vector2D { 0.0, 0.0 };
}

