#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "Vertex.hpp"

class Face {
private:
public:
    std::vector<std::shared_ptr<Vertex> > _vertices;
    Vertex                                _normal;
    double                                _red;
    double                                _green;
    double                                _blue;
    double                                _x;
    double                                _y;
    double                                _z;
    void moveAmongNormal(double distance);
    void moveVerticesAlongAveragedNormal(double distance);
    void computeNormal();
    Face(std::vector<std::shared_ptr<Vertex> > &vertices);
};