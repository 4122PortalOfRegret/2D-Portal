#include "player.h"
#include "block.h"
using namespace std;

Player::Player() {
    setColorR(216);
    setColorG(191);
    setColorB(216);
    setColorA(255);
}

Player::Player(int x, int y, int w, int h, SDL_Renderer* r, SDL_Rect& rect, SDL_Texture* i) {
    setXSpeed(0);
    setYSpeed(0);
    renderer = r;
    rectangle = rect;
    //animation = a;
    image = i;
    setX(x);
    setY(y);
    setHeight(h);
    setWidth(w);
    setColorR(216);
    setColorG(191);
    setColorB(216);
    setColorA(255);
}

void Player::setHeight(int h) {
    height = h;
    rectangle.h = h;
}

void Player::setWidth(int w) {
    width = w;
    rectangle.w = w;
}
int Player::getX() {
    return xLoc;
}

int Player::getY() {
    return yLoc;
}

int Player::getNewX() {
    return newXLoc;
}

int Player::getNewY() {
    return newYLoc;
}

void Player::setX(int x) {
    xLoc = x;
    rectangle.x = x;
}

void Player::setY(int y) {
    yLoc = y;
    rectangle.y = y;
}

int Player::getHeight() {
    return height;
}

int Player::getWidth() {
    return width;
}

SDL_Rect* Player::getRectangle() {
    return &rectangle;
}

int Player::getXSpeed() {
    return xSpeed;
}

int Player::getYSpeed() {
    return ySpeed;
}

void Player::changeXSpeed(int x) {
    xSpeed += x;
}

void Player::changeYSpeed(int y) {
    ySpeed += y;
}

void Player::setXSpeed(int x) {
    xSpeed = x;
}

void Player::setYSpeed(int y) {
    ySpeed = y;
}

void Player::setColorR(Uint8 color) {
    red = color;
}

void Player::setColorG(Uint8 color) {
    green = color;
}

void Player::setColorB(Uint8 color) {
    blue = color;
}

void Player::setColorA(Uint8 color) {
    alpha = color;
}

Uint8 Player::getColorR() {
    return red;
}

Uint8 Player::getColorG() {
    return green;
}

Uint8 Player::getColorB() {
    return blue;
}

Uint8 Player::getColorA() {
    return alpha;
}

// move the player to a new location based on speeds
// void Player::update(vector<Block*>& vec, bool* ground, STATE& jump) {
//     // if (xSpeed == 0 && ySpeed == 0)
//     //     return;
//     // newXLoc = xLoc + xSpeed;

//     // if (newXLoc < 0)
//     //     newXLoc = 0;
//     // if (newXLoc > WINDOW_WIDTH - width)
//     //     newXLoc = WINDOW_WIDTH - width;
//     // newYLoc = yLoc + ySpeed;
//     // if (newYLoc < 0)
//     //     newYLoc = 0;
//     // if (newYLoc > WINDOW_HEIGHT - height)
//     //     newYLoc = WINDOW_HEIGHT - height;
//     for (unsigned int i = 0; i < vec.size(); ++i) {
//         updateX(vec[i]->getRectangle());
//         updateY(vec[i]->getRectangle(), ground, jump);
//     }
// }

void Player::updateX(vector<Block>& vec) {
    if (xSpeed == 0)
        return;
    rectangle.x = rectangle.x + xSpeed;
    
    if (rectangle.x < 0)
        rectangle.x = 0;
    if (rectangle.x > WINDOW_WIDTH - CHAR_WIDTH)
        rectangle.x = WINDOW_WIDTH - CHAR_WIDTH;
    
    // int left1 = rectangle.x;                    // playerx
    // int right1 = rectangle.x + rectangle.w;         // playerx+width
    // int top1 = rectangle.y;                     // playerY
    // int bottom1 = rectangle.y + rectangle.h;        // playerY+height

    int oldleft1 = rectangle.x - xSpeed;
    int oldright1 = rectangle.x + rectangle.w - xSpeed;
    
    vector<Block>::iterator it;
    for (it = vec.begin(); it != vec.end(); it++) {
    //for (unsigned int i = 0; i < vec.size(); i++) {             //++i or i++ ??
        //SDL_Rect* rect2 = vec[i]->getRectangle();
        SDL_Rect* rect2 = (*it).getRectangle();

        // Find edges of rect2
        // int left2 = rect2->x;                    // blockX
        // int right2 = rect2->x + rect2->w;         // blockX+width
        // int top2 = rect2->y;                     // blockY
        // int bottom2 = rect2->y + rect2->h;        // blocky+height
        
        if ( rectangle.x > rect2->x + rect2->w || rectangle.x + rectangle.w < rect2->x  || rectangle.y > rect2->y + rect2->h || rectangle.y + rectangle.h < rect2->y)
            continue;
        
        if (oldleft1 < rect2->x && oldright1 < rect2->x && (((rectangle.y < rect2->y) || (rectangle.y + rectangle.h < rect2->y))  || ((rect2->y < rect2->y + rect2->h) || rectangle.y + rectangle.h < rect2->y + rect2->h)))        // left
            rectangle.x = rect2->x - rectangle.w - 1;
        
        if (oldleft1 > rect2->x + rect2->w && oldright1 > rect2->x + rect2->w && (((rect2->y < rect2->y) || (rectangle.y + rectangle.h < rect2->y))  || ((rect2->y < rect2->y + rect2->h) || (rectangle.y + rectangle.h < rect2->y + rect2->h))))  // right
            rectangle.x = rect2->x + rect2->w + 1;
        }
    return;
}

void Player::updateY(vector<Block>& vec, bool* ground, STATE& lols) {
    if (ySpeed == 0)
        return;
    
    rectangle.y = rectangle.y + ySpeed;
    if (rectangle.y < 0)
        rectangle.y = 0;
    if (rectangle.y > WINDOW_HEIGHT - CHAR_HEIGHT) {
        rectangle.y = WINDOW_HEIGHT - CHAR_HEIGHT;
        *ground = true;
    }
    
    // int left1 = rectangle.x;                    // playerx
    // int right1 = rectangle.x + rectangle.w;         // playerx+width
    // int top1 = rectangle.y;                     // playerY
    // int bottom1 = rectangle.y + rectangle.h;        // playerY+height

    int oldtop1 = rectangle.y - ySpeed;
    int oldbottom1 = rectangle.y + rectangle.h - ySpeed;
    
    vector<Block>::iterator it;
    for (it = vec.begin(); it != vec.end(); it++) {
    //for (unsigned int i = 0; i < vec.size(); i++) {             //++i or i++ ??
        //SDL_Rect* rect2 = vec[i]->getRectangle();
        SDL_Rect* rect2 = (*it).getRectangle();

        // Find edges of rect2
        // int left2 = rect2->x;                    // blockX
        // int right2 = rect2->x + rect2->w;         // blockX+width
        // int top2 = rect2->y;                     // blockY
        // int bottom2 = rect2->y + rect2->h;        // blocky+height
        
        // no collision
        if ( rectangle.x > rect2->x + rect2->w || rectangle.x + rectangle.w < rect2->x  || rectangle.y > rect2->y + rect2->h || rectangle.y + rectangle.h < rect2->y)
            continue;
       
        // top
        if (rectangle.y < rect2->y && rect2->y < rectangle.y + rectangle.h && rectangle.y + rectangle.h < rect2->y + rect2->h) {
            rectangle.y = rect2->y - rectangle.h - 1;
            *ground = true;
        }

        // bottom, need to change state to free fall
        if  ((rect2->y < oldtop1 && oldtop1 < rect2->y + rect2->h && rect2->y + rect2->h < oldbottom1)) {
            rectangle.y = rect2->y + rect2->h + 1;
            if (lols == BUTTON_PRESS || lols == DECELERATE || lols == DESCEND)
                lols = FREEFALL;
        }

    }
    return;
}

void Player::draw(SDL_Rect *anim) {
    // erase old player
    //rectangle.x = xLoc;
    //rectangle.y = yLoc;
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //SDL_RenderFillRect(renderer, &rectangle);
    // draw new player
    // rectangle.x = newXLoc;
    // rectangle.y = newYLoc;
    // xLoc = newXLoc;
    // yLoc = newYLoc;
    //cout << animation.x << endl;
    SDL_RenderCopy(renderer, image, anim, &rectangle);
    //SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
    //SDL_RenderFillRect(renderer, &rectangle);
    //SDL_RenderPresent(renderer);
}

bool Player::teleport(Portal blue, Portal orange, STATE& jumpState) {
    if(!(blue.getActive() && orange.getActive())){
        // dont do anything if you dont have both portals active.
        return false;
    }
    rectangle.x += xSpeed;
    rectangle.y += ySpeed;
    setX(rectangle.x);
    setY(rectangle.y);
    if(SDL_HasIntersection(blue.getRect(), &rectangle)) {
        //cout << "touching blue portal" << endl;
        // TELEPORT TO ORANGE PORTAL
        int oldXSpeed = xSpeed;
        int oldYSpeed = ySpeed;
        switch (orange.getSide()) {
            case TOP:
                setX(orange.getX() + orange.getWidth()/2 - CHAR_WIDTH/2);
                setY(orange.getY() - CHAR_HEIGHT/2 - 5);
                setXSpeed(oldXSpeed);
                setYSpeed(-20);
                /*
                switch (blue.getSide()) {
                    case TOP:
                        setXSpeed(oldXSpeed);
                        setYSpeed(-oldYSpeed);
                        break;
                    case LEFT:
                        setXSpeed(oldYSpeed);
                        setYSpeed(-oldXSpeed);
                        break;
                    case RIGHT:
                        setXSpeed(-oldYSpeed);
                        setYSpeed(oldXSpeed);
                        break;
                    case BOTTOM:
                        setXSpeed(oldXSpeed);
                        setYSpeed(oldYSpeed);
                        break;
                    default:
                        break;
                }
                */
                break;
            case LEFT:
                setX(orange.getX() - CHAR_WIDTH/2 - 5);
                setY(orange.getY() + orange.getHeight()/2 - CHAR_HEIGHT/2);
                setXSpeed(-20);
                setYSpeed(0);
                /*
                switch (blue.getSide()) {
                    case TOP:
                        setXSpeed(-oldYSpeed);
                        setYSpeed(oldXSpeed);
                        break;
                    case LEFT:
                        setXSpeed(-oldXSpeed);
                        setYSpeed(oldYSpeed);
                        break;
                    case RIGHT:
                        setXSpeed(oldXSpeed);
                        setYSpeed(oldYSpeed);
                        break;
                    case BOTTOM:
                        setXSpeed(oldYSpeed);
                        setYSpeed(-oldXSpeed);
                        break;
                    default:
                        break;
                }
                */
                break;
            case RIGHT:
                setX(orange.getX() + orange.getWidth() + 5);
                setY(orange.getY() + orange.getWidth()/2 - CHAR_WIDTH/2);
                setYSpeed(0);
                setXSpeed(20);
                /*
                switch (blue.getSide()) {
                    case TOP:
                        setXSpeed(oldYSpeed);
                        setYSpeed(-oldXSpeed);
                        break;
                    case LEFT:
                        setXSpeed(-oldXSpeed);
                        setYSpeed(oldYSpeed);
                        break;
                    case RIGHT:
                        setXSpeed(oldXSpeed);
                        setYSpeed(oldYSpeed);
                        break;
                    case BOTTOM:
                        setXSpeed(-oldYSpeed);
                        setYSpeed(oldXSpeed);
                        break;
                    default:
                        break;
                }
                */
                break;
            case BOTTOM:
                setX(orange.getX() + orange.getWidth()/2 - CHAR_WIDTH/2);
                setY(orange.getY() + orange.getHeight() + 5);
                setYSpeed(20);
                setXSpeed(0);
                /*
                switch (blue.getSide()) {
                    case TOP:
                        setXSpeed(oldXSpeed);
                        setYSpeed(oldYSpeed);
                        break;
                    case LEFT:
                        setXSpeed(-oldYSpeed);
                        setYSpeed(oldXSpeed);
                        break;
                    case RIGHT:
                        setXSpeed(oldYSpeed);
                        setYSpeed(-oldXSpeed);
                        break;
                    case BOTTOM:
                        setXSpeed(oldXSpeed);
                        setYSpeed(-oldYSpeed);
                        break;
                    default:
                        break;
                }
                */
                break;
            default:
                break;
        }
	jumpState = DECELERATE;
	    return true;
    } else if(SDL_HasIntersection(orange.getRect(), &rectangle)){
        //cout << "touching orange portal" << endl;
        // TELEPORT TO BLUE PORTAL
        int oldXSpeed = xSpeed;
        int oldYSpeed = ySpeed;
        switch (blue.getSide()) {
            case TOP:
                setX(blue.getX() + blue.getWidth()/2 - CHAR_WIDTH/2);
                setY(blue.getY() - CHAR_HEIGHT/2 - 5);
                setXSpeed(oldXSpeed);
                setYSpeed(-20);
                /*
                switch (orange.getSide()) {
                    case TOP:
                        setXSpeed(oldXSpeed);
                        setYSpeed(-oldYSpeed);
                        break;
                    case LEFT:
                        setXSpeed(oldYSpeed);
                        setYSpeed(-oldXSpeed);
                        break;
                    case RIGHT:
                        setXSpeed(-oldYSpeed);
                        setYSpeed(oldXSpeed);
                        break;
                    case BOTTOM:
                        setXSpeed(oldXSpeed);
                        setYSpeed(oldYSpeed);
                        break;
                    default:
                        break;
                }
                */
                break;
            case LEFT:
                setX(blue.getX() - CHAR_WIDTH/2 - 5);
                setY(blue.getY() + blue.getHeight()/2 - CHAR_HEIGHT/2);
                setXSpeed(-20);
                setYSpeed(0);
                /*
                switch (orange.getSide()) {
                    case TOP:
                        setXSpeed(-oldYSpeed);
                        setYSpeed(oldXSpeed);
                        break;
                    case LEFT:
                        setXSpeed(-oldXSpeed);
                        setYSpeed(oldYSpeed);
                        break;
                    case RIGHT:
                        setXSpeed(oldXSpeed);
                        setYSpeed(oldYSpeed);
                        break;
                    case BOTTOM:
                        setXSpeed(oldYSpeed);
                        setYSpeed(-oldXSpeed);
                        break;
                    default:
                        break;
                }
                */
                jumpState = FREEFALL;
                break;
            case RIGHT:
                setX(blue.getX() + blue.getWidth() + 5);
                setY(blue.getY() + blue.getWidth()/2 - CHAR_WIDTH/2);
                setXSpeed(20);
                setYSpeed(0);
                /*
                switch (orange.getSide()) {
                    case TOP:
                        setXSpeed(oldYSpeed);
                        setYSpeed(-oldXSpeed);
                        break;
                    case LEFT:
                        setXSpeed(-oldXSpeed);
                        setYSpeed(oldYSpeed);
                        break;
                    case RIGHT:
                        setXSpeed(oldXSpeed);
                        setYSpeed(oldYSpeed);
                        break;
                    case BOTTOM:
                        setXSpeed(-oldYSpeed);
                        setYSpeed(oldXSpeed);
                        break;
                    default:
                        break;
                }
                */
                jumpState = FREEFALL;
                break;
            case BOTTOM:
                setX(blue.getX() + blue.getWidth()/2 - CHAR_WIDTH/2);
                setY(blue.getY() + blue.getHeight() + 5);
                setXSpeed(0);
                setYSpeed(20);
                /*
                switch (orange.getSide()) {
                    case TOP:
                        setXSpeed(oldXSpeed);
                        setYSpeed(oldYSpeed);
                        break;
                    case LEFT:
                        setXSpeed(-oldYSpeed);
                        setYSpeed(oldXSpeed);
                        break;
                    case RIGHT:
                        setXSpeed(oldYSpeed);
                        setYSpeed(-oldXSpeed);
                        break;
                    case BOTTOM:
                        setXSpeed(oldXSpeed);
                        setYSpeed(-oldYSpeed);
                        break;
                    default:
                        break;
                }
                */
                break;
            default:
                break;
        }
	jumpState = DECELERATE;
	    return true;
    }
    rectangle.x -= xSpeed;
    rectangle.y -= ySpeed;
    setX(rectangle.x);
    setY(rectangle.y);
    return false;
}
