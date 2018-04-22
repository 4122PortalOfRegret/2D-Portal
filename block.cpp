#include "block.h"


Block::Block(int x, int y int h, int w) : 
	Object(x, y, h, w) {}

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

Uint8 getColorR() {
	return red;
}

Uint8 getColorG() {
	return green;
}

Uint8 getColorB() {
	return blue;
}

Uint8 getColorA() {
	return alpha;
}

void setColorR(Uint8 r) {
	red = r;
}

void setColorA(Uint8 a) {
	alpha = a;
}

void setColorB(Uint8 b) {
	blue = b;
}

void setColorG(Uint8 g) {
	green = g;
}