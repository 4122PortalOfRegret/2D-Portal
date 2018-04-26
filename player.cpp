#include "player.h"
#include "SDL.h"

Player::Player() : Block() {}

Player::Player(int x, int y, int w, int h, SDL_Renderer* r, SDL_Rect* rect) : Block(x, y, h, w, r, rect) {}

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
    Block::setX(x);
}

void Player::setY(int y) {
    Block::setY(y);
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
    Block::setColorR(color);
}

void Player::setColorG(Uint8 color) {
    Block::setColorG(color);
}

void Player::setColorB(Uint8 color) {
    Block::setColorB(color);
}

void Player::setColorA(Uint8 color) {
    Block::setColorA(color);
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
    SDL_SetRenderDrawColor(renderer, red, blue, green, alpha);
    SDL_RenderFillRect(renderer, &rectangle);
    SDL_RendererPresent(renderer);
}