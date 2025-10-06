#include "PlayerInputHandler.h"
#include <iostream>
#include <GL/glut.h> // for GLUT key codes

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

// GLUT key press/release callbacks
void keyDown(unsigned char key, int x, int y) {
    keyState[key] = true;
}

void keyUp(unsigned char key, int x, int y) {
    keyState[key] = false;
}

// Framework for player input - add cases as I make more actions
void handlePlayerInput(Player& player) {
    for (auto& [key, action] : keyBindings) {
        if (keyState[key]) {
            std::cout << "Player Input: key='" << key << "' action=";
            switch (action) {
                case PlayerAction::MoveLeft:
                    player.x -= 5.0f;
                    break;
                case PlayerAction::MoveRight:
                    player.x += 5.0f;
                    break;
                case PlayerAction::Jump:
                    if (player.onGround) {
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
