#include "player.h"
#include "SDL.h"

Player::Player() : Block() {
    setColorR(216);
    setColorG(191);
    setColorB(216);
    setColorA(255);
}

Player::Player(int x, int y, int w, int h, SDL_Renderer* r, SDL_Rect& rect) {
    setXSpeed(0);
    setYSpeed(0);
    setX(x);
    setY(y);
    setHeight(h);
    setWidth(w);
    renderer = r;
    rectangle = rect;
    setColorR(216);
    setColorG(191);
    setColorB(216);
    setColorA(255);
}

void Player::setHeight(int h) {
    height = h;
}

void Player::setWidth(int w) {
    width = w;
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
}

void Player::setY(int y) {
    yLoc = y;
}

int Player::getHeight() {
    return Block::getHeight();
}

int Player::getWidth() {
    return Block::getWidth();
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
void Player::update() {
    if (xSpeed == 0 && ySpeed == 0)
        return;
    newXLoc = xLoc + xSpeed;

    if (newXLoc < 0)
        newXLoc = 0;
    if (newXLoc > WINDOW_WIDTH - width)
        newXLoc = WINDOW_WIDTH - width;
    newYLoc = yLoc + ySpeed;
    if (newYLoc < 0)
        newYLoc = 0;
    if (newYLoc > WINDOW_HEIGHT - height)
        newYLoc = WINDOW_HEIGHT - height;
}

void Player::draw() {
    // erase old player
    rectangle.x = xLoc;
    rectangle.y = yLoc;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rectangle);
    // draw new player
    rectangle.x = newXLoc;
    rectangle.y = newYLoc;
    xLoc = newXLoc;
    yLoc = newYLoc;
    SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
    SDL_RenderFillRect(renderer, &rectangle);

    //SDL_RenderPresent(renderer);
}