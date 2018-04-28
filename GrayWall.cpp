#include "GrayWall.h"


GrayWall::GrayWall(int x, int y, int h, int w, SDL_Renderer* ref, SDL_Rect& rectangle) : 
	{
	setX(x);
	setY(y);
	setHeight(h);
	setWidth(w);
    setColorR(200);
    setColorG(200);
    setColorB(200);
    setColorA(255);
	rectangle = rect;
	renderer = ref;
	draw();
  }

void GrayWall::setX(int x){
    rectangle.x = x;
}

void GrayWall::setY(int y){
    rectangle.y = y;
}

void GrayWall::setHeight(int h){
    rectangle.x = h;
}

void GrayWall::setWidth(int w){
    rectangle.w = w;
}

int GrayWall::getX(){
    return xLoc;
}

int GrayWall::getY(){
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

int GrayWall::getHeight(){
    return height;
}

int GrayWall::getWidth(){
    return width;
}

Uint8 GrayWall::getColorR() {
	return red;
}

Uint8 GrayWall::getColorG() {
	return green;
}

Uint8 GrayWall::getColorB() {
	return blue;
}

Uint8 GrayWall::getColorA() {
	return alpha;
}

void GrayWall::setColorR(Uint8 r) {
	red = r;
}

void GrayWall::setColorA(Uint8 a) {
	alpha = a;
}

void GrayWall::setColorB(Uint8 b) {
	blue = b;
}

void GrayWall::setColorG(Uint8 g) {
	green = g;
}

void GrayWall:draw() {
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
