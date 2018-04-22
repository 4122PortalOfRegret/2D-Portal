#include "Portal.h"


Portal::Portal(int x, int y, bool pc, bool vertOrHoriz) {
    setX(x);
    setY(y);
    setColorA(255);
    if (vertOrHoriz) { // Vertical = 0 | Horizontal = 1
      setHeight(50);
      setWidth(20);
    } else {
      setHeight(20);
      setWidth(50);
    }
    if (!pc) {  // Colors correspond to blue portal
      portalColor = 0;
      setColorR(0);
      setColorG(120);
      setColorB(255);
    } else {    // Colors correspond to orange portal
      portalColor = 1;
      setColorR(253);
      setColorG(102);
      setColorB(0);
    }
  }

void Portal::setX(int x){
    xLoc = x;
}

void Portal::setY(int y){
    yLoc = y;
}

void Portal::setHeight(int h){
    height = h;
}

void Portal::setWidth(int w){
    width = w;
}

int Portal::getX(){
    return xLoc;
}

int Portal::getY(){
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

int Portal::getHeight(){
    return height;
}

int Portal::getWidth(){
    return width;
}

Uint8 Portal::getColorR() {
	return red;
}

Uint8 Portal::getColorG() {
	return green;
}

Uint8 Portal::getColorB() {
	return blue;
}

Uint8 Portal::getColorA() {
	return alpha;
}

void Portal::setColorR(Uint8 r) {
	red = r;
}

void Portal::setColorA(Uint8 a) {
	alpha = a;
}

void Portal::setColorB(Uint8 b) {
	blue = b;
}

void Portal::setColorG(Uint8 g) {
	green = g;
}

// This function is toggling if you want the portal to be drawn or not
void Portal::toggleClick() {
  isActive = !isActive;
}