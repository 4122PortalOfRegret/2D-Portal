#include "block.h"
#include "SDL.h"

Block::Block() : obj() {}

Block::Block(int x, int y, int w, int h, SDL_Renderer* r, SDL_Rect* rect) : obj(x, y, h, w) {
    renderer = r;
    rectangle = *rect;
}

void Block::setX(int x){
    obj::setX(x);
}

void Block::setY(int y){
    obj::setY(y);
}

void Block::setHeight(int h){
    obj::setHeight(h);
}

void Block::setWidth(int w){
    obj::setWidth(w);
}

int Block::getX(){
    return obj::getX();
}

int Block::getY(){
    return obj::getY();
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
    return obj::getHeight();
}

int Block::getWidth(){
    return obj::getWidth();
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
    SDL_RendererPresent(renderer);
}