#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "MainPlayer.h"
#include <mutex>

extern Player player;
extern std::mutex playerMutex;

void mainLoop();

#endif
