#include "scop.hpp"

// Rotation angle for the cube

void camera() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float dirx = cosf(yaw) * cosf(pitch);
    float diry = sinf(pitch);
    float dirz = sinf(yaw) * cosf(pitch);
    gluLookAt(cam_x, cam_y, cam_z, cam_x + dirx, cam_y + diry, cam_z + dirz, 0.0f, 1.0f, 0.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera();
    int i = 0;
    for (auto it = faces.begin(); it != faces.end(); it++)
    {
        if ((*it)._vertices.size() == 3)
            glBegin(GL_TRIANGLES);
        else if ((*it)._vertices.size() == 4)
            glBegin(GL_QUADS);
        else
            glBegin(GL_POLYGON);
        if (isFaceSelected[i])
            glColor3f(1.0f, 0.0f, 0.0f);
        else
        {
            // double gray = mapRange(getDist(cam_x, cam_y, cam_z, (*it)._x, (*it)._y, (*it)._z), 0, 100, 0, 1);
            // glColor3f(gray, gray, gray);
            glColor3f((*it)._red, (*it)._green, (*it)._blue);
        }

        for (auto itt = (*it)._vertices.begin(); itt < (*it)._vertices.end(); itt++)
            glVertex3f((*itt)->_x, (*itt)->_y,  (*itt)->_z);
        glEnd();
        i++;
    }
    glutSwapBuffers();
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}


void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int ac, char** av)
{
    if (ac != 2)
    {
        std::cerr << "Not enough arguments" << std::endl;
        return 1;
    }
    faces = parseOBJ(av[1]);
    if (faces.size() == 0)
        return 1;
    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow(av[1]);

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyRelease);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseClick);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
