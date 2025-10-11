#include "PlayerInputHandler.h"
#include <iostream>
#include <GL/glut.h> // for GLUT key codes

extern float dt; // delta time from GameLoop

// Key-to-action mapping (can be modified at runtime, will have other functions later)
std::map<unsigned char, PlayerAction> keyBindings = {
    {'a', PlayerAction::MoveLeft},
    {'d', PlayerAction::MoveRight},
    {'w', PlayerAction::Jump},
    {' ', PlayerAction::Jump},
    {'e', PlayerAction::OpenInventory}
};

// Track which keys are currently pressed
std::map<unsigned char, bool> keyState;

bool isKeyPressed(unsigned char key) {
    return keyState[key];
}

// GLUT key press/release callbacks
void keyDown(unsigned char key, int x, int y) {
    keyState[key] = true;
}

void keyUp(unsigned char key, int x, int y) {
    keyState[key] = false;

    switch (key) {
        case 'a':
            std::cout << "[Input] Stopping Left\n";
            extern Player player;
            player.stopLeft(dt);
            break;
        case 'd':
            std::cout << "[Input] Stopping Right\n";
            extern Player player;
            player.stopRight(dt);
            break;
        default:
            break;
    }
}

// Framework for player input - add cases as I make more actions
void handlePlayerInput(Player& player) {
    for (auto& [key, action] : keyBindings) {
        if (keyState[key]) {
            switch (action) {
                case PlayerAction::MoveLeft:
                    player.moveLeft(dt);
                    break;
                case PlayerAction::MoveRight:
                    player.moveRight(dt);
                    break;
                case PlayerAction::Jump:
                    if (player.onGround) {
                        player.orientation = 0; // jumping
                        player.vy = 500.0f;
                        player.onGround = false;
                    }
                    break;
                case PlayerAction::OpenInventory:
                    std::cout << "[PlayerInputHandler] Opening Armor Inventory!\n";
                    break;
            }
        }
    }
}
