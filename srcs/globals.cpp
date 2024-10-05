
#include "scop.hpp"

std::vector<std::shared_ptr<Vertex> > vertices;
std::vector<Face> faces;

std::map<int, bool> isFaceSelected;
int                 storedVector = -1;
float yaw = 4.2f;
float pitch = -0.3f;

float cam_x = 3.0f;
float cam_y = 1.5f;
float cam_z = 50.0f;

std::map<unsigned char, bool> keys;