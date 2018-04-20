#include <iostream>
#include "SDL.h"
#include "object.h"
#include <ctime>

using namespace std;

// constants
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int GRAVITY = 10;
const int CHAR_WIDTH = 64;
const int CHAR_HEIGHT = 64;
// globals
enum STATE {BUTTON_PRESS, DECELERATE, DESCEND, FREEFALL, READY};
STATE jump = READY;
bool canJump = false;

void update(int* xLoc, int* yLoc, int xSpeed, int ySpeed){
    canJump = false;
    if (xSpeed == 0 && ySpeed == 0)
        return;
    *xLoc = *xLoc + xSpeed;
    if (*xLoc < 0)
        *xLoc = 0;
    if (*xLoc > WINDOW_WIDTH - CHAR_WIDTH)
        *xLoc = WINDOW_WIDTH - CHAR_WIDTH;
    *yLoc = *yLoc + ySpeed;
    if (*yLoc < 0)
        *yLoc = 0;
    if (*yLoc > WINDOW_HEIGHT - CHAR_HEIGHT) {
        *yLoc = WINDOW_HEIGHT - CHAR_HEIGHT;
        canJump = true;
    }
}


int main(int argc, char** argv) {
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        cout << "Something went wrong! " << SDL_GetError() << endl;
    }

    SDL_Window* window = SDL_CreateWindow("SDL_Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if(window == NULL){
        cout << "Something also went wrong here" << endl;
    }

    bool quit = false;
    SDL_Event event;
    int x = 288;
    int y = 208;	
    
    SDL_Renderer* renderer;
    SDL_Renderer* wRender;
    SDL_Event events;
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Rect myRect = {50, 50, CHAR_WIDTH, CHAR_HEIGHT};
    int xSpeed = 0; int ySpeed = 0;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &myRect);
    SDL_RenderPresent(renderer);

    clock_t start; clock_t end;

    while(!quit){
        SDL_PollEvent(&events);
        if(events.type == SDL_QUIT) {
            quit = true;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &myRect);
        const Uint8 *state = SDL_GetKeyboardState(NULL);

        xSpeed = 0; 
        //ySpeed = -GRAVITY;
        // x direction
        if(state[SDL_SCANCODE_A]) {
            xSpeed -= 2;;
        }
        if(state[SDL_SCANCODE_D]) {
            xSpeed += 2;
        }
        // y direction
        if(state[SDL_SCANCODE_W]) {
/*            if (event.type == SDL_KEYDOWN) {
                if (jump == READY) {
                    start = clock();
                    jump = BUTTON_PRESS;
                    canJump = false;
                }
            } else if (event.type == SDL_KEYUP) {
                canJump = true;
            }*/
            
            if (jump == READY) {
                start = clock();
                jump = BUTTON_PRESS;
                //ySpeed += 10;
            }
        }
        // escape
        if(state[SDL_SCANCODE_ESCAPE]) {
            quit = true;
        }

        switch(jump) {
            case BUTTON_PRESS:
//                if (canJump) {
                    ySpeed = -10;
                    end = clock();
                    if ((end - start)/ (double) CLOCKS_PER_SEC > .01) {
                        jump = DECELERATE;
                    }
//                }
                break;
            case DECELERATE  :
                ySpeed += 5;
                if (ySpeed == 0)
                    jump = DESCEND;
                break;
            case DESCEND     :
                ySpeed += 5;
                if (ySpeed == GRAVITY) {
                    jump = FREEFALL;
                    start = clock();
                }
                break;
            case FREEFALL    :
                ySpeed = GRAVITY;
                end = clock();
                if ((end - start)/ (double) CLOCKS_PER_SEC > .05 && canJump) {
                    if (canJump) {
                        jump = READY;
                    }
                }
                break;
            case READY      :
                ySpeed = GRAVITY;
                break;
        }

        // update location based on button press
        update(&myRect.x, &myRect.y, xSpeed, ySpeed);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &myRect);
        SDL_RenderPresent(renderer);
        SDL_PumpEvents();
        SDL_Delay(5);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

