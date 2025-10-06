#include "GameLoop.h"
#include "MainRenderer.h"
#include "MainPlayer.h"
#include <iostream>
#include <thread>
#include <windows.h>
#include <mutex>
#include "PlayerInputHandler.h"

// Global game state
Player player;
std::mutex playerMutex;
int desiredFPS = 60; // note, when I make a pause screen this will be able to be changed by the player

void mainLoop() {
    bool gameOver = false;

    // init player
    player.x = 960.0f;
    player.y = 540.0f;
    player.vy = 0.0f;
    player.onGround = false;

    float floorTop = 150.0f;

    // Start renderer in separate thread theoritically this will allow for multiplayer in the future
    std::thread renderThread(mainRenderer, std::ref(player));

    float dt = 1.0f / desiredFPS;
    int loopnum = 0;

    while (!gameOver) {
        {
            std::lock_guard<std::mutex> lock(playerMutex);

            // Handle player input
            handlePlayerInput(player);

            player.update(dt, floorTop);
        }

        std::cout << "Loop " << loopnum
                  << " — Player at (" << player.x << ", " << player.y
                  << "), vy = " << player.vy
                  << ", onGround = " << player.onGround << std::endl;

        loopnum++;
        Sleep(1000 / desiredFPS);
    }

    renderThread.join();
}
