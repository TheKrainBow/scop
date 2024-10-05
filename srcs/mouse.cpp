#include "scop.hpp"

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Perform picking
        int lastClickedFace = pickFace(x, y);  // Implement the pickFace function
        if (lastClickedFace != -1) {
            std::cout << "Face " << lastClickedFace << " was clicked." << std::endl;
            isFaceSelected[lastClickedFace] = !isFaceSelected[lastClickedFace];
        }
    }
}