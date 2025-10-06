#include "MainRenderer.h"
#include "LoadTexture.h"
#include <GL/glut.h>
#include <iostream>

// Floor Renderer
void renderFloor() {
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.545f, 0.271f, 0.075f);

    int floorHeight = 150;
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(WINDOW_WIDTH, 0);
        glVertex2f(WINDOW_WIDTH, floorHeight);
        glVertex2f(0, floorHeight);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
}



// -------------------- First Level Renderer --------------------
void renderFirstLevel() {
    // TODO: Draw more complex level elements here
    renderFloor();
}