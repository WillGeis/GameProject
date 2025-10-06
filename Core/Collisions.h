#ifndef COLLISIONS_H
#define COLLISIONS_H
#pragma once

void object(float leftX, float rightX, float bottomY, float topY);
int* checkCollision(
    float obj1_leftX, float obj1_rightX, float obj1_bottomY, float obj1_topY,
    float obj2_leftX, float obj2_rightX, float obj2_bottomY, float obj2_topY);

#endif