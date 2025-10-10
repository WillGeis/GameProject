#ifndef PLAYER_INPUT_HANDLER_H
#define PLAYER_INPUT_HANDLER_H

#include "MainPlayer.h"
#include <map>

enum class PlayerAction {
    MoveLeft,
    MoveRight,
    Jump,
    OpenInventory
};

void keyDown(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void handlePlayerInput(Player& player);

bool isKeyPressed(unsigned char key);

#endif
