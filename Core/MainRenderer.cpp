#include <iostream>
#include <string>
#include <windows.h>
#include <math.h>
#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "LoadTexture.h"
#include "MainRenderer.h"
#include "MainPlayer.h"
#include "Gravity.h"

// Window dimensions
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

void (*playerRenderCallback)(float, float) = nullptr;

// Draw sprite in the center
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Call the modular render function if set
    if (playerRenderCallback != nullptr) {
        playerRenderCallback(playerX, playerY);
    }

    // -------------------- Floor Renderer --------------------
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.545f, 0.271f, 0.075f);

    int floorHeight = 150;
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(WINDOW_WIDTH, 0);
        glVertex2f(WINDOW_WIDTH, floorHeight);
        glVertex2f(0, floorHeight);
    glEnd();

    // Reset color
    glColor3f(1.0f, 1.0f, 1.0f);

    glFlush();
}


// Setup 2D projection
void setupProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void update() {
    playerY = gravity(playerY);  // Apply gravity
    glutPostRedisplay();         // Tell GLUT to redraw
}

int mainRenderer() {
    int argc = 1;
    char* argv[1] = { (char*)"app" };
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Game Window");

    glClearColor(1,1,1,1);
    setupProjection();

    if (!initPlayerTexture()) {
        std::cerr << "Failed to load character sprite!" << std::endl;
        return -1;
    }

    playerRenderCallback = mainPlayerRender;

    glutDisplayFunc(display);

    glutIdleFunc(update);

    glutMainLoop();
    return 0;
}

