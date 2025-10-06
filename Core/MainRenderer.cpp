#include "MainRenderer.h"
#include "LoadTexture.h"
#include <GL/glut.h>
#include <iostream>
#include <mutex>
#include "GameLoop.h"
#include "PlayerInputHandler.h"
#include "Levels/FirstLevelRender.h"


// Window constants TODO: be able to change resolution at runtime
extern const int WINDOW_WIDTH = 1920;
extern const int WINDOW_HEIGHT = 1080;

// Texture for main character sprite
GLuint characterSpriteTexture;
const char* spritePath = "Sprites/testSprite.png"; //(TODO: make new player sprite)

static Player* activePlayer = nullptr;

// Texture Loader
bool initPlayerTexture() {
    return loadTexture(spritePath, characterSpriteTexture);
}

// Player Renderer (I will likely put this in a separate class later but for now it's fine here)
void mainPlayerRender(Player& player) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, characterSpriteTexture);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const int SPRITE_WIDTH = 200;
    const int SPRITE_HEIGHT = 200;
    float halfW = SPRITE_WIDTH / 2.0f;
    float halfH = SPRITE_HEIGHT / 2.0f;

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(player.x - halfW, player.y - halfH);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(player.x + halfW, player.y - halfH);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(player.x + halfW, player.y + halfH);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(player.x - halfW, player.y + halfH);
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}



// Projection
void setupProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Display
void display() {
    if (!activePlayer) return;
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    renderFloor();

    {
        std::lock_guard<std::mutex> lock(playerMutex);
        mainPlayerRender(*activePlayer);
    }

    glutSwapBuffers();
}

// Entry
int mainRenderer(Player& player) {
    activePlayer = &player;

    int argc = 1;
    char* argv[1] = {(char*)"app"};
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Game Window");

    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);

    // TODO: implement special key handling (arrow keys, etc)
    //glutSpecialFunc(specialKeyDown);
    //glutSpecialUpFunc(specialKeyUp);


    glClearColor(1,1,1,1);
    setupProjection();

    if (!initPlayerTexture()) {
        std::cerr << "Failed to load character sprite!\n";
        return -1;
    }

    glutDisplayFunc(display);
    glutIdleFunc([](){ glutPostRedisplay(); });
    glutMainLoop();

    return 0;
}
