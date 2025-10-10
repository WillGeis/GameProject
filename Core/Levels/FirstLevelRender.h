#ifndef FIRST_LEVEL_RENDER_H
#define FIRST_LEVEL_RENDER_H

#include "../FloorMaker.h"   // relative path to FloorMaker.h
#include "../WallMaker.h"    // relative path to WallMaker.h
#include <vector>

inline std::vector<Platform> getFirstLevelPlatforms() {
    return {
        {0, 0, 1920, 50}, // main floor
        {300, 100, 600, 130}, // platform 1
        {800, 200, 1100, 230} // platform 2
    };
}

inline std::vector<WALL> getFirstLevelWalls() {
    return {
        {0, 0, 50, 1080}, // left wall
        {1870, 0, 1920, 1080} // right wall
    };
}

inline void renderFirstLevel() {
    for (const Platform& plat : getFirstLevelPlatforms()) {
        renderFloor(plat.leftX, plat.bottomY, plat.rightX, plat.topY);
    }
}

#endif
