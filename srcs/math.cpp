#include "scop.hpp"

double mapRange(double input_value, double input_min, double input_max, double output_min, double output_max) {
    // std::cout << input_value << std::endl;
    return ((input_value - input_min) / (input_max - input_min)) * (output_max - output_min) + output_min;
}

double getDist(double x1, double y1, double z1, double x2, double y2, double z2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
}