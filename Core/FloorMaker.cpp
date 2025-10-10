#include "MainRenderer.h"
#include "LoadTexture.h"
#include <GL/glut.h>
#include <iostream>

// Modular floor/platform renderer
void renderFloor(float leftX, float bottomY, float rightX, float topY) {
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.545f, 0.271f, 0.075f); // brown color

    glBegin(GL_QUADS);
        glVertex2f(leftX, bottomY);
        glVertex2f(rightX, bottomY);
        glVertex2f(rightX, topY);
        glVertex2f(leftX, topY);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); // reset color
}
