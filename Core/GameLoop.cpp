#include<iostream>
#include<string>
#include <windows.h>
#include<math.h>
#include<GL/glut.h>
#include "MainRenderer.h"
#include "MainPlayer.h"
#include "Gravity.h"

void mainLoop()
{
    int gameState = 0;
    bool gameOver = false;
    while (!gameOver)
    {
        if (gameState == 0)
        {
            playerX = 960.0f; // Center of 1920 width
            playerY = 540.0f; // Center of 1080 height
            // Initialize game
            gameState = 1; // Move to running state
        }
        if (gameOver)
        {
            std::cout << "Game Over " << std::endl;
        }
        else
        {
            mainRenderer();
            playerY = gravity(playerY);
            std::cout << "Game Running " << std::endl;
        }
    }
}

