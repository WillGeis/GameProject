#ifndef FLOOR_MAKER_H
#define FLOOR_MAKER_H

struct Platform {
    float leftX;
    float bottomY;
    float rightX;
    float topY;
};

void renderFloor(float leftX, float bottomY, float rightX, float topY);

#endif