#include "object.h"

object::object(int x, int y, int h, int w){
    setX(x);
    setY(y);
    setHeight(h);
    setWidth(w);
    //setXSpeed(0);
    //setYSpeed(0);
}

void object::setX(int x){
    xLoc = x;
}

void object::setY(int y){
    yLoc = y;
}

void object::setHeight(int h){
    height = h;
}

void object::setWidth(int w){
    width = w;
}

int object::getX(){
    return xLoc;
}

int object::getY(){
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

int object::getHeight(){
    return height;
}

int object::getWidth(){
    return width;
}