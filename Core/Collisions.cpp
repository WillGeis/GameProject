#include <iostream>
#include <string>
#include <windows.h>
#include <math.h>
#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION

void object(float leftX, float rightX, float bottomY, float topY)
{
    glBegin(GL_QUADS);
        glVertex2f(leftX, bottomY);
        glVertex2f(rightX, bottomY);
        glVertex2f(rightX, topY);
        glVertex2f(leftX, topY);
    glEnd();
}

bool checkCollision(float obj1_leftX, float obj1_rightX, float obj1_bottomY, float obj1_topY, float obj2_leftX, float obj2_rightX, float obj2_bottomY, float obj2_topY)
{
    bool xOverlap = (obj1_leftX < obj2_rightX) && (obj1_rightX > obj2_leftX); // Check for overlap on the x-axis
    bool yOverlap = (obj1_bottomY < obj2_topY) && (obj1_topY > obj2_bottomY); // Check for overlap on the y-axis
    return xOverlap && yOverlap; // If there's overlap on both axes, a collision has occurred
}