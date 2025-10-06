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

// Returns int[2] = { viableX, viableY } this is the position the player can move to without colliding
// If no collision, returns {-1, -1}
int* checkCollision(
    float obj1_leftX, float obj1_rightX, float obj1_bottomY, float obj1_topY,
    float obj2_leftX, float obj2_rightX, float obj2_bottomY, float obj2_topY)
{
    static int result[2] = { 0, 0 }; // return by pointer
    result[0] = -1; // viableX
    result[1] = -1; // viableY

    bool xOverlap = (obj1_leftX < obj2_rightX) && (obj1_rightX > obj2_leftX);
    bool yOverlap = (obj1_bottomY < obj2_topY) && (obj1_topY > obj2_bottomY);

    if (xOverlap && yOverlap)
    {
        // Determine vertical or horizontal collision direction
        float overlapBottom = obj2_topY - obj1_bottomY;
        float overlapTop    = obj1_topY - obj2_bottomY;

        // If overlapBottom < overlapTop then player is above the object
        if (overlapBottom > 0 && overlapBottom < overlapTop) {
            result[1] = static_cast<int>(obj2_topY); // Viable Y = object top
        }

        else if (overlapTop > 0 && overlapTop < overlapBottom) {
            result[1] = static_cast<int>(obj2_bottomY); // Hit from below
        }

        // Horizontal collisions (optional, for walls)
        float overlapLeft  = obj1_rightX - obj2_leftX;
        float overlapRight = obj2_rightX - obj1_leftX;
        if (overlapLeft > 0 && overlapLeft < overlapRight) {
            result[0] = static_cast<int>(obj2_leftX);
        } else if (overlapRight > 0 && overlapRight < overlapLeft) {
            result[0] = static_cast<int>(obj2_rightX);
        }
    }

    return result;
}