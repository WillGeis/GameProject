#ifndef WALL_MAKER_H
#define WALL_MAKER_H

struct WALL {
    float leftX;
    float bottomY;
    float rightX;
    float topY;
};

void renderWall(float leftX, float bottomY, float rightX, float topY);

#endif