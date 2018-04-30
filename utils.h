#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include "SDL.h"
#include <ctime>
#include <chrono>
#include <vector>

using namespace std;
namespace sc = std::chrono;

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

const int GRAVITY = 10;
const int CHAR_WIDTH = 43;
const int CHAR_HEIGHT = 64;
const int FRAMES_PER_SEC = 20;

enum STATE {BUTTON_PRESS, DECELERATE, DESCEND, FREEFALL, READY};

#define KEY_W 0
#define KEY_A 1
#define KEY_D 2
#define KEY_S 3
#define KEY_LEFT 4
#define KEY_RIGHT 5

#endif