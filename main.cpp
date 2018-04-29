#include "block.h"
#include "player.h"
#include "block.cpp"
#include "player.cpp"
#include "portal.h"
#include "portal.cpp"
#include "BlackWall.h"
#include "BlackWall.cpp"
#include "GrayWall.h"
#include "GrayWall.cpp"
#include "utils.h"

// globals
auto frameStart = sc::high_resolution_clock::now();
auto frameEnd = sc::high_resolution_clock::now();

STATE jump = READY;
bool canJump = false;
bool ground = true;

int main(int argc, char** argv) {
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        cout << "Something went wrong! " << SDL_GetError() << endl;
    }
    
    SDL_Window* window = SDL_CreateWindow("SDL_Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if(window == NULL){
        cout << "Something also went wrong here" << endl;
    }
    bool pastPlat = false;
    int pastPress[] = {0,0,0,0};
    int jumpframes = 0;
    bool quit = false;
    SDL_Event event;
    int x = 288;
    int y = 208;
    const int FPS = 60;
    int frameTime;
    
    SDL_Renderer* renderer;
    SDL_Event events;
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    // player
    SDL_Surface * image = SDL_LoadBMP("lols.bmp");
    SDL_Texture * currentimage = SDL_CreateTextureFromSurface(renderer, image);
    
    SDL_Rect playerRect = {600, 100, CHAR_WIDTH, CHAR_HEIGHT};
    //int xSpeed = 0; int ySpeed = 0;
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //SDL_RenderFillRect(renderer, &myRect);
    //SDL_RenderPresent(renderer);
    
    // player texture
    SDL_Rect animationRect;
    int framewidth, frameheight;
    int texturewidth, textureheight;
    SDL_QueryTexture(currentimage,NULL,NULL,&texturewidth,&textureheight);
    framewidth = texturewidth/4 ;
    frameheight = textureheight/4;
    animationRect.x = animationRect.y = 0;
    animationRect.w = framewidth;
    animationRect.h = frameheight;

    Player player(600, 100, CHAR_WIDTH, CHAR_HEIGHT, renderer, playerRect, animationRect, currentimage);
    player.draw();
    
    long int delayTime;
    clock_t start; clock_t end;
    
    // test Block
    SDL_Rect platform = {200,670,400,50};
    BlackWall plat(200, 670, 400, 50, renderer, platform);
    plat.draw();
    vector<Block*> vec;
    vec.push_back(&plat);
    //SDL_SetRenderDrawColor(renderer, 47, 79, 79, 255);
    //SDL_RenderFillRect(renderer, &platform);
    
    SDL_RenderPresent(renderer);
    
    while(!quit){
        frameStart = sc::high_resolution_clock::now();
        SDL_PollEvent(&events);
        if(events.type == SDL_QUIT) {
            quit = true;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        //SDL_RenderFillRect(renderer, &myRect);
        
        SDL_RenderClear(renderer);
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        
        
        player.setXSpeed(0);
        if(state[SDL_SCANCODE_A]) {
            player.changeXSpeed(-5);
        }
        if(state[SDL_SCANCODE_D]) {
            player.changeXSpeed(5);
        }
        // y direction
        if(state[SDL_SCANCODE_W])
        {
            ++pastPress[KEY_W];
            if(pastPress[KEY_W] == 1)
            {
                canJump = true;
            }
            if (jump == READY) {
                start = clock();
                jump = BUTTON_PRESS;
            }
        }
        else {
            pastPress[KEY_W] = 0;
            canJump = true;
        }
        // escape
        if(state[SDL_SCANCODE_ESCAPE]) {
            quit = true;
        }
        // } else if (event.type == SDL_KEYUP) {
        if(!state[SDL_SCANCODE_W]) {
            canJump = true;
        }
        //
        switch(jump) {
            case BUTTON_PRESS:
                //                if (canJump) {
                canJump = false;
                player.setYSpeed(-12);
                end = clock();
                if (jumpframes > 6)
                {
                    jumpframes = 0;
                    jump = DECELERATE;
                }
                ++jumpframes;
                ground = false;
                break;
            case DECELERATE  :
                player.changeYSpeed(3);
                if (player.getYSpeed() >= 0){
                    player.setYSpeed(0);
                    jump = DESCEND;
                }
                break;
            case DESCEND     :
                player.changeYSpeed(5);
                if (player.getYSpeed() == GRAVITY) {
                    jump = FREEFALL;
                    start = clock();
                }
                break;
            case FREEFALL    :
                jumpframes = 0;
                player.setYSpeed(GRAVITY);
                if (canJump && ground) {
                    jump = READY;
                }
                break;
            case READY      :
                jumpframes = 0;
                player.setYSpeed(GRAVITY);
                break;
        }
        
        
        // are there collisions?
        //CheckCollision(myRect,platform,&myRect.x,&myRect.y,xSpeed,ySpeed);
        
        
        // update location based on button press
        //updatex(myRect,platform,&myRect.x, &myRect.y, xSpeed, ySpeed,&jump,&pastPlat);
        //updatey(myRect,platform,&myRect.x, &myRect.y, xSpeed, ySpeed,&jump,&pastPlat);

        player.updateX(vec);
        player.updateY(vec,&ground, jump);

        // update + check collisions

        // draw
        
        ++frameTime;
        if (player.getXSpeed() == 0)
        {
            if (FPS/frameTime == 4)
            {
                animationRect.x +=framewidth;
                if(animationRect.x >= texturewidth)
                    animationRect.x = 0;
                frameTime = 0;
            }
        }
        else if(player.getXSpeed() < 0)
        {
            if (FPS/frameTime == 4){
            animationRect.y = frameheight;
            animationRect.x +=framewidth;
            if(animationRect.x >= texturewidth)
                animationRect.x = 0;
            frameTime = 0;
            }
        }
        else if (player.getXSpeed() > 0)
        {
            if (FPS/frameTime == 4){
                animationRect.y = frameheight*2;
                animationRect.x +=framewidth;
                if(animationRect.x >= texturewidth)
                    animationRect.x = 0;
                frameTime = 0;
            }
        }
        
        //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        //SDL_RenderFillRect(renderer, &myRect);
        //SDL_RenderCopy(renderer,currentimage,&animationRect,&playerRect);
        player.draw();

        // draw some platforms
        plat.draw();
        //SDL_SetRenderDrawColor(renderer, 47, 79, 79, 255);
        //SDL_RenderFillRect(renderer, &platform);

        // switch buffer to display
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
