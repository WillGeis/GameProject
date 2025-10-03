#include<iostream>
#include<string>
#include <windows.h>
#include<math.h>
#include<GL/glut.h>
#include "MainRenderer.h"

void mainLoop(int argc, char** argv)
{
    bool gameOver = false;
    if (gameOver)
    {
        std::cout << "Game Over " << std::endl;
    }
    else
    {
        mainRenderer(argc, argv);
        std::cout << "Game Running " << std::endl;
    }
}

