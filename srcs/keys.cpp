
#include "scop.hpp"

void update(int value)
{
    (void)value;
    float moveSpeed = 0.1f;
    float turnSpeed = 0.02f;

    if (keys['z']) {
        cam_x += cosf(yaw) * cosf(pitch) * moveSpeed;
        cam_y += sinf(pitch) * moveSpeed;
        cam_z += sinf(yaw) * cosf(pitch) * moveSpeed;
    }
    if (keys['s']) {
        cam_x -= cosf(yaw) * cosf(pitch) * moveSpeed;
        cam_y -= sinf(pitch) * moveSpeed;
        cam_z -= sinf(yaw) * cosf(pitch) * moveSpeed;
    }
    if (keys[' '])
    {
        cam_y += moveSpeed;
    }
    if (keys['c'])
    {
        cam_y -= moveSpeed;
    }

    if (keys['q']) {
        cam_x -= cosf(yaw + 3.14159f / 2.0f) * moveSpeed;
        cam_z -= sinf(yaw + 3.14159f / 2.0f) * moveSpeed;
    }
    if (keys['d']) {
        cam_x += cosf(yaw + 3.14159f / 2.0f) * moveSpeed;
        cam_z += sinf(yaw + 3.14159f / 2.0f) * moveSpeed;
    }

    if (keys['o']) {
        pitch += turnSpeed;
        if (pitch > 1.5f) pitch = 1.5f;
    }

    if (keys['n']) {
        for (auto it = isFaceSelected.begin(); it != isFaceSelected.end(); it++)
            if ((*it).second)
                faces[(*it).first].moveAmongNormal(0.1f);
        for (auto it = isFaceSelected.begin(); it != isFaceSelected.end(); it++)
            if ((*it).second)
                faces[(*it).first].moveVerticesAlongAveragedNormal(0.1f);
        for (auto it = vertices.begin(); it != vertices.end(); it++)
            (*it).get()->resetAccumulatedNormal();
    }
    if (keys['b']) {
        for (auto it = isFaceSelected.begin(); it != isFaceSelected.end(); it++)
            if ((*it).second)
                faces[(*it).first].moveAmongNormal(-0.1f);
        for (auto it = isFaceSelected.begin(); it != isFaceSelected.end(); it++)
            if ((*it).second)
                faces[(*it).first].moveVerticesAlongAveragedNormal(-0.1f);
        for (auto it = vertices.begin(); it != vertices.end(); it++)
            (*it).get()->resetAccumulatedNormal();
    }
    if (keys['l']) {
        pitch -= turnSpeed;
        if (pitch < -1.5f) pitch = -1.5f;
    }
    if (keys['u'])
        isFaceSelected.clear();
    if (keys['a'])
    {
        for (size_t i = 0; i < faces.size(); i++)
            isFaceSelected[i] = true;
    }
    if (keys['m']) {
        yaw += turnSpeed;
    }
    if (keys['k']) {
        yaw -= turnSpeed;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyRelease(unsigned char key, int x, int y)
{
    keys[key] = false;
    (void)x;
    (void)y;
}

void keyPressed(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
    keys[key] = true;
    (void)x;
    (void)y;
}