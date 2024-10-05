#include "scop.hpp"

bool rayIntersectsFace(const Vertex& rayOrigin, const Vertex& rayDirection, const Face& face, Vertex& intersectionPoint) {
    if (face._vertices.size() < 3) return false; // Ignore faces with less than 3 vertices

    bool hit = false;
    Vertex tempIntersection;
    double closestT = std::numeric_limits<double>::max();  // Keep track of the closest intersection

    // Triangulate the face and check for intersection with each triangle
    Vertex v0 = *face._vertices[0];

    for (size_t i = 1; i < face._vertices.size() - 1; i++) {
        Vertex v1 = *face._vertices[i];
        Vertex v2 = *face._vertices[i + 1];

        // Calculate edge vectors and the normal of the triangle
        Vertex edge1 = v1 - v0;
        Vertex edge2 = v2 - v0;
        Vertex h = rayDirection.cross(edge2);
        double a = edge1.dot(h);

        if (fabs(a) < 1e-5) continue;  // Ray is parallel to the triangle, skip

        double f = 1.0 / a;
        Vertex s = rayOrigin - v0;
        double u = f * s.dot(h);

        if (u < 0.0 || u > 1.0) continue;  // Intersection outside the triangle

        Vertex q = s.cross(edge1);
        double v = f * rayDirection.dot(q);

        if (v < 0.0 || u + v > 1.0) continue;  // Intersection outside the triangle

        // At this stage, the ray intersects the triangle
        double t = f * edge2.dot(q);
        if (t > 1e-5 && t < closestT) {
            closestT = t;
            tempIntersection = rayOrigin + rayDirection * t;
            hit = true;
        }
    }

    if (hit) {
        intersectionPoint = tempIntersection;
    }

    return hit;
}

int pickFace(int mouseX, int mouseY) {
    // Get the current viewport and projection matrix
    int viewport[4];
    double modelview[16];
    double projection[16];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    // Invert the Y coordinate to match OpenGL's coordinate system
    mouseY = viewport[3] - mouseY;

    // Convert 2D mouse coordinates to 3D coordinates (ray origin and direction)
    double nearX, nearY, nearZ;
    double farX, farY, farZ;

    // Unproject the mouse position into world coordinates
    gluUnProject(mouseX, mouseY, 0.0, modelview, projection, viewport, &nearX, &nearY, &nearZ);
    gluUnProject(mouseX, mouseY, 1.0, modelview, projection, viewport, &farX, &farY, &farZ);

    // Ray origin and direction
    Vertex rayOrigin(nearX, nearY, nearZ);
    Vertex rayDirection(farX - nearX, farY - nearY, farZ - nearZ);

    // Normalize the ray direction
    rayDirection.normalize();
    int closestFaceIndex = -1;
    double closestDistance = std::numeric_limits<double>::max(); // Initialize with max value

    // Check for intersections with each face
    for (size_t i = 0; i < faces.size(); i++) {
        Vertex intersectionPoint;
        if (rayIntersectsFace(rayOrigin, rayDirection, faces[i], intersectionPoint)) {
            // Calculate the distance from the ray origin to the intersection point
            double distance = (intersectionPoint - rayOrigin).length();
            if (distance < closestDistance) {
                closestDistance = distance; // Update the closest distance
                closestFaceIndex = i; // Update the index of the closest face
            }
        }
    }
    return closestFaceIndex; 
}