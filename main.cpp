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
    SDL_Surface * img = SDL_LoadBMP("splash_screen.bmp");
    SDL_Texture * splashScreen = SDL_CreateTextureFromSurface(renderer, img);
    
    // player
    SDL_Surface * image = SDL_LoadBMP("sprite.bmp");
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
        //SDL_PollEvent(&events);
        // if red X is clicked or ESC

        // manage mouse clicks
	    while(SDL_PollEvent(&events)) {
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
                    } else if (events.button.button == SDL_BUTTON_RIGHT){
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
                if (ground && canJump) {
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
    SDL_Rect wall4 = {10,700,1260,20};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,700,1260,20,renderer, wall4, true);

    SDL_Rect wall5 = {400,650,50,50};
    SDL_Rect wall6 = {450,600,50,100};
    Block hellowall(400,650,50,50,renderer, wall5, true);
    Block hellowall2(450,600,50,100,renderer, wall6, true);

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
    end.setY(700-CHAR_HEIGHT);
    p.setX(20);
    p.setY(640);

    end.draw();
}

void level2(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p){
    SDL_Rect wall1 = {0,0,10,720};
    SDL_Rect wall2 = {1270,0,10,720};
    SDL_Rect wall3 = {10,0,1260,10};
    SDL_Rect wall4 = {10,700,1260,20};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,700,1260,20,renderer, wall4, true);

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
    end.setY(700-CHAR_HEIGHT);
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

void level7(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p){
    SDL_Rect wall1 = {0,0,10,720};
    SDL_Rect wall2 = {1270,0,10,720};
    SDL_Rect wall3 = {10,0,1260,10};
    SDL_Rect wall4 = {10,710,1260,10};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,710,1260,10,renderer, wall4, true);

    SDL_Rect floor = {10,680,1260,30};
    
    SDL_Rect bot1 = {150,620,30,100};
    SDL_Rect bot2 = {250,580,30,40};
    SDL_Rect bot3 = {380,580,30,40};
    SDL_Rect bot4 = {410,550,30,70};
    SDL_Rect bot5 = {540,550,120,40};
    SDL_Rect bot6 = {740,580,120,40};
    SDL_Rect bot7 = {940,550,30,70};
    SDL_Rect bot8 = {1050,550,30,40};
    SDL_Rect bot9 = {1080,520,30,70};
    SDL_Rect bot10 = {1110,490,30,100};
    SDL_Rect bot11 = {1140,460,60,130};

    SDL_Rect mid1 = {1020,400,60,30};
    SDL_Rect mid2 = {960,430,90,30};
    SDL_Rect mid3 = {830,430,30,30};
    SDL_Rect mid4 = {700,430,30,30};
    SDL_Rect mid5 = {600,410,30,50};
    SDL_Rect mid6 = {470,410,30,50};
    SDL_Rect mid7 = {370,430,100,30};
    SDL_Rect mid8 = {300,410,30,50};
    SDL_Rect mid9 = {270,380,30,30};
    SDL_Rect mid10 = {240,350,30,30};
    SDL_Rect mid11 = {150,320,90,30};

    SDL_Rect top1 = {300,260,250,30};
    SDL_Rect top2 = {650,260,250,30};
    SDL_Rect top3 = {1000,260,270,30};

    Block floorB(10,680,1260,30,renderer,mid1,true);

    Block bot1B(150,620,30,100,renderer,bot1,true);
    Block bot2B(250,580,30,40,renderer,bot2,true);
    Block bot3B(380,580,30,40,renderer,bot3,true);
    Block bot4B(410,550,30,70,renderer,bot4,true);
    Block bot5B(540,550,120,40,renderer,bot5,true);
    Block bot6B(740,580,120,40,renderer,bot6,true);
    Block bot7B(940,550,30,70,renderer,bot7,true);
    Block bot8B(1050,550,30,40,renderer,bot8,true);
    Block bot9B(1080,520,30,70,renderer,bot9,true);
    Block bot10B(1110,490,30,100,renderer,bot10,true);
    Block bot11B(1140,460,60,130,renderer,bot11,true);

    Block mid1B(1020,400,60,30,renderer,mid1,true);
    Block mid2B(960,430,90,30,renderer,mid2,true);
    Block mid3B(830,430,30,30,renderer,mid3,true);
    Block mid4B(700,430,30,30,renderer,mid4,true);
    Block mid5B(600,410,30,50,renderer,mid5,true);
    Block mid6B(470,410,30,50,renderer,mid6,true);
    Block mid7B(370,430,100,30,renderer,mid7,true);
    Block mid8B(300,410,30,50,renderer,mid8,true);
    Block mid9B(270,380,30,30,renderer,mid9,true);
    Block mid10B(240,350,30,30,renderer,mid10,true);
    Block mid11B(150,320,90,30,renderer,mid11,true);

    Block top1B(300,260,250,30,renderer,top1,true);
    Block top2B(650,260,250,30,renderer,top2,true);
    Block top3B(1000,260,270,30,renderer,top3,true);

    blockVec.push_back(leftwall);
    blockVec.push_back(rightwall);
    blockVec.push_back(topwall);
    blockVec.push_back(bottomwall);

    blockVec.push_back(floorB);

    blockVec.push_back(bot1B);
    blockVec.push_back(bot2B);
    blockVec.push_back(bot3B);
    blockVec.push_back(bot4B);
    blockVec.push_back(bot5B);
    blockVec.push_back(bot6B);
    blockVec.push_back(bot7B);
    blockVec.push_back(bot8B);
    blockVec.push_back(bot9B);
    blockVec.push_back(bot10B);
    blockVec.push_back(bot11B);

    blockVec.push_back(mid1B);
    blockVec.push_back(mid2B);
    blockVec.push_back(mid3B);
    blockVec.push_back(mid4B);
    blockVec.push_back(mid5B);
    blockVec.push_back(mid6B);
    blockVec.push_back(mid7B);
    blockVec.push_back(mid8B);
    blockVec.push_back(mid9B);
    blockVec.push_back(mid10B);
    blockVec.push_back(mid11B);

    blockVec.push_back(top1B);
    blockVec.push_back(top2B);
    blockVec.push_back(top3B);

    for(auto i : blockVec){
        i.draw();
    }

    end.setX(1170);
    end.setY(196);
    p.setX(75);
    p.setY(600);

    end.draw();
}

void level8(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p){
    SDL_Rect wall1 = {0,0,10,720};
    SDL_Rect wall2 = {1270,0,10,720};
    SDL_Rect wall3 = {10,0,1260,10};
    SDL_Rect wall4 = {10,700,1260,20};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,700,1260,20,renderer, wall4, true);

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
    end.setY(700-CHAR_HEIGHT);
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
    SDL_Rect grayTop1 = {10,10,140,30};
    SDL_Rect grayTop2 = {290,10,140,30};
    SDL_Rect grayTop3 = {570,10,140,30};
    SDL_Rect grayTop4 = {850,10,420,30};

    SDL_Rect grayBot1 = {10,680,140,30};
    SDL_Rect grayBot2 = {290,680,140,30};
    SDL_Rect grayBot3 = {570,680,140,30};
    SDL_Rect grayBot4 = {850,680,140,30};
    //SDL_Rect grayBot5 = {1130,680,140,30};

    SDL_Rect topWall1 = {150,10,140,350};
    SDL_Rect botWall1 = {150,460,140,250};
    SDL_Rect topWall2 = {430,10,140,200};
    SDL_Rect botWall2 = {430,310,140,400};
    SDL_Rect topWall3 = {710,10,140,400};
    SDL_Rect botWall3 = {710,510,140,200};
    SDL_Rect botWall4 = {990,150,140,560};

    Block g1(10,10,140,30,renderer, grayTop1, false);
    Block g2(290,10,140,30,renderer, grayTop2, false);
    Block g3(570,10,140,30,renderer, grayTop3, false);
    Block g4(850,10,420,30,renderer, grayTop4, false);
    Block g5(10,680,140,30,renderer, grayBot1, false);
    Block g6(290,680,140,30,renderer, grayBot2, false);
    Block g7(570,680,140,30,renderer, grayBot3, false);
    Block g8(850,680,140,30,renderer, grayBot4, false);
    //Block g9(1130,680,140,30,renderer, grayBot5, false);

    Block b1(150,10,140,350,renderer, topWall1, true);
    Block b2(150,460,140,250,renderer, botWall1, true);
    Block b3(430,10,140,200,renderer, topWall2, true);
    Block b4(430,310,140,400,renderer, botWall2, true);
    Block b5(710,10,140,400,renderer, topWall3, true);
    Block b6(710,510,140,200,renderer, botWall3, true);
    Block b7(990,150,140,560,renderer, botWall4, true);

    blockVec.push_back(leftwall);
    blockVec.push_back(rightwall);
    blockVec.push_back(topwall);
    blockVec.push_back(bottomwall);
    blockVec.push_back(g1);
    blockVec.push_back(g2);
    blockVec.push_back(g3);
    blockVec.push_back(g4);
    blockVec.push_back(g5);
    blockVec.push_back(g6);
    blockVec.push_back(g7);
    blockVec.push_back(g8);
    //blockVec.push_back(g9);
    blockVec.push_back(b1);
    blockVec.push_back(b2);
    blockVec.push_back(b3);
    blockVec.push_back(b4);
    blockVec.push_back(b5);
    blockVec.push_back(b6);
    blockVec.push_back(b7);

    for(auto i : blockVec){
        i.draw();
    }

    end.setX(1170);
    end.setY(646);
    p.setX(75);
    p.setY(640);

    end.draw();
}
