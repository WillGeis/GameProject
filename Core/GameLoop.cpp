#include "GameLoop.h"
#include "MainRenderer.h"
#include "MainPlayer.h"
#include "PlayerInputHandler.h"
#include <iostream>
#include <thread>
#include <windows.h>
#include <mutex>
#include "Levels/FirstLevelRender.h"

// Global game state
Player player;
std::mutex playerMutex;
int desiredFPS = 60;
float dt = 1.0f / desiredFPS; // note, when I make a pause screen this will be able to be changed by the player, accessible to PlayerInputHandler

void mainLoop() 
{
    bool gameOver = false;

    // Init player
    player.orientation = 1; // facing right
    player.x = 960.0f;
    player.y = 540.0f;
    player.vy = 0.0f;
    player.vx = 0.0f;
    player.onGround = false;

    // Start renderer thread
    std::thread renderThread(mainRenderer, std::ref(player));
    int loopnum = 0;

    while (!gameOver) {
        {
            std::lock_guard<std::mutex> lock(playerMutex);

            // Handle input
            handlePlayerInput(player);

            // Handle deceleration if keys are NOT pressed
            if (!isKeyPressed('a') && player.vx < 0) {
                player.stopLeft(dt);
            }
            if (!isKeyPressed('d') && player.vx > 0) {
                player.stopRight(dt);
            }

            std::vector<WALL> walls = getFirstLevelWalls();
            std::vector<Platform> platforms = getFirstLevelPlatforms();

            // Update physics
            player.update(dt, platforms, walls);
        }

        loopnum++;
        Sleep(1000 / desiredFPS);
    }

    renderThread.join();
}
