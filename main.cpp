#include "block.h"
#include "player.h"
#include "portal.h"
#include "EndZoneWall.h"
#include "utils.h"
using namespace std;

// globals
auto frameStart = sc::high_resolution_clock::now();
auto frameEnd = sc::high_resolution_clock::now();

STATE jump = READY;
bool canJump = false;
bool ground = true;

int level = 0;
bool loadLevel = true;
const int NUM_LEVELS = 5;

void level0(SDL_Renderer* renderer, vector<SDL_Rect>& rectVec);
void level1(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p);
void level2(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p);
void level3(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p);
void level4(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p);
void level5(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p);


int main(int argc, char** argv) {
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        cout << "Something went wrong! " << SDL_GetError() << endl;
    }
    
    SDL_Window* window = SDL_CreateWindow("SDL_Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if(window == NULL){
        cout << "Something also went wrong here" << endl;
    }
    int pastPress[] = {0,0,0,0,0,0,0,0};
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
    // player.draw(&animationRect);

    // end zone wall
    SDL_Rect endBlock = {0,0,CHAR_WIDTH/2,CHAR_HEIGHT};
    EndZoneWall endWall(0,0,CHAR_WIDTH/2,CHAR_HEIGHT, renderer, endBlock);

    // portals

    // block vector
    vector<Block> blockVector;
    vector<SDL_Rect> rectVector;

    // call the level function
    // level0(renderer, rectVector);
    // loadLevel = false;
    // player.draw(&animationRect);
    

    long int delayTime;
    clock_t start; clock_t end;
    
    // // test Block
    // SDL_Rect platform = {200,670,400,50};
    // Block block(200, 670, 400, 50, renderer, platform, false);
    // //block.draw();
    // vector<Block> vec;
    // vec.push_back(block);
    // SDL_Rect plat = {600, 620, 300, 100};
    // Block block2(600, 620, 300, 100, renderer, plat, true);
    // vec.push_back(block2);
    // //SDL_SetRenderDrawColor(renderer, 47, 79, 79, 255);
    // //SDL_RenderFillRect(renderer, &platform);
    
    SDL_RenderPresent(renderer);

    while(!quit){
        // level handling
        if (loadLevel == true) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);        
            SDL_RenderClear(renderer);
            blockVector.clear();
            rectVector.clear();
            switch(level) {
                case 0:
                    level0(renderer, rectVector);
                    loadLevel = false;
                    break;
                case 1:
                    level1(renderer, blockVector, endWall, player);
                    loadLevel = false;
                    player.draw(&animationRect);
                    break;
                case 2:
                    level2(renderer, blockVector, endWall, player);
                    loadLevel = false;
                    player.draw(&animationRect);
                    break;
                case 3:
                    level3(renderer, blockVector, endWall, player);
                    loadLevel = false;
                    player.draw(&animationRect);
                    break;
                case 4:
                    level4(renderer, blockVector, endWall, player);
                    loadLevel = false;
                    player.draw(&animationRect);
                    break;
                case 5:
                    level5(renderer, blockVector, endWall, player);
                    loadLevel = false;
                    player.draw(&animationRect);
                default: 
                    level0(renderer, rectVector);
                    loadLevel = false;
                    break;
            }
        }

        frameStart = sc::high_resolution_clock::now();
        SDL_PollEvent(&events);
        if(events.type == SDL_QUIT) {
            quit = true;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);        
        SDL_RenderClear(renderer);
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        
        // use the arrow keys to control the player
        if(state[SDL_SCANCODE_R]) {
          
            loadLevel = true;
        }

        // allows iteration through the levels
        if(state[SDL_SCANCODE_LEFT]) {
            ++pastPress[KEY_LEFT];
            if (pastPress[KEY_LEFT] == 1) {
                level--;
                loadLevel = true;
                if (level < 0)
                    level = 0;
            }
        } else {
            pastPress[KEY_LEFT] = 0;
        }
        if(state[SDL_SCANCODE_RIGHT]) {
            ++pastPress[KEY_RIGHT];
            if (pastPress[KEY_RIGHT] == 1) {
                level++;
                loadLevel = true;
                if (level > NUM_LEVELS)
                    level = NUM_LEVELS;
            }
        } else {
            pastPress[KEY_RIGHT] = 0;
        }

        // use AWD to control the player
        player.setXSpeed(0);
        if(state[SDL_SCANCODE_A]) { // x direction
            player.changeXSpeed(-5);
        }
        if(state[SDL_SCANCODE_D]) { // x direction
            player.changeXSpeed(5);
        }
        if(state[SDL_SCANCODE_W]) { // y direction
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

        // jump state machine
        switch(jump) {
            case BUTTON_PRESS:
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
        if (level != 0) {
            player.updateX(blockVector);
            player.updateY(blockVector, &ground, jump);
        }
        

        // check if player collides with exit
        if (SDL_HasIntersection(player.getRectangle(), endWall.getRectangle())) {
            loadLevel = true;
            level++;
            if (level > NUM_LEVELS)
                // game has finished
                level = NUM_LEVELS;
        }

        // check if player collides with portal
        
        // update animation if necessary
        ++frameTime;
        if (player.getXSpeed() == 0) {
            if (FPS/frameTime == 4) {   
                animationRect.y = 0;
                animationRect.x +=framewidth;
                if(animationRect.x >= texturewidth)
                    animationRect.x = 0;
                frameTime = 0;
            }
        } else if(state[SDL_SCANCODE_A]) {
            if (FPS/frameTime == 4){
                animationRect.y = frameheight;
                animationRect.x +=framewidth;
                if(animationRect.x >= texturewidth)
                    animationRect.x = 0;
                frameTime = 0;
            }
        } else if (state[SDL_SCANCODE_D]) {
            if (FPS/frameTime == 4){
                animationRect.y = frameheight*2;
                animationRect.x +=framewidth;
                if(animationRect.x >= texturewidth)
                    animationRect.x = 0;
                frameTime = 0;
            }
        }


        if (level != 0) {
            // draw the player and its animation
            player.draw(&animationRect);
            // draw the blocks
            vector<Block>::iterator it;
            for (it = blockVector.begin(); it != blockVector.end(); it++) {
                (*it).draw();
            }
            // draw the end zone
            endWall.draw();
            // draw the portals
        } else {
            int count = 0;
            for(auto i : rectVector){
                if (count % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer, 0, 120, 255, 255);
                } else {
                    SDL_SetRenderDrawColor(renderer, 253, 102, 0, 255);
                }
                SDL_RenderFillRect(renderer, &i);
                count++;
            }
        }

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


void level0(SDL_Renderer* renderer, vector<SDL_Rect>& rectVec){
    SDL_Rect level1 = {1045,50,150,60};
    SDL_Rect level2 = {1045,120,150,60};
    SDL_Rect level3 = {1045,190,150,60};
    SDL_Rect level4 = {1045,260,150,60};
    SDL_Rect level5 = {1045,330,150,60};
    SDL_Rect level6 = {1045,400,150,60};
    SDL_Rect level7 = {1045,470,150,60};
    SDL_Rect level8 = {1045,540,150,60};
    SDL_Rect level9 = {1045,610,150,60};

    rectVec.push_back(level1);
    rectVec.push_back(level2);
    rectVec.push_back(level3);
    rectVec.push_back(level4);
    rectVec.push_back(level5);
    rectVec.push_back(level6);
    rectVec.push_back(level7);
    rectVec.push_back(level8);
    rectVec.push_back(level9);

    int count = 0;
    for(auto i : rectVec){
        if (count % 2 == 0) {
            SDL_SetRenderDrawColor(renderer, 0, 120, 255, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 253, 102, 0, 255);
        }
        SDL_RenderFillRect(renderer, &i);
        count++;
    }
}

void level1(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p){
    SDL_Rect wall1 = {0,0,10,720};
    SDL_Rect wall2 = {1270,0,10,720};
    SDL_Rect wall3 = {10,0,1260,10};
    SDL_Rect wall4 = {10,710,1260,10};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,710,1260,10,renderer, wall4, true);

    SDL_Rect wall5 = {400,660,50,50};
    SDL_Rect wall6 = {450,610,50,100};
    Block hellowall(400,660,50,50,renderer, wall5, true);
    Block hellowall2(450,610,50,100,renderer, wall6, true);

    blockVec.push_back(leftwall);
    blockVec.push_back(rightwall);
    blockVec.push_back(topwall);
    blockVec.push_back(bottomwall);
    blockVec.push_back(hellowall);
    blockVec.push_back(hellowall2);

    for(auto i : blockVec){
        i.draw();
    }

    end.setX(1170);
    end.setY(710-CHAR_HEIGHT);
    p.setX(20);
    p.setY(640);

    end.draw();
}

void level2(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p){
    SDL_Rect wall1 = {0,0,10,720};
    SDL_Rect wall2 = {1270,0,10,720};
    SDL_Rect wall3 = {10,0,1260,10};
    SDL_Rect wall4 = {10,710,1260,10};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,710,1260,10,renderer, wall4, true);

    SDL_Rect wall5 = {10,540,100,170};
    SDL_Rect wall6 = {110,590,100,120};
    SDL_Rect wall7 = {210,640,100,70};
    SDL_Rect wall8 = {310,690,200,20};
    SDL_Rect wall9 = {510,310,100,400};
    SDL_Rect wall10 = {710,10,560,300};
    Block stair1(10,540,100,170,renderer, wall5, true);
    Block stair2(110,590,100,120,renderer, wall6, true);
    Block stair3(210,640,100,70,renderer, wall7, true);
    Block floor1(310,690,200,20,renderer, wall8, false);
    Block bigwall(510,310,100,400,renderer, wall9, true);
    Block topright(710,10,560,300,renderer, wall10, false); 

    blockVec.push_back(leftwall);
    blockVec.push_back(rightwall);
    blockVec.push_back(topwall);
    blockVec.push_back(bottomwall);

    blockVec.push_back(stair1);
    blockVec.push_back(stair2);
    blockVec.push_back(stair3);
    blockVec.push_back(floor1);
    blockVec.push_back(bigwall);
    blockVec.push_back(topright);

    for(auto i : blockVec){
        i.draw();
    }

    end.setX(1170);
    end.setY(710-CHAR_HEIGHT);
    p.setX(240);
    p.setY(500);

    end.draw();
}

void level3(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p){
    SDL_Rect wall1 = {0,0,10,720};
    SDL_Rect wall2 = {1270,0,10,720};
    SDL_Rect wall3 = {10,0,1260,10};
    SDL_Rect wall4 = {10,710,1260,10};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,710,1260,10,renderer, wall4, true);

    SDL_Rect wall5 = {10,10,750,200};
    SDL_Rect wall6 = {760,10,20,200};
    SDL_Rect wall7 = {10,660,1000,50};
    SDL_Rect wall8 = {1010,210,260,500};
    Block topleft(10,10,750,200,renderer,wall5,true);
    Block ledge(760,10,20,200,renderer,wall6,false);
    Block floorWall(10,660,1000,50,renderer,wall7,false);
    Block right(1010,210,260,500,renderer,wall8,true);

    blockVec.push_back(leftwall);
    blockVec.push_back(rightwall);
    blockVec.push_back(topwall);
    blockVec.push_back(bottomwall);

    blockVec.push_back(topleft);
    blockVec.push_back(ledge);
    blockVec.push_back(floorWall);
    blockVec.push_back(right);

    for(auto i : blockVec){
        i.draw();
    }

    end.setX(1170);
    end.setY(210-CHAR_HEIGHT);
    p.setX(20);
    p.setY(600);

    end.draw();
}

void level4(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p){
    SDL_Rect wall1 = {0,0,10,720};
    SDL_Rect wall2 = {1270,0,10,720};
    SDL_Rect wall3 = {10,0,1260,10};
    SDL_Rect wall4 = {10,710,1260,10};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,710,1260,10,renderer, wall4, true);

    SDL_Rect wall5 = {10,10,800,20};
    SDL_Rect wall6 = {10,710,1000,200};
    SDL_Rect wall7 = {1010,210,260,500};
    Block topGray(10,10,800,20,renderer,wall5,false);
    Block bottomGray(10,710,1000,200,renderer,wall6,false);
    Block right(1010,210,260,500,renderer,wall7,true);

    blockVec.push_back(leftwall);
    blockVec.push_back(rightwall);
    blockVec.push_back(topwall);
    blockVec.push_back(bottomwall);

    blockVec.push_back(topGray);
    blockVec.push_back(bottomGray);
    blockVec.push_back(right);

    for(auto i : blockVec){
        i.draw();
    }

    end.setX(1170);
    end.setY(210-CHAR_HEIGHT);
    p.setX(20);
    p.setY(600);

    end.draw();
}

void level5(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p){
    SDL_Rect wall1 = {0,0,10,720};
    SDL_Rect wall2 = {1270,0,10,720};
    SDL_Rect wall3 = {10,0,1260,10};
    SDL_Rect wall4 = {10,710,1260,10};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,710,1260,10,renderer, wall4, true);

    SDL_Rect wall5 = {40,100,50,610};
    SDL_Rect wall6 = {1040,100,50,610};
    SDL_Rect wall7 = {40,10,50,5};
    SDL_Rect wall8 = {1270,40,5,50};
    Block hellowall(40,40,50,670,renderer, wall5, true);
    Block hellowall2(1040,40,50,670,renderer, wall6, true);
    Block hellowall3(40,10,50,5,renderer, wall7, false);
    Block hellowall4(1270,40,5,50,renderer, wall8, false);

    blockVec.push_back(leftwall);
    blockVec.push_back(rightwall);
    blockVec.push_back(topwall);
    blockVec.push_back(bottomwall);
    blockVec.push_back(hellowall);
    blockVec.push_back(hellowall2);
    blockVec.push_back(hellowall3);
    blockVec.push_back(hellowall4);

    for(auto i : blockVec){
        i.draw();
    }

    end.setX(1170);
    end.setY(660);
    p.setX(200);
    p.setY(640);

    end.draw();
}