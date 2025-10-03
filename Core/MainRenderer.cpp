#include <iostream>
#include <string>
#include <windows.h>
#include <math.h>
#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Window dimensions
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

// Texture ID
GLuint spriteTexture;

// Sprite path
const char* spritePath = "Sprites/testSprite.png";

// Sprite size
const int SPRITE_WIDTH = 200;
const int SPRITE_HEIGHT = 200;

// Load texture from file
bool loadTexture(const char* path, GLuint& textureID) {
    int width, height, channels;
    unsigned char* image = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
    if (!image) {
        std::cerr << "Failed to load image: " << path << std::endl;
        return false;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    stbi_image_free(image);
    return true;
}

// Draw sprite in the center
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, spriteTexture);

    // Enable blending for PNG transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float x_center = WINDOW_WIDTH / 2.0f;
    float y_center = WINDOW_HEIGHT / 2.0f;
    float halfW = SPRITE_WIDTH / 2.0f;
    float halfH = SPRITE_HEIGHT / 2.0f;

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x_center - halfW, y_center - halfH);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x_center + halfW, y_center - halfH);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x_center + halfW, y_center + halfH);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x_center - halfW, y_center + halfH);
    glEnd();

    glDisable(GL_BLEND); // disable blending after drawing
    glDisable(GL_TEXTURE_2D);

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

// Function to initialize renderer (called from main)
int mainRenderer(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Game Window");

    // White background
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    setupProjection();

    if (!loadTexture(spritePath, spriteTexture)) {
        return -1;
    }

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
