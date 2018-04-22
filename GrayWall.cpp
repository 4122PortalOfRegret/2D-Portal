#include "GrayWall.h"


GrayWall::GrayWall(int x, int y, int h, int w) : 
	Block(x, y, h, w) {
    setColorR(200);
    setColorG(200);
    setColorB(200);
    setColorA(255);
  }

void GrayWall::setX(int x){
    xLoc = x;
}

void GrayWall::setY(int y){
    yLoc = y;
}

void GrayWall::setHeight(int h){
    height = h;
}

void GrayWall::setWidth(int w){
    width = w;
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