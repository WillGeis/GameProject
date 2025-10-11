#include "MainRenderer.h"
#include "LoadTexture.h"
#include <GL/glut.h>
#include <iostream>
#include <mutex>
#include "GameLoop.h"
#include "MainPlayer.h"
#include "PlayerInputHandler.h"
#include "Levels/FirstLevelRender.h"


// Window constants TODO: be able to change resolution at runtime
extern const int WINDOW_WIDTH = 1920;
extern const int WINDOW_HEIGHT = 1080;

// Texture for main character sprite
GLuint characterSpriteTexture, runTexture1, runTexture2, jumpTexture;
const char* spritePath = "Sprites/testSprite.png"; //(TODO: make new player sprite)
const char* runPath1 = "Sprites/testSpriteRun1.png";
const char* runPath2 = "Sprites/testSpriteRun2.png";
const char* jumpPath = "Sprites/testSpriteJump.png";

static Player* activePlayer = nullptr;
static int frameCounter = 0;

// Texture Loader
bool initPlayerTexture() {
    bool ok = true;
    ok &= loadTexture(spritePath, characterSpriteTexture);
    ok &= loadTexture(runPath1, runTexture1);
    ok &= loadTexture(runPath2, runTexture2);
    ok &= loadTexture(jumpPath, jumpTexture);
    return ok;
}

// Player Renderer (I will likely put this in a separate class later but for now it's fine here)
void renderPlayerSprite(const Player& player, int orientation, GLuint textureID) {
    float halfW = player.halfWidth;
    float halfH = player.halfHeight;

    glEnable(GL_TEXTURE_2D);// enable textures
    glEnable(GL_BLEND); // enable blending for transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // standard alpha blend

    glBindTexture(GL_TEXTURE_2D, textureID);
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(player.x, player.y, 0.0f);

    if (orientation == -1 || orientation == -2) {
        glScalef(-1.0f, 1.0f, 1.0f); // flip horizontally for left-facing sprite
    }

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-halfW, -halfH);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( halfW, -halfH);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( halfW,  halfH);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-halfW,  halfH);
    glEnd();

    glPopMatrix();

    glDisable(GL_BLEND);// clean up state
    glDisable(GL_TEXTURE_2D);
}


void mainPlayerRender(Player& player) {
    GLuint tex = characterSpriteTexture;

    // Jumping takes precedence over running
    if (!player.onGround) {
        tex = jumpTexture;
    } 
    else if (player.orientation == 2 || player.orientation == -2) { // running right or left
        frameCounter++;
        if ((frameCounter / 10) % 2 == 0)
            tex = runTexture1;
        else
            tex = runTexture2;
    }

    renderPlayerSprite(player, player.orientation, tex);
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

    renderFirstLevel();

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


    glClearColor(1, 1, 1, 1);
    setupProjection();

    if (!initPlayerTexture()) {
        std::cerr << "Failed to load character sprite!\n";
        return -1;
    }

    glutDisplayFunc(display);
    glutIdleFunc([]() { glutPostRedisplay(); });
    glutMainLoop();

    return 0;
}


