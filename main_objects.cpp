#include <iostream>
#include "SDL.h"
#include <ctime>
#include <chrono>
#include "block.h"
#include "player.h"
#include "block.cpp"
#include "player.cpp"
#include "portal.h"
#include "portal.cpp"

#define KEY_W 0
#define KEY_A 1
#define KEY_D 2
#define KEY_S 3

using namespace std;
namespace sc = std::chrono;

// constants
#ifndef WINDOW_SIZE
#define WINDOW_SIZE
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
#endif
const int GRAVITY = 10;
const int CHAR_WIDTH = 64;
const int CHAR_HEIGHT = 64;
const int FRAMES_PER_SEC = 20;

// globals
enum STATE {BUTTON_PRESS, DECELERATE, DESCEND, FREEFALL, READY};
STATE jump = READY;
bool canJump = false;
bool ground = true;
auto frameStart = sc::high_resolution_clock::now();
auto frameEnd = sc::high_resolution_clock::now();

// void update(int* xLoc, int* yLoc, int xSpeed, int ySpeed){
//     if (xSpeed == 0 && ySpeed == 0)
//         return;
//     *xLoc = *xLoc + xSpeed;
//     if (*xLoc < 0)
//         *xLoc = 0;
//     if (*xLoc > WINDOW_WIDTH - CHAR_WIDTH)
//         *xLoc = WINDOW_WIDTH - CHAR_WIDTH;
//     *yLoc = *yLoc + ySpeed;
//     if (*yLoc < 0)
//         *yLoc = 0;
//     if (*yLoc > WINDOW_HEIGHT - CHAR_HEIGHT) {
//         *yLoc = WINDOW_HEIGHT - CHAR_HEIGHT;
//         ground = true;
//     }
// }

int main(int argc, char** argv) {
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        cout << "Something went wrong! " << SDL_GetError() << endl;
    }

    SDL_Window* window = SDL_CreateWindow("SDL_Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if(window == NULL){
        cout << "Something also went wrong here" << endl;
    }

    int pastPress[] = {0,0,0,0};
    int jumpframes = 0;
    bool quit = false;
    SDL_Event event;
    int x = 288;
    int y = 208;	
    
    SDL_Renderer* renderer;
    SDL_Event events;
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // player
    SDL_Rect myRect = {50, 50, CHAR_WIDTH, CHAR_HEIGHT};
    Player player(50, 50, CHAR_WIDTH, CHAR_HEIGHT, renderer, myRect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &myRect);
    SDL_RenderPresent(renderer);

    // block
    SDL_Rect blockRect = {200, 400, 600, 220};
    Block block(200, 400, 600, 220, renderer, blockRect);
    //SDL_SetRenderDrawColor(renderer, 47, 79, 79, 255);
    //SDL_RenderFillRect(renderer, &blockRect);
    //SDL_RenderPresent(renderer);

    Portal portal(0, 0, renderer);
    portal.toggleClick();
    portal.draw(100, 100, 0);


    block.draw();
    //SDL_RenderFillRect(renderer, &myRect);


    //int xSpeed = 0; int ySpeed = 0;
    long int delayTime;
    clock_t start; clock_t end;

    int count = 0;

    while(!quit){
	    frameStart = sc::high_resolution_clock::now();
        SDL_PollEvent(&events);
        if(events.type == SDL_QUIT) {
            quit = true;
        }

        // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // SDL_RenderFillRect(renderer, &myRect);

        const Uint8 *state = SDL_GetKeyboardState(NULL);

        // xSpeed = 0;
        player.setXSpeed(0);
        // x direction
        if(state[SDL_SCANCODE_A]) {
            // xSpeed -= 5;
            player.changeXSpeed(-5);
        }
        if(state[SDL_SCANCODE_D]) {
            // xSpeed += 5;
            player.changeXSpeed(5);
        }

        // y direction
        if(state[SDL_SCANCODE_W]) {
    		++pastPress[KEY_W];
    		if(pastPress[KEY_W] == 1) {
    			canJump = true;
    		}
            if (jump == READY) {
                start = clock();
                jump = BUTTON_PRESS;
                //ySpeed += 10;
            }
        } else {
    		pastPress[KEY_W] = 0;
    		canJump = true;
	    }
        if(!state[SDL_SCANCODE_W]) {
            canJump = true;
        }

        // escape
        if(state[SDL_SCANCODE_ESCAPE]) {
            quit = true;
        }
 
        // jump state machine
        switch(jump) {
            case BUTTON_PRESS:
    		    canJump = false;
                player.setYSpeed(-16);
    		    // ySpeed = -16;
                end = clock();
                if (jumpframes > 10) {
                    jumpframes = 0;
		            jump = DECELERATE;
                }
    		    ++jumpframes;
    		    // ground = false;
                break;
            case DECELERATE  :
                player.changeYSpeed(2);
                // ySpeed += 2;
                // if (ySpeed <= 0){
                if (player.getYSpeed() <= 0) {
                    // ySpeed = 0;
                    player.setYSpeed(0);
		            jump = DESCEND;
		        }
                break;
            case DESCEND     :
                player.changeYSpeed(5);
                // ySpeed += 5;
                // if (ySpeed == GRAVITY) {
                if (player.getYSpeed() == GRAVITY) {
                    jump = FREEFALL;
                    start = clock();
                }
                break;
            case FREEFALL    :
                player.setYSpeed(GRAVITY);
                // ySpeed = GRAVITY;
                if (canJump && ground) {
                    if (canJump) {
                        jump = READY;
                    }
                }
                break;
            case READY      :
                player.setYSpeed(GRAVITY);
                // ySpeed = GRAVITY;
                break;
        }

        count++;
        if (count % 1000 == 0) {
            count = 0;
            portal.toggleClick();
            portal.draw(100, 100, 0);
        }

        // update location based on button press
        // update(&myRect.x, &myRect.y, xSpeed, ySpeed);
        player.update();
        player.draw();

        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        // SDL_RenderFillRect(renderer, &myRect);
        SDL_RenderPresent(renderer);
    	frameEnd = sc::high_resolution_clock::now();
    	delayTime = 16 - sc::duration_cast<sc::milliseconds>(frameEnd-frameStart).count(); 
    	if(delayTime > 0) {
    	    SDL_Delay(delayTime);
    	}
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

