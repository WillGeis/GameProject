#include "Gravity.h"

// Gravity acceleration in units per second^2
const float GRAVITY_ACCEL = -980.0f; // negative because Y goes up

// NOTE: Physics may need to be adjusted based on frame rate for consistency or something else that will do a calculation on runtime based on frame rate


void applyGravity(Player& player, float dt)
{
    if (!player.onGround) {
        // Update vertical velocity
        player.vy += GRAVITY_ACCEL * dt;

        // Update position
        player.y += player.vy * dt;
    }
}
