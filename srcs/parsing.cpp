#include "scop.hpp"

std::vector<Face> parseOBJ(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return faces;
    }

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            // Lecture des sommets
            double x, y, z;
            iss >> x >> y >> z;
            vertices.push_back(std::make_shared<Vertex>(x, y, z));
        } else if (type == "f") {
            // Lecture des faces
            std::vector<std::shared_ptr<Vertex> > faceVertices;
            std::string vertexData;
            while (iss >> vertexData) {
                // On ne prend que la première valeur avant le "/"
                std::istringstream vertexStream(vertexData);
                int vertexIndex;
                vertexStream >> vertexIndex;
                faceVertices.push_back(vertices[vertexIndex - 1]);
            }
            faces.push_back(Face(faceVertices));
        }
    }

    file.close();
    return (faces);
}