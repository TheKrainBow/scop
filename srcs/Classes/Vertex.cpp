#include "Vertex.hpp"
#include "math.h"

Vertex::Vertex() : _x(0), _y(0), _z(0), _moved(false) {}
Vertex::Vertex(double x, double y, double z) : _x(x), _y(y), _z(z), _moved(false)
{
}

Vertex Vertex::operator-(const Vertex& v) const {
    return Vertex(_x - v._x, _y - v._y, _z - v._z);
}

double Vertex::length() const {
    return std::sqrt(_x * _x + _y * _y + _z * _z);
}

double Vertex::dot(const Vertex& v) const {
    return _x * v._x + _y * v._y + _z * v._z;
}

// Cross product between two vertices
Vertex Vertex::cross(const Vertex& v) const {
    return Vertex(
        _y * v._z - _z * v._y,  // x component
        _z * v._x - _x * v._z,  // y component
        _x * v._y - _y * v._x   // z component
    );
}

// Normalize the vector (convert it to a unit vector)
void Vertex::normalize() {
    double length = sqrt(_x * _x + _y * _y + _z * _z);
    if (length != 0) {
        _x /= length;
        _y /= length;
        _z /= length;
    }
}

