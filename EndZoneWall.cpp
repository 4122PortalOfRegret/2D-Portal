#include "EndZoneWall.h"


EndZoneWall::EndZoneWall(int x, int y, int h, int w, SDL_Renderer* ref, SDL_Rect& rect) {
	setX(x);
	setY(y);
	setHeight(h);
	setWidth(w);
    setColorR(171);
    setColorG(130);
    setColorB(255);
    setColorA(255);
	rectangle = rect;
	renderer = ref;
	draw();
}

void EndZoneWall::setX(int x){
    rectangle.x = x;
}

void EndZoneWall::setY(int y){
    rectangle.y = y;
}

void EndZoneWall::setHeight(int h){
    rectangle.x = h;
}

void EndZoneWall::setWidth(int w){
    rectangle.w = w;
}

int EndZoneWall::getX(){
    return xLoc;
}

int EndZoneWall::getY(){
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

int EndZoneWall::getHeight(){
    return height;
}

int EndZoneWall::getWidth(){
    return width;
}

SDL_Rect* EndZoneWall::getRectangle() {
    return &rectangle;
}

Uint8 EndZoneWall::getColorR() {
	return red;
}

Uint8 EndZoneWall::getColorG() {
	return green;
}

Uint8 EndZoneWall::getColorB() {
	return blue;
}

Uint8 EndZoneWall::getColorA() {
	return alpha;
}

void EndZoneWall::setColorR(Uint8 r) {
	red = r;
}

void EndZoneWall::setColorA(Uint8 a) {
	alpha = a;
}

void EndZoneWall::setColorB(Uint8 b) {
	blue = b;
}

void EndZoneWall::setColorG(Uint8 g) {
	green = g;
}

void EndZoneWall::draw() {
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
