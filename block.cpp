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