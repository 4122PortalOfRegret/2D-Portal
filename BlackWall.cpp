#include "BlackWall.h"


BlackWall::BlackWall(int x, int y, int h, int w, SDL_Renderer* ref, SDL_Rect& rectangle) : 
	Block(x, y, h, w) {
    setColorR(40);
    setColorG(40);
    setColorB(40);
    setColorA(255);
	rectangle = rect;
	renderer = ref;
	draw();
  }

void BlackWall::setX(int x){
    rectangle.x = x;
}

void BlackWall::setY(int y){
    rectangle.y = y;
}

void BlackWall::setHeight(int h){
    rectangle.x = h;
}

void BlackWall::setWidth(int w){
    rectangle.w = w;
}

int BlackWall::getX(){
    return xLoc;
}

int BlackWall::getY(){
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

int BlackWall::getHeight(){
    return height;
}

int BlackWall::getWidth(){
    return width;
}

Uint8 BlackWall::getColorR() {
	return red;
}

Uint8 BlackWall::getColorG() {
	return green;
}

Uint8 BlackWall::getColorB() {
	return blue;
}

Uint8 BlackWall::getColorA() {
	return alpha;
}

void BlackWall::setColorR(Uint8 r) {
	red = r;
}

void BlackWall::setColorA(Uint8 a) {
	alpha = a;
}

void BlackWall::setColorB(Uint8 b) {
	blue = b;
}

void BlackWall::setColorG(Uint8 g) {
	green = g;
}

void BlackWall:draw() {
        // erase old player
        // draw new player
        //std::cout << "New X Location = " << newXLoc << " X Speed = " << xSpeed << std::endl;
        //std::cout << "New Y Location = " << newYLoc << " Y Speed = " << ySpeed << std::endl;
        //rectangle.x = xLoc;
        //rectangle.y = yLoc;
        //SDL_Rect rectangle = {xLoc, yLoc, width, height};
        SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
        SDL_RenderFillRect(renderer, &rectangle);
}
