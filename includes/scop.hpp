#pragma once

#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>

#include "Face.hpp"
#include "Vertex.hpp"
#include <math.h>
#include <memory>


extern std::vector<std::shared_ptr<Vertex> > vertices;
extern std::vector<Face> faces;

extern std::map<int, bool> isFaceSelected;
extern int                  storedVector;
extern float yaw;
extern float pitch;

extern float cam_x;
extern float cam_y;
extern float cam_z;

extern std::map<unsigned char, bool> keys;

// key.cpp
void update(int value);
void keyPressed(unsigned char key, int x, int y);
void keyRelease(unsigned char key, int x, int y);

// mouse.cpp
void mouseClick(int button, int state, int x, int y);

// math.cpp
double mapRange(double input_value, double input_min, double input_max, double output_min, double output_max);
double getDist(double x1, double y1, double z1, double x2, double y2, double z2);

// raycast.cpp
bool rayIntersectsFace(const Vertex& rayOrigin, const Vertex& rayDirection, const Face& face, Vertex& intersectionPoint);
int pickFace(int mouseX, int mouseY);

// parsing.cpp
std::vector<Face> parseOBJ(const std::string& filename);