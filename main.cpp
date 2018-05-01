#include "block.h"
#include "player.h"
#include "portal.h"
#include "EndZoneWall.h"
#include "utils.h"

// globals
auto frameStart = sc::high_resolution_clock::now();
auto frameEnd = sc::high_resolution_clock::now();

STATE jump = READY;
bool canJump = false;
bool ground = true;

int level = 0;
bool loadLevel = true;
const int NUM_LEVELS = 9;

void level0(SDL_Renderer* renderer, vector<SDL_Rect>& rectVec);
void level1(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p);
void level2(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p);
void level3(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p);
void level4(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p);
void level5(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p);
void level6(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p);
void level7(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p);
void level8(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p);
void level9(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p);

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
    int frameTime = 0;
    int mouse_x, mouse_y;
    bool hasTeleported;
    SDL_Renderer* renderer;
    SDL_Event events;
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    int telecounter;


    // splash screen
    SDL_Surface * img = SDL_LoadBMP("splash screen.bmp");
    SDL_Texture * splashScreen = SDL_CreateTextureFromSurface(renderer, img);
    
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

    long int delayTime;
    clock_t start; clock_t end;
    
    // test Block
    // SDL_Rect platform = {200,670,400,50};
    // Block block(200, 670, 400, 50, renderer, platform, false);
    // vector<Block> vec;
    // vec.push_back(block);
    // SDL_Rect plat = {600, 420, 300, 300};
    // Block block2(600, 420, 300, 300, renderer, plat, true);
    // vec.push_back(block2);

    SDL_RenderPresent(renderer);

    // SDL_Rect portal1; //LEFT CLICK
    // SDL_Rect portal2; //RIGHT CLICK
    Portal portal1(false,renderer); //Right click, Blue
    Portal portal2(true,renderer); // Left Click,  Orange

    while(!quit){
        frameStart = sc::high_resolution_clock::now();
        //std::cout << "X SPEED = " << player.getXSpeed() << "Y SPEED = " << player.getYSpeed() << std::endl;
        SDL_PollEvent(&events);
        // if red X is clicked or ESC
        if(events.type == SDL_QUIT) {
            quit = true;
        }

        // manage mouse clicks
        switch (events.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (events.button.button == SDL_BUTTON_LEFT) {
                    if (level == 0) {
                        SDL_GetMouseState(&mouse_x,&mouse_y);
                        int count = 1;
                        for(auto i : rectVector){
                            SDL_Rect temp = {mouse_x, mouse_y, 1, 1};
                            if (SDL_HasIntersection(&i, &temp)) {
                                level = count;
                                loadLevel = true;
                                break;
                            }
                            count++;
                        }
                    } else {
                        pastPress[LEFT_MOUSE]++;
                        if (pastPress[LEFT_MOUSE] == 1) {
                            SDL_GetMouseState(&mouse_x,&mouse_y);
                            portal1.PortalHit(blockVector, *player.getRectangle(), mouse_x, mouse_y, portal2);
                            // SDL_Rect draw = {mouse_x-10, mouse_y-10, 20,20};
                            // SDL_SetRenderDrawColor(renderer, 255,128,0,130);
                            // SDL_RenderFillRect(renderer, &draw);
                        }
                    }  
                }
                else if (events.button.button == SDL_BUTTON_RIGHT){
                    pastPress[RIGHT_MOUSE]++;
                    if (pastPress[RIGHT_MOUSE] == 1) {
                        SDL_GetMouseState(&mouse_x,&mouse_y);
                        portal2.PortalHit(blockVector, *player.getRectangle(), mouse_x, mouse_y, portal1);
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

        // level handling
        if (loadLevel == true) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);        
            // SDL_RenderClear(renderer);
            portal1.setActive(false);
            portal2.setActive(false);
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
                    break;
                case 6:
                    level6(renderer, blockVector, endWall, player);
                    loadLevel = false;
                    player.draw(&animationRect);
                    break;
                case 7:
                    level7(renderer, blockVector, endWall, player);
                    loadLevel = false;
                    player.draw(&animationRect);
                    break;
                case 8:
                    level8(renderer, blockVector, endWall, player);
                    loadLevel = false;
                    player.draw(&animationRect);
                    break;
                case 9: 
                    level9(renderer, blockVector, endWall, player);
                    loadLevel = false;
                    player.draw(&animationRect);
                    break;
                default: 
                    level0(renderer, rectVector);
                    loadLevel = false;
                    break;
            }
        } 

        // use the arrow keys to control the player
        // resets the level
        if(state[SDL_SCANCODE_R]) {
            loadLevel = true;
        }

        // left and right arrows allow iteration through the levels
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
                player.setYSpeed(-15);
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
                if (player.getYSpeed() >= 20) {
                    jump = FREEFALL;
                    start = clock();
                }
                break;
            case FREEFALL    :
                jumpframes = 0;
                player.setYSpeed(20);
                if (ground) {
                    jump = READY;
                }
                break;
            case READY      :
                jumpframes = 0;
                player.setYSpeed(GRAVITY[4]);
                break;
        }

        if (level != 0) {
            // move the player to the new position based on current momentum
            // check if the player collides with its environment
            hasTeleported = player.teleport(portal1, portal2, jump);


            player.updateX(blockVector);
            player.updateY(blockVector, &ground, jump);


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
            portal1.draw();
            portal2.draw();

        } else {
            SDL_RenderCopy(renderer, splashScreen, NULL, NULL);
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

        // draw portals

        // SDL_SetRenderDrawColor(renderer, 255,128,0,130);
        // SDL_RenderFillRect(renderer, &portal1);

        // SDL_SetRenderDrawColor(renderer, 0,128,255,130);
        // SDL_RenderFillRect(renderer, &portal2);
        // portal1.draw();
        // portal2.draw();        

        // switch buffer to display the new frame
        // enables a set frame rate
        frameEnd = sc::high_resolution_clock::now();
        delayTime = 16 - sc::duration_cast<sc::milliseconds>(frameEnd-frameStart).count(); 
        if(delayTime > 0) {
            SDL_Delay(delayTime);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}


void level0(SDL_Renderer* renderer, vector<SDL_Rect>& rectVec){
    SDL_Rect level1 = {1045,60,150,60};
    SDL_Rect level2 = {1045,130,150,60};
    SDL_Rect level3 = {1045,200,150,60};
    SDL_Rect level4 = {1045,270,150,60};
    SDL_Rect level5 = {1045,340,150,60};
    SDL_Rect level6 = {1045,410,150,60};
    SDL_Rect level7 = {1045,480,150,60};
    SDL_Rect level8 = {1045,550,150,60};
    SDL_Rect level9 = {1045,620,150,60};

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

void level5(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p){
    SDL_Rect wall1 = {0,0,10,720};
    SDL_Rect wall2 = {1270,0,10,720};
    SDL_Rect wall3 = {10,0,1260,10};
    SDL_Rect wall4 = {10,710,1260,10};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,710,1260,10,renderer, wall4, true);

    SDL_Rect wall5 = {10,10,250,20};
    SDL_Rect wall6 = {10,680,500,30};
    SDL_Rect wall7 = {510,210,760,500};
    SDL_Rect wall8 = {1240,10,30,200};
    Block topGray(10,10,250,20,renderer,wall5,false);
    Block bottomGray(10,680,500,30,renderer,wall6,false);
    Block right(510,210,760,500,renderer,wall7,true);
    Block otherRight(1240,10,30,200,renderer,wall8,false);
    blockVec.push_back(leftwall);
    blockVec.push_back(rightwall);
    blockVec.push_back(topwall);
    blockVec.push_back(bottomwall);

    blockVec.push_back(topGray);
    blockVec.push_back(bottomGray);
    blockVec.push_back(right);
    blockVec.push_back(otherRight);

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

    SDL_Rect wall5 = {10,200,100,510};
    SDL_Rect wall6 = {1000,200,100,510};
    SDL_Rect wall7 = {10,10,100,25};
    SDL_Rect wall8 = {1240,100,30,150};
    SDL_Rect wall9 = {110,680,890,30};
    Block hellowall(10,200,100,510,renderer, wall5, true);
    Block hellowall2(1000,200,100,510,renderer, wall6, true);
    Block hellowall3(10,100,100,25,renderer, wall7, false);
    Block hellowall4(1240,100,30,150,renderer, wall8, false);
    Block floor(110,680,890,30,renderer,wall9,false);

    blockVec.push_back(leftwall);
    blockVec.push_back(rightwall);
    blockVec.push_back(topwall);
    blockVec.push_back(bottomwall);
    blockVec.push_back(hellowall);
    blockVec.push_back(hellowall2);
    blockVec.push_back(hellowall3);
    blockVec.push_back(hellowall4);
    blockVec.push_back(floor);

    for(auto i : blockVec){
        i.draw();
    }

    end.setX(1170);
    end.setY(646);
    p.setX(200);
    p.setY(570);

    end.draw();
}

void level6(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p) {
    SDL_Rect wall1 = {0,0,10,720};
    SDL_Rect wall2 = {1270,0,10,720};
    SDL_Rect wall3 = {10,0,1260,10};
    SDL_Rect wall4 = {10,710,1260,10};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,710,1260,10,renderer, wall4, true);

    SDL_Rect topGray = {10,10,440,30};
    SDL_Rect topGray2 = {470,10,400,30};
    SDL_Rect leftGray = {10,40,30,200};
    SDL_Rect leftPlat = {10,210,200,100};
    SDL_Rect leftPlat2 = {240,210,430,100};
    SDL_Rect leftPlat3 = {700,210,430,100};
    SDL_Rect grayFloor = {10,680,1260,30};
    SDL_Rect leftBlockTop = {440,10,30,160};
    SDL_Rect leftBlockBottom = {440,200,30,10};
    SDL_Rect rightBlockTop = {870,10,30,160};
    SDL_Rect rightBlockBottom = {870,200,30,10};
    SDL_Rect rightGray = {1240,10,30,670};
    SDL_Rect middlePlat1 = {440,310,30,100};
    SDL_Rect middlePlat2 = {440,410,450,100};

    Block topGrayBlock(10,10,550,30,renderer, topGray, false);
    Block topGrayBlock2(470,10,400,30,renderer, topGray2, false);
    Block leftGrayBlock(10,40,30,250,renderer, leftGray, false);
    Block leftPlatBlock(10,260,200,100,renderer, leftPlat, true);
    Block leftPlatBlock2(240,260,430,100,renderer, leftPlat2, true);
    Block leftPlatBlock3(240,260,430,100,renderer, leftPlat3, true);
    Block grayFloorBlock(10,680,1260,30,renderer, grayFloor, false);
    Block leftBlockTopBlock(440,10,30,140,renderer, leftBlockTop, true);
    Block leftBlockBottomBlock(440,180,30,30,renderer, leftBlockBottom, true);
    Block rightBlockTopBlock(870,10,30,140,renderer, rightBlockTop, true);
    Block rightBlockBottomBlock(870,180,30,30,renderer, rightBlockBottom, true);
    Block rightGrayBlock(1240,10,30,700,renderer, rightGray, false);
    Block middlePlatBlock1(440,310,30,100,renderer, middlePlat1, false);
    Block middlePlatBlock2(440,410,450,100,renderer, middlePlat2, true);

    blockVec.push_back(leftwall);
    blockVec.push_back(rightwall);
    blockVec.push_back(topwall);
    blockVec.push_back(bottomwall);
    blockVec.push_back(topGrayBlock);
    blockVec.push_back(topGrayBlock2);
    blockVec.push_back(leftGrayBlock);
    blockVec.push_back(leftPlatBlock);
    blockVec.push_back(leftPlatBlock2);
    blockVec.push_back(leftPlatBlock3);
    blockVec.push_back(grayFloorBlock);
    blockVec.push_back(leftBlockTopBlock);
    blockVec.push_back(leftBlockBottomBlock);
    blockVec.push_back(rightBlockTopBlock);
    blockVec.push_back(rightBlockBottomBlock);
    blockVec.push_back(rightGrayBlock);
    blockVec.push_back(middlePlatBlock1);
    blockVec.push_back(middlePlatBlock2);
    for(auto i : blockVec){
        i.draw();
    }

    end.setX(600);
    end.setY(146);
    p.setX(50);
    p.setY(50);

    end.draw();
}

void level7(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p) {
    SDL_Rect wall1 = {0,0,10,720};
    SDL_Rect wall2 = {1270,0,10,720};
    SDL_Rect wall3 = {10,0,1260,10};
    SDL_Rect wall4 = {10,710,1260,10};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,710,1260,10,renderer, wall4, true);

    SDL_Rect wall5 = {0,200,400,510};  // built
    SDL_Rect wall6 = {950,520,320,190}; // built
    SDL_Rect wall7 = {520,10,300,600};  // built
    SDL_Rect wall8 = {400,705,550,5};   // built
    SDL_Rect wall9 = {280,10,100,5};    // built
    Block b_wall5(0,200,400,510,renderer, wall5, true);
    Block b_wall6(950,520,320,190,renderer, wall6, true);
    Block b_wall7(520,10,300,600,renderer, wall7, true);
    Block b_wall8(400,705,550,5,renderer, wall8, false);
    Block b_wall9(280,10,100,5,renderer, wall9, false);

    blockVec.push_back(leftwall);
    blockVec.push_back(rightwall);
    blockVec.push_back(topwall);
    blockVec.push_back(bottomwall);
    blockVec.push_back(b_wall5);
    blockVec.push_back(b_wall6);
    blockVec.push_back(b_wall7);
    blockVec.push_back(b_wall8);
    blockVec.push_back(b_wall9);

    for(auto i : blockVec){
        i.draw();
    }

    end.setX(1170);
    end.setY(456);
    p.setX(25);
    p.setY(125);

    end.draw();
}

void level8(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p){
    SDL_Rect wall1 = {0,0,10,720};
    SDL_Rect wall2 = {1270,0,10,720};
    SDL_Rect wall3 = {10,0,1260,10};
    SDL_Rect wall4 = {10,710,1260,10};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,710,1260,10,renderer, wall4, true);

    SDL_Rect wall6 = {10,690,1260,20};
    SDL_Rect wall7 = {200,600,30,120};
    SDL_Rect wall8 = {350,550,30,75};
    SDL_Rect wall9 = {500,500,30,75};
    SDL_Rect walla = {650,450,30,75};
    SDL_Rect wallb = {800,400,30,75};
    SDL_Rect wallc = {950,350,30,360};

    Block bwall6(10,690,1260,20,renderer, wall7, true);
    Block bwall7(200,600,30,120,renderer, wall7, true);
    Block bwall8(350,550,30,75,renderer, wall8, true);
    Block bwall9(500,500,30,75,renderer, wall9, true);
    Block bwalla(650,450,30,75,renderer, walla, true);
    Block bwallb(800,400,30,75,renderer, wallb, true);
    Block bwallc(950,350,30,360,renderer, wallc, true);
    
    blockVec.push_back(leftwall);
    blockVec.push_back(rightwall);
    blockVec.push_back(topwall);
    blockVec.push_back(bottomwall);
 
    blockVec.push_back(bwall6);
    blockVec.push_back(bwall7);
    blockVec.push_back(bwall8);
    blockVec.push_back(bwall9);
    blockVec.push_back(bwalla);
    blockVec.push_back(bwallb);
    blockVec.push_back(bwallc);
    for(auto i : blockVec){
        i.draw();
    }

    end.setX(1170);
    end.setY(650);
    p.setX(75);
    p.setY(640);

    end.draw();
}

void level9(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p){
    SDL_Rect wall1 = {0,0,10,720};
    SDL_Rect wall2 = {1270,0,10,720};
    SDL_Rect wall3 = {10,0,1260,10};
    SDL_Rect wall4 = {10,710,1260,10};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,710,1260,10,renderer, wall4, true);

    SDL_Rect wall5 = {150,0,20,300};    //done
    SDL_Rect wall6 = {150,500,20,220};   // done
    SDL_Rect wall7 = {170,640,10,80};    // done
    SDL_Rect wall8 = {400,0,20,600};     // done
    SDL_Rect wall9 = {390,200,10,150};   // done
    SDL_Rect wallc = {420,200,10,150};   // done
    SDL_Rect walla = {700,220,50,500};   // done
    SDL_Rect wallb = {1000,150,20,570};
    SDL_Rect walld = {1050,10,200,10};
    Block bwall5(150,660,30,50,renderer, wall5, true);
    Block bwall6(150,500,20,2200,renderer, wall6, true);
    Block bwall7(170,640,10,80,renderer, wall7, false);
    Block bwall8(400,0,20,600,renderer, wall8, true);
    Block bwall9(390,200,10,150,renderer, wall9, false);
    Block bwallc(420,200,10,150,renderer, wallc, false);
    Block bwalla(700,220,50,500,renderer, walla, true);
    Block bwallb(1000,150,20,570,renderer, wallb, true);
    Block bwalld(1050,10,200,10,renderer, walld, true);

    blockVec.push_back(leftwall);
    blockVec.push_back(rightwall);
    blockVec.push_back(topwall);
    blockVec.push_back(bottomwall);
    blockVec.push_back(bwall5);
    blockVec.push_back(bwall6);
    blockVec.push_back(bwall7);
    blockVec.push_back(bwall8);
    blockVec.push_back(bwall9);
    blockVec.push_back(bwalla);
    blockVec.push_back(bwallb);
    blockVec.push_back(bwallc);
    blockVec.push_back(bwalld);

    for(auto i : blockVec){
        i.draw();
    }

    end.setX(1170);
    end.setY(650);
    p.setX(75);
    p.setY(640);

    end.draw();
}
