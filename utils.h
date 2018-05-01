#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include "SDL.h"
#include <ctime>
#include <chrono>
#include <vector>
#include "math.h"

using namespace std;
namespace sc = std::chrono;

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

const int GRAVITY[] = {4,4,5,6,8,10,11,13,15,18};
const int GRAV_LEN = sizeof(GRAVITY)/ sizeof(GRAVITY[0]);
const int CHAR_WIDTH = 42;
const int CHAR_HEIGHT = 64;
const int FRAMES_PER_SEC = 20;
const int LEFT = 0;
const int RIGHT = 1;
const int TOP = 2;
const int BOTTOM = 3;

enum STATE {BUTTON_PRESS, DECELERATE, DESCEND, FREEFALL, READY};

#define KEY_W 0
#define KEY_A 1
#define KEY_D 2
#define KEY_S 3
#define LEFT_MOUSE 4
#define RIGHT_MOUSE 5
#define KEY_LEFT 6
#define KEY_RIGHT 7

#endif
