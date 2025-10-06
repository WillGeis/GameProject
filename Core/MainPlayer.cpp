#include "MainPlayer.h"

const float GRAVITY_ACCEL = -980.0f;

void Player::update(float dt, float floorTop) {
    if (!onGround) {
        vy += GRAVITY_ACCEL * dt; // always apply gravity
        y += vy * dt;

        float playerBottom = y - halfHeight;
        if (playerBottom <= floorTop) {
            y = floorTop + halfHeight;
            vy = 0.0f;
            onGround = true; // update global ground status
        }
    }
}
