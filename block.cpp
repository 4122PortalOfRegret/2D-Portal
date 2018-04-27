#include "block.h"
#include "SDL.h"

Block::Block() {
    setX(0);
    setY(0);
    setHeight(0);
    setWidth(0);
    setColorR(100);
    setColorB(100);
    setColorG(100);
    setColorA(255);
}

Block::Block(int x, int y, int w, int h, SDL_Renderer* r, SDL_Rect& rect) {
    setX(x);
    setY(y);
    setHeight(h);
    setWidth(w);
    renderer = r;
    rectangle = rect;
    setColorR(100);
    setColorB(100);
    setColorG(100);
    setColorA(255);
}

void Block::setX(int x){
    xLoc = x;
}

void Block::setY(int y){
    yLoc = y;
}

void Block::setHeight(int h){
    height = h;
}

void Block::setWidth(int w){
    width = w;
}

int Block::getX(){
    return xLoc;
}

int Block::getY(){
    return yLoc;
}

//int Object::getNewX(){
  //  return newXLoc;
//}

//int Object::getNewY(){
  //  return newYLoc;
//}

//void Object::setXSpeed(int x){
  //  xSpeed = x;
//}

//void Object::setYSpeed(int y){
  //  ySpeed = y;
//}

//void Object::update(){

//}

int Block::getHeight(){
    return height;
}

int Block::getWidth(){
    return width;
}

Uint8 Block::getColorR() {
	  return red;
}

Uint8 Block::getColorG() {
	  return green;
}

Uint8 Block::getColorB() {
	  return blue;
}

Uint8 Block::getColorA() {
	  return alpha;
}

void Block::setColorR(Uint8 r) {
	  red = r;
}

void Block::setColorA(Uint8 a) {
	  alpha = a;
}

void Block::setColorB(Uint8 b) {
	  blue = b;
}

void Block::setColorG(Uint8 g) {
	  green = g;
}

void Block::draw() {
    // draw the block, should only need to draw one time
    rectangle.x = xLoc;
    rectangle.y = yLoc;
    SDL_SetRenderDrawColor(renderer, red, blue, green, alpha);
    SDL_RenderFillRect(renderer, &rectangle);
    //SDL_RenderPresent(renderer);
}