#include <iostream>
#include "SDL.h"
#include "object.h"
#include <ctime>
#include <chrono>
using namespace std;
namespace sc = std::chrono;
// constants
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
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
#define KEY_W 0
#define KEY_A 1
#define KEY_D 2
#define KEY_S 3

void update(int* xLoc, int* yLoc, int xSpeed, int ySpeed){
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
        ground = true;
    }
}

void CheckCollision(const SDL_Rect &rect1, const SDL_Rect &rect2, int* playerX, int* playerY, int xSpeed, int ySpeed)
{
    // Find edges of rect1
    // int left1 = rect1.x;                    // playerx
    // int right1 = rect1.x + rect1.w;         // playerx+width
    // int top1 = rect1.y;                     // playerY
    // int bottom1 = rect1.y + rect1.h;        // playerY+height

    // Find edges of rect2
    int left2 = rect2.x;                    // blockX
    int right2 = rect2.x + rect2.w;         // blockX+width
    int top2 = rect2.y;                     // blockY          
    int bottom2 = rect2.y + rect2.h;        // blocky+height

    // use future positions of the player
    int left1 = rect1.x + xSpeed;
    int right1 = rect1.x + rect1.w + xSpeed;
    int top1 = rect1.y + ySpeed;
    int bottom1 = rect1.y + rect1.h + ySpeed;

        // Check edges
    if ( left1 > right2 )// Left 1 is right of right 2
        return; // No collision

    if ( right1 < left2 ) // Right 1 is left of left 2 
        return; // No collision 

    if ( top1 > bottom2 ) // Top 1 is below bottom 2
        return; // No collision

    if ( bottom1 < top2 ) // Bottom 1 is above top 2
        return; // No collision 

    if (right1 >= left2 && left1 <= right2 && top1 <= top2)
    {
        *playerY = top2 - rect1.h - 10;
        ySpeed = 0;
        ground = true;
    }

    if (right1 >= left2 && left1 <= right2 && bottom1 >= bottom2)
    {
        *playerY = bottom2 + 10;         // add some constant value because it clips otherwise
        ySpeed = 0;
        ground = true;
    }

    // block is below player?
    if (top1 <= bottom2 && bottom1 >= top2 && left1 <= left2)
    {
        *playerX = left2 - rect1.w - 5;
        xSpeed = 0;   
    }

    if (top1 <= bottom2 && bottom1 >= top2 && right1 >= right2)
    {
        *playerX = right2 + 5;
        xSpeed = 0;
    }



    // bool rb = false;
    // bool lb = false;
    // bool tr = false;
    // bool tl = false;

    // // playerX >= blockX && playerX <= blockX+width && playerY >= blockY && playerY <= blockY+height
    // if (left1 >= left2 && left1 <= right2 && top1 >= top2 && top1 <= bottom2)
    //     rb = true;
    // //  playerX+width >= blockX && playerX+width <= blockX+width && playerY >= blockY && playerY <= blockY+height
    // if (right1 >= left2 && right1 <= right2 && top1 >= top2 && top1 <= bottom2)
    //     lb = true;
        
    // //playerX >= blockX && playerX <= blockX+width && playerY+height >= blockY && playerY+height <= blockY+height
    // if (left1 >= left2 && left1 <= right2 && bottom1 >= top2 && bottom1 <= bottom2)
    //     tr = true;

    // // playerX+width >= blockX && playerX+width <= blockX+width && playerY+height >= blockY && playerY+height <= blockY+height
    // if (right1 >= left2 && right1 <= right2 && bottom1 >= top2 && bottom1 <= bottom2)
    //     tl = true;

    // if (rb && lb)                   // if bottom
    //     *playerY = bottom2 + 10;         // add some constant value because it clips otherwise
    //     ySpeed = 0;
    // if (rb && tr)                   // if right
    //     *playerX = right2 + 5;
    //     xSpeed = 0;    
    // if (tr && tl)                   // if top
    //     *playerY = top2 - rect1.h - 10;
    //     ySpeed = 0;
    // if (lb && tl)                   // if left
    //     *playerX = left2 - rect1.w - 5;
    //     xSpeed = 0;     
}




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
    SDL_Renderer* wRender;
    SDL_Event events;
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Rect myRect = {600, 100, CHAR_WIDTH, CHAR_HEIGHT};
    int xSpeed = 0; int ySpeed = 0;
    long int delayTime;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &myRect);
    SDL_RenderPresent(renderer);

    clock_t start; clock_t end;

    SDL_Rect platform = {200,400,600,220};
    SDL_SetRenderDrawColor(renderer, 47, 79, 79, 255);
    SDL_RenderFillRect(renderer, &platform);
    SDL_RenderPresent(renderer);



    while(!quit){
	    frameStart = sc::high_resolution_clock::now();
        SDL_PollEvent(&events);
        if(events.type == SDL_QUIT) {
            quit = true;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &myRect);
        const Uint8 *state = SDL_GetKeyboardState(NULL);

        xSpeed = 0;

        if(state[SDL_SCANCODE_A]) {
            xSpeed -= 5;;
        }
        if(state[SDL_SCANCODE_D]) {
            xSpeed += 5;
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
            }
        } else {
    		pastPress[KEY_W] = 0;
    		canJump = true;
	    }
        // escape
        if(state[SDL_SCANCODE_ESCAPE]) {
            quit = true;
        }
        if(!state[SDL_SCANCODE_W]) {
            canJump = true;
        }

        // state machine for player jumping
        switch(jump) {
            case BUTTON_PRESS:
    		    canJump = false;
    		    ySpeed = -16;
                end = clock();
                if (jumpframes > 10) {
                    jumpframes = 0;
    			    jump = DECELERATE;
                }
    		    ++jumpframes;
    		    ground = false;
                break;
            case DECELERATE  :
                ySpeed += 2;
                if (ySpeed <= 0){
                    ySpeed = 0;
                    jump = DESCEND;
		        }
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
                if (canJump && ground) {
                    if (canJump) {
                        jump = READY;
                    }
                }
                break;
            case READY      :
                ySpeed = GRAVITY;
                break;
        }
        //std::cout << jump << endl;

        CheckCollision(myRect,platform,&myRect.x,&myRect.y,xSpeed,ySpeed);

        // update location based on button press
        update(&myRect.x, &myRect.y, xSpeed, ySpeed);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &myRect);
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

