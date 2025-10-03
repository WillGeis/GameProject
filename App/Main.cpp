#include<iostream>
#include<string>
#include <windows.h>
#include<math.h>
#include "GameLoop.h"
#include<GL/glut.h>

int gameState = 0;
int items[10]; // array for item storage 10 is arbirary size

int main(int argc, char** argv)
{
    mainLoop(argc, argv);
    return 0;
}