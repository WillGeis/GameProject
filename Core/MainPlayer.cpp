#include <iostream>
#include <string>
#include <windows.h>
#include <math.h>
#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "LoadTexture.h"

// Texture ID
GLuint characterSpriteTexture;

// Sprite path
const char* spritePath = "Sprites/testSprite.png";

float playerX;
float playerY;

// Sprite size
const int SPRITE_WIDTH = 200;
const int SPRITE_HEIGHT = 200;

bool initPlayerTexture() {
    return loadTexture(spritePath, characterSpriteTexture);
}

void mainPlayerRender(float playerX, float playerY)
{
    // -------------------- Sprite Renderer --------------------

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, characterSpriteTexture);

    // Enable blending for PNG transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Calculate half dimensions for centering
    float halfW = SPRITE_WIDTH / 2.0f;
    float halfH = SPRITE_HEIGHT / 2.0f;

    // bottom left of the window is vertex postion (0,0)
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(playerX - halfW, playerY - halfH);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(playerX + halfW, playerY - halfH);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(playerX + halfW, playerY + halfH);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(playerX - halfW, playerY + halfH);
    glEnd();

    glDisable(GL_BLEND); // disable blending after drawing
    glDisable(GL_TEXTURE_2D);

    glFlush();
}