#include "MainPlayer.h"
#include "MainRenderer.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <thread>
#include "Collisions.h"
#include "FloorMaker.h"
#include "Levels/FirstLevelRender.h"
#include <vector>
#include "WallMaker.h"


void Player::moveLeft(float dt) {
    orientation = -2; // moving left
    vx -= MOVE_ACCEL * dt;
    vx = std::clamp(vx, -MAX_MOVE_SPEED, MAX_MOVE_SPEED);
}

void Player::stopLeft(float dt) {
    if (vx < 0)
    {
        vx += STOP_DECEL * dt;
        if (vx > (STOP_VELOCITY * -1))
        {
            orientation = -1; // facing left
            vx = 0.0f; // prevent overshoot
        }
    }
}

void Player::moveRight(float dt) {
    orientation = 2; // moving right
    vx += MOVE_ACCEL * dt;
    vx = std::clamp(vx, -MAX_MOVE_SPEED, MAX_MOVE_SPEED);
}

void Player::stopRight(float dt) {
    if (vx > 0)
    {
        vx -= STOP_DECEL * dt;
        if (vx < STOP_VELOCITY) 
        {
            orientation = 1; // facing right
            vx = 0.0f;
        }
    }
}

void Player::update(float dt, const std::vector<Platform>& platforms, const std::vector<WALL>& walls) {
    // Apply gravity
    vy += GRAVITY_ACCEL * dt;
    y += vy * dt; // move vertically first

    // Horizontal movement
    x += vx * dt;

    // Reset ground status
    onGround = false;

    float playerBottom = y - halfHeight;
    float playerTop    = y + halfHeight;
    float playerLeft   = x - halfWidth;
    float playerRight  = x + halfWidth;

    // Check vertical collisions with platforms
    for (const Platform& plat : platforms) {
        float playerBottom = y - halfHeight;
        float playerTop = y + halfHeight;
        float playerLeft = x - halfWidth;
        float playerRight = x + halfWidth;

        bool xOverlap = (playerRight > plat.leftX) && (playerLeft < plat.rightX);

        if (xOverlap) {
            // Landing on top
            if (vy <= 0 && playerBottom <= plat.topY && playerBottom >= plat.topY - 10) {
                y = plat.topY + halfHeight; // bottom of sprite on top of platform
                vy = 0.0f;
                onGround = true;
            }

            // Hitting head from below
            if (vy > 0 && playerTop >= plat.bottomY && playerTop <= plat.bottomY + 10) {
                y = plat.bottomY - halfHeight; // top of sprite hits bottom of platform
                vy = 0.0f;
            }
        }
    }

    // Check horizontal collisions with platforms
    for (const WALL& wall : walls) {
        bool yOverlap = (playerTop > wall.bottomY) && (playerBottom < wall.topY);

        if (yOverlap) {
            // Hitting left side of wall
            if (vx > 0 && playerRight >= wall.leftX && playerLeft < wall.leftX) {
                x = wall.leftX - halfWidth; // snap to left of wall
                vx = 0.0f;
                playerLeft = x - halfWidth;
                playerRight = x + halfWidth;
            }

            // Hitting right side of wall
            if (vx < 0 && playerLeft <= wall.rightX && playerRight > wall.rightX) {
                x = wall.rightX + halfWidth; // snap to right of wall
                vx = 0.0f;
                playerLeft = x - halfWidth;
                playerRight = x + halfWidth;
            }
        }
    }
}
