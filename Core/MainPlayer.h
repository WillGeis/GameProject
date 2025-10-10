#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H
#include <vector>
#include <algorithm>
#include "FloorMaker.h" // for Platform struct
#include "WallMaker.h"  // for WALL struct

struct Player {
    float x;
    float y;
    float vy = 0.0f;      // vertical velocity
    float vx = 0.0f;      // horizontal velocity
    bool onGround = false; // is the player standing on something

    // movement constants
    const float GRAVITY_ACCEL = -980.0f;
    const float MOVE_ACCEL = 800.0f;     // how quickly the player speeds up
    const float STOP_DECEL = MOVE_ACCEL; // how quickly the player slows down when no input
    const float MAX_MOVE_SPEED = 300.0f; // max horizontal velocity
    const float FRICTION = .99f;        // horizontal slowdown factor
    const float STOP_VELOCITY = 5.0f; // below this horizontal speed, set to 0
    const int SPRITE_WIDTH = 50;
    const int SPRITE_HEIGHT = 50;
    float halfWidth = SPRITE_WIDTH / 2.0f; // half of sprite width
    float halfHeight = SPRITE_HEIGHT / 2.0f; // half of sprite height
    

    // move functions
    void moveLeft(float dt);
    void moveRight(float dt);
    void stopLeft(float dt);
    void stopRight(float dt);

    // Update player physics
    void update(float dt, const std::vector<Platform>& platforms, const std::vector<WALL>& walls);
};

#endif
