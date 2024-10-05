#pragma once

#include <math.h>
#include <cstdint>

class Vertex {
public:
    double _x, _y, _z;
    bool    _moved;
    int     _normalCount;
    double _accumulatedNormalX = 0.0;
    double _accumulatedNormalY = 0.0;
    double _accumulatedNormalZ = 0.0;
    Vertex(double x, double y, double z);
    Vertex();
public:
    // Subtraction operator: subtracts one vertex from another
    Vertex operator-(const Vertex& v) const;

    // Dot product between two vertices
    double dot(const Vertex& v) const;
    double length() const;

    Vertex operator*(double scalar) const {
        return Vertex(_x * scalar, _y * scalar, _z * scalar);
    }

    bool operator==(const Vertex& other) const {
        const double epsilon = 1e-5; // Tolerance for floating-point comparison
        return (fabs(_x - other._x) < epsilon &&
                fabs(_y - other._y) < epsilon &&
                fabs(_z - other._z) < epsilon);
    }
    int encode() const {
        uint32_t x = static_cast<uint32_t>(_x) & 0xFFFF;
        uint32_t y = static_cast<uint32_t>(_y) & 0xFFFF;
        uint32_t z = static_cast<uint32_t>(_z) & 0xFFFF;
        return (x << 16) | (y << 8) | z;
    }
    bool operator!=(const Vertex& other) const {
        return (!(*this == other));
    }

    Vertex getAverageNormal() const;

    // Remet à zéro la normale accumulée et le compteur
    void resetAccumulatedNormal() {
        _accumulatedNormalX = 0.0;
        _accumulatedNormalY = 0.0;
        _accumulatedNormalZ = 0.0;
        _normalCount = 0;
        _moved = false;
    }

    // Ajoute une normale à la normale accumulée
    void accumulateNormal(const Vertex& normal) {
        _accumulatedNormalX += normal._x;
        _accumulatedNormalY += normal._y;
        _accumulatedNormalZ += normal._z;
        _normalCount++;
    }

    // Calcule la normale moyenne et la normalise
    Vertex getAverageNormal() {
        if (_normalCount == 0) return Vertex(0.0, 0.0, 0.0);
        
        // Moyenne des coordonnées des normales
        double avgX = _accumulatedNormalX / _normalCount;
        double avgY = _accumulatedNormalY / _normalCount;
        double avgZ = _accumulatedNormalZ / _normalCount;

        // Création de la normale moyenne et normalisation
        Vertex avgNormal(avgX, avgY, avgZ);
        avgNormal.normalize();
        return avgNormal;
    }

    Vertex operator+(const Vertex& other) const {
        return Vertex(_x + other._x, _y + other._y, _z + other._z);
    }
    

    // Cross product between two vertices
    Vertex cross(const Vertex& v) const;

    // Normalize the vector (convert it to a unit vector)
    void normalize();
};