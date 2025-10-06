#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

struct Player {
    float x;
    float y;
    float vy = 0.0f;      // vertical velocity
    bool onGround = false; // is the player standing on something

    float halfWidth = 100.0f;  // half of sprite width
    float halfHeight = 100.0f; // half of sprite height

    // Update player physics
    void update(float dt, float floorTop);
};

#endif
