#include "block.h"
#include "player.h"
#include "block.cpp"
#include "player.cpp"
#include "portal.h"
#include "portal.cpp"
#include "utils.h"
#include "math.h"
using namespace std;



// globals
auto frameStart = sc::high_resolution_clock::now();
auto frameEnd = sc::high_resolution_clock::now();

STATE jump = READY;
bool canJump = false;
bool ground = true;



// void Portalhit(vector<Block>& vec, SDL_Rect &player, int prlx, int prly, SDL_Rect &portal){
//     double x = prlx - (player.x + CHAR_WIDTH/2);
//     double y = prly - (player.y + CHAR_HEIGHT/2);
//     double length = sqrt( x*x + y*y );

//     double addx = x / length;
//     double addy = y / length;

//     x = (player.x + CHAR_WIDTH/2);
//     y = (player.y + CHAR_HEIGHT/2);


//     while(x>0 && x<WINDOW_WIDTH && y>0 && y<WINDOW_HEIGHT)
//     {
//         //cout << "what" << endl;
//       x += addx;
//       y += addy;
//     }



//     int playerheadx = player.x + CHAR_WIDTH/2;
//     int playerheady = player.y + CHAR_HEIGHT/2;

//     int pheadx = playerheadx;
//     int pheady = playerheady;

//     int minx;
//     int miny;
//     SDL_Rect* collisionRect;

//     double mindist = 9999;
//     double distance;

//     bool collide = false;

//     int x2 = (int)x;
//     int y2 = (int)y;

//     SDL_bool hit;

//     vector<Block>::iterator it;
//     for (it = vec.begin(); it != vec.end(); it++) {
//         SDL_Rect* rect2 = (*it).getRectangle();
//         hit = SDL_IntersectRectAndLine(rect2, &playerheadx , &playerheady,&x2,&y2);
//         if (hit){
//             collide = true;
//             distance = sqrt(pow((playerheadx - pheadx), 2) +  pow((playerheady - pheady), 2));
//             if (distance < mindist) {
//                 collisionRect = rect2;
//                 minx = playerheadx;
//                 miny = playerheady;
//                 mindist = distance;
//                 cout << "miny:" << miny << endl;
//             }
//             distance = sqrt(pow((x2 - pheadx), 2) +  pow((y2 - pheady), 2));
//             if (distance < mindist) {
//                 collisionRect = rect2;
//                 minx = x2;
//                 miny = y2;
//                 mindist = distance;
//                 cout << "hit the wierd one" << endl;
//             }
//             x2 = (int)x;
//             y2 = (int)y;
//             playerheadx = pheadx;
//             playerheady = pheady;
//         }
//     }

//     bool valid = false;

//     if(collide) {
//         if (minx > collisionRect->x && minx < collisionRect->x + collisionRect->w && miny == collisionRect->y)                      // top
//         {
//             cout << "top" << endl;
//             if (minx - 40 >= collisionRect->x && minx + 40 <= collisionRect->x + collisionRect->w){
//                 portal.x = minx - 40;
//                 portal.w = 80;
//                 portal.y = miny - 5;
//                 portal.h = 10;
//                 valid = true;
//             }
//         }

//         if (minx > collisionRect->x && minx < collisionRect->x + collisionRect->w && miny == collisionRect->y + collisionRect->h)    // bottom
//         {
//                         cout << "bot" << endl;
//             if (minx - 40 >= collisionRect->x && minx + 40 <= collisionRect->x + collisionRect->w){
//                 portal.x = minx - 40;
//                 portal.w = 80;
//                 portal.y = miny - 5;
//                 portal.h = 10;
//                 valid = true;
//             }
//         }

//         if (miny > collisionRect->y && miny < collisionRect->y + collisionRect->h && minx == collisionRect->x)                      // left
//         {
//                         cout << "lef" << endl;
//             if ((miny - 40) >= collisionRect->y && miny + 40 <= collisionRect->y + collisionRect->h){
//                 portal.x = minx - 5;
//                 portal.w = 10;
//                 portal.y = miny - 40;
//                 portal.h = 80;
//                 valid = true;                
//             }
//         }

//         if (miny > collisionRect->y && miny < collisionRect->y + collisionRect->h && minx == collisionRect->x + collisionRect->w)                      // left
//         {
//                         cout << "right" << endl;
//             if (miny - 40 >= collisionRect->y && miny + 40 <= collisionRect->y + collisionRect->h){
//                 portal.x = minx - 5;
//                 portal.w = 10;
//                 portal.y = miny - 40;
//                 portal.h = 80;
//                 valid = true;                
//             }
//         }
//     }


// }

    // if(valid){
    //     vector<Block>::iterator it;
    // for (it = vec.begin(); it != vec.end(); it++) {
    //     SDL_Rect* rect3 = (*it).getRectangle();
    //     if (collisionRect != rect3)
    //     {
    //         if(SDL_HasIntersection(portal,rect3)){

    //         }
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
    int pastPress[] = {0,0,0,0,0,0};
    int jumpframes = 0;
    bool quit = false;
    SDL_Event event;
    int x = 288;
    int y = 208;
    const int FPS = 60;
    int frameTime;
        int mouse_x, mouse_y;
    
    SDL_Renderer* renderer;
    SDL_Event events;
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    // player
    SDL_Surface * image = SDL_LoadBMP("lols.bmp");
    SDL_Texture * currentimage = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect playerRect = {600, 100, CHAR_WIDTH, CHAR_HEIGHT};
    
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

    Player player(600, 100, CHAR_WIDTH, CHAR_HEIGHT, renderer, playerRect, currentimage);
    player.draw(&animationRect);
    
    long int delayTime;
    clock_t start; clock_t end;
    
    // test Block
    SDL_Rect platform = {200,670,400,50};
    Block block(200, 670, 400, 50, renderer, platform, false);
    vector<Block> vec;
    vec.push_back(block);
    SDL_Rect plat = {600, 420, 300, 300};
    Block block2(600, 420, 300, 300, renderer, plat, true);
    vec.push_back(block2);

    
    SDL_RenderPresent(renderer);



    // SDL_Rect portal1; //LEFT CLICK
    // SDL_Rect portal2; //RIGHT CLICK
    Portal portal1(false,renderer);
    Portal portal2(true,renderer);

    
    while(!quit){
        frameStart = sc::high_resolution_clock::now();
        SDL_PollEvent(&events);
        if(events.type == SDL_QUIT) {
            quit = true;
        }
        switch (events.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (events.button.button == SDL_BUTTON_LEFT) {
                    pastPress[LEFT_MOUSE]++;
                    if (pastPress[LEFT_MOUSE] == 1) {
                        std::cout << "LEFT BUTTON PRESSED" << std::endl;
                        SDL_GetMouseState(&mouse_x,&mouse_y);
                        portal1.PortalHit(vec, *player.getRectangle(), mouse_x, mouse_y, portal2);
                        // SDL_Rect draw = {mouse_x-10, mouse_y-10, 20,20};
                        // SDL_SetRenderDrawColor(renderer, 255,128,0,130);
                        // SDL_RenderFillRect(renderer, &draw);
                    }
                }
                else if (events.button.button == SDL_BUTTON_RIGHT){
                    pastPress[RIGHT_MOUSE]++;
                    if (pastPress[RIGHT_MOUSE] == 1) {
                        std::cout << "RIGHT BUTTON PRESSED" << std::endl;
                        SDL_GetMouseState(&mouse_x,&mouse_y);
                        portal2.PortalHit(vec, *player.getRectangle(), mouse_x, mouse_y, portal1);
                        // SDL_Rect draw = {mouse_x-10, mouse_y-10, 20,20};
                        // SDL_SetRenderDrawColor(renderer, 0,128,255,130);
                        // SDL_RenderFillRect(renderer, &draw);
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if(events.button.button == SDL_BUTTON_LEFT) {
                    pastPress[LEFT_MOUSE] = 0;
                } else if (events.button.button == SDL_BUTTON_RIGHT) {
                    pastPress[RIGHT_MOUSE] = 0;
                }
                break;
            default:
                break;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);        
        SDL_RenderClear(renderer);
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        
        // use the arrow keys to control the player
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
        
        // move the player to the new position based on current momentum
        // check if the player collides with its environment
        player.updateX(vec);
        player.updateY(vec, &ground, jump);
        
        // update animation if necessary
        ++frameTime;
        if (player.getXSpeed() == 0)
        {
            if (FPS/frameTime == 4)
            {   
                animationRect.y = 0;
                animationRect.x +=framewidth;
                if(animationRect.x >= texturewidth)
                    animationRect.x = 0;
                frameTime = 0;
            }
        }
        else if(state[SDL_SCANCODE_A])
        {
            if (FPS/frameTime == 4){
            animationRect.y = frameheight;
            animationRect.x +=framewidth;
            if(animationRect.x >= texturewidth)
                animationRect.x = 0;
            frameTime = 0;
            }
        }
        else if (state[SDL_SCANCODE_D])
        {
            if (FPS/frameTime == 4){
                animationRect.y = frameheight*2;
                animationRect.x +=framewidth;
                if(animationRect.x >= texturewidth)
                    animationRect.x = 0;
                frameTime = 0;
            }
        }

        // draw the player and its animation
        player.draw(&animationRect);

        // draw some platforms
        vector<Block>::iterator it;
        for (it = vec.begin(); it != vec.end(); it++) {
            (*it).draw();
        }

        // switch buffer to display

        // draw portals

        // SDL_SetRenderDrawColor(renderer, 255,128,0,130);
        // SDL_RenderFillRect(renderer, &portal1);

        // SDL_SetRenderDrawColor(renderer, 0,128,255,130);
        // SDL_RenderFillRect(renderer, &portal2);
        portal1.draw();
        portal2.draw();        

        SDL_RenderPresent(renderer);
        
        frameEnd = sc::high_resolution_clock::now();
        delayTime = 16 - sc::duration_cast<sc::milliseconds>(frameEnd-frameStart).count(); 
        if(delayTime > 0) {
            SDL_Delay(delayTime);
        }
    }
    // vector<Block*>::iterator it;
    // for (it = vec.begin(); it < vec.end(); it++) {
    //     delete *it;
    // }

    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;

}
