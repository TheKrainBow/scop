#include "Face.hpp"


void Face::computeNormal()
{
    _normal = Vertex(0.0, 0.0, 0.0);

    for (size_t i = 1; i < _vertices.size() - 1; ++i) {
        Vertex v0 = *_vertices[0];     // Fixed reference vertex
        Vertex v1 = *_vertices[i];     // Current vertex
        Vertex v2 = *_vertices[i + 1]; // Next vertex

        // Compute the normal for this triangle and add to the total normal
        Vertex edge1 = v1 - v0;
        Vertex edge2 = v2 - v0;
        Vertex triangleNormal = edge1.cross(edge2);
        _normal = _normal + triangleNormal;
    }

    // Normalize the accumulated normal
    _normal.normalize();
}

Face::Face(std::vector<std::shared_ptr<Vertex> > &vertices) : _vertices(vertices)
{
    _red = (double)(rand() % 250 + 5) / 255;
    _green = (double)(rand() % 250 + 5) / 255;
    _blue = (double)(rand() % 250 + 5) / 255;
    _x = 0;
    _y = 0;
    _z = 0;
    for (auto &it : vertices)
    {
        _x += (*it)._x;
        _y += (*it)._y;
        _z += (*it)._z;
    }
    _x /= _vertices.size();
    _y /= _vertices.size();
    _z /= _vertices.size();
    computeNormal();
}

void Face::moveAmongNormal(double distance) {
    (void)distance;
    // Assure-toi que la face a suffisamment de sommets
    if (_vertices.size() < 3) {
        std::cerr << "Error: Face has fewer than 3 vertices, cannot calculate normal!" << std::endl;
        return;
    }

    // Étape 1 : Accumuler les normales pour chaque sommet
    for (std::shared_ptr<Vertex> vertexPtr : _vertices) {
        vertexPtr->accumulateNormal(_normal);  // Accumule la normale de la face dans le sommet
    }
    
}

void Face::moveVerticesAlongAveragedNormal(double distance) {
    // Déplace chaque sommet en fonction de sa normale moyenne
    for (std::shared_ptr<Vertex> vertexPtr : _vertices) {
        Vertex& vertex = *vertexPtr;
        if (!vertex._moved) {
            Vertex avgNormal = vertex.getAverageNormal();
            if (avgNormal.length() > 0.0) {
                vertex = vertex + (avgNormal * distance);  // Déplace le sommet le long de la normale moyenne
                vertex._moved = true;
            }
        }
    }
}

// void Face::moveAmongNormal(double distance) {
//     // Step 1: Ensure the face has enough vertices
//     if (_vertices.size() < 3) {
//         std::cerr << "Error: Face has fewer than 3 vertices, cannot calculate normal!" << std::endl;
//         return;
//     }

//     // Step 3: Move each vertex along the averaged normal vector
//     for (std::shared_ptr<Vertex> vertexPtr : _vertices) {
//         Vertex& vertex = *vertexPtr;
//         if (!vertex._moved) {
//             vertex = vertex + (_normal * distance);  // Displace the vertex along the average normal
//             vertex._moved = true;
//         }
//     }
//     computeNormal();
// }