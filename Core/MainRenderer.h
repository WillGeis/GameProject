#ifndef MAIN_RENDERER_H
#define MAIN_RENDERER_H

#include "MainPlayer.h"

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

bool initPlayerTexture();
void mainPlayerRender(Player& player);
int mainRenderer(Player& player);

#endif
