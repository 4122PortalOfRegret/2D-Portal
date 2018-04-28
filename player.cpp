#include "player.h"

Player::Player() : Block() {
    setColorR(216);
    setColorG(191);
    setColorB(216);
    setColorA(255);
}

Player::Player(int x, int y, int w, int h, SDL_Renderer* r, SDL_Rect& rect, SDL_Rect& a, SDL_Texture* i) {
    setXSpeed(0);
    setYSpeed(0);
    renderer = r;
    rectangle = rect;
    animation = a;
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
    return Block::getX();
}

int Player::getY() {
    return Block::getY();
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
    return Block::getHeight();
}

int Player::getWidth() {
    return Block::getWidth();
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
    return Block::getColorR();
}

Uint8 Player::getColorG() {
    return Block::getColorG();
}

Uint8 Player::getColorB() {
    return Block::getColorB();
}

Uint8 Player::getColorA() {
    return Block::getColorA();
}

// move the player to a new location based on speeds
void Player::update(vector<Block*>& vec, bool* ground, STATE& jump) {
    // if (xSpeed == 0 && ySpeed == 0)
    //     return;
    // newXLoc = xLoc + xSpeed;

    // if (newXLoc < 0)
    //     newXLoc = 0;
    // if (newXLoc > WINDOW_WIDTH - width)
    //     newXLoc = WINDOW_WIDTH - width;
    // newYLoc = yLoc + ySpeed;
    // if (newYLoc < 0)
    //     newYLoc = 0;
    // if (newYLoc > WINDOW_HEIGHT - height)
    //     newYLoc = WINDOW_HEIGHT - height;
    for (unsigned int i = 0; i < vec.size(); ++i) {
        updateX(vec[i]->getRectangle(), jump);
        updateY(vec[i]->getRectangle(), ground, jump);
    }
}

void Player::updateX(const SDL_Rect* rect2, STATE& lols){
    if (xSpeed == 0)
        return;
    newXLoc = xLoc + xSpeed;
    
    if (newXLoc < 0)
        newXLoc = 0;
    if (newXLoc > WINDOW_WIDTH - CHAR_WIDTH)
        newXLoc = WINDOW_WIDTH - CHAR_WIDTH;
    
    int left1 = xLoc;                    // playerx
    int right1 = xLoc + rectangle.w;         // playerx+width
    int top1 = yLoc;                     // playerY
    int bottom1 = yLoc + rectangle.h;        // playerY+height
    
    // Find edges of rect2
    int left2 = *rect2.x;                    // blockX
    int right2 = *rect2.x + *rect2.w;         // blockX+width
    int top2 = *rect2.y;                     // blockY
    int bottom2 = *rect2.y + *rect2.h;        // blocky+height
    
    
    int oldleft1 = xLoc - xSpeed;
    int oldright1 = rectangle.x + rectangle.w - xSpeed;
    
    
    if ( left1 > right2 || right1 < left2 || top1 > bottom2 || bottom1 < top2 )// Left 1 is right of right 2
        return; // No collision
    
    if (oldleft1 < left2 && oldright1 < left2 && (((top1 < top2) || (bottom1 < top1))  || ((top1 < bottom2) || bottom1 < bottom2)))        // left
        newXLoc = *rect2.x - rectangle.w - 1;
    
    if (oldleft1 > right2 && oldright1 > right2 && (((top1 < top2) || (bottom1 < top1))  || ((top1 < bottom2) || (bottom1 < bottom2))))  // right
        newXLoc = *rect2.x + *rect2.w + 1;
    
    return;
}

void Player::updateY(const SDL_Rect* rect2, bool* ground, STATE& lols)
{
    if (ySpeed == 0)
        return;
    
    newYLoc = newYLoc + ySpeed;
    if (newYLoc < 0)
        newYLoc = 0;
    if (newYLoc > WINDOW_HEIGHT - CHAR_HEIGHT) {
        newYLoc = WINDOW_HEIGHT - CHAR_HEIGHT;
        ground = true;
    }
    
    int left1 = rectangle.x;                    // playerx
    int right1 = rectangle.x + rectangle.w;         // playerx+width
    int top1 = rectangle.y;                     // playerY
    int bottom1 = rectangle.y + rectangle.h;        // playerY+height
    
    // Find edges of rect2
    int left2 = *rect2.x;                    // blockX
    int right2 = *rect2.x + *rect2.w;         // blockX+width
    int top2 = *rect2.y;                     // blockY
    int bottom2 = *rect2.y + *rect2.h;        // blocky+height
    
    int oldtop1 = rectangle.y - ySpeed;
    int oldbottom1 = rectangle.y + rectangle.h - ySpeed;
    
    // no collition
    if ( left1 > right2 || right1 < left2  || top1 > bottom2 || bottom1 < top2)
        return;
    
    // top
    if (top1 < top2 && top2 < bottom1 && bottom1 < bottom2) {
        newYLoc = *rect2.y - rectangle.h - 1;
        ground = true;
        //*prevPlat = true;
    }

    // bottom
    // need to change state to free fall
    if  ((top2 < oldtop1 && oldtop1 < bottom2 && bottom2 < oldbottom1)) {
        newYLoc = *rect2.y + *rect2.h + 1;
        if (*lols == BUTTON_PRESS || *lols == DECELERATE || *lols == DESCEND)
            *lols = FREEFALL;
    }

    return;
}

void Player::draw() {
    // erase old player
    //rectangle.x = xLoc;
    //rectangle.y = yLoc;
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //SDL_RenderFillRect(renderer, &rectangle);
    // draw new player
    rectangle.x = newXLoc;
    rectangle.y = newYLoc;
    xLoc = newXLoc;
    yLoc = newYLoc;
    SDL_RenderCopy(renderer, image, &animation, &rectangle);
    //SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
    //SDL_RenderFillRect(renderer, &rectangle);

    //SDL_RenderPresent(renderer);
}