#include "obj.h"

obj::obj() {
    setX(0);
    setY(0);
    setHeight(0);
    setWidth(0);
}

obj::obj(int x, int y, int w, int h){
    setX(x);
    setY(y);
    setHeight(h);
    setWidth(w);
    //setXSpeed(0);
    //setYSpeed(0);
}

void obj::setX(int x){
    xLoc = x;
}

void obj::setY(int y){
    yLoc = y;
}

void obj::setHeight(int h){
    height = h;
}

void obj::setWidth(int w){
    width = w;
}

int obj::getX(){
    return xLoc;
}

int obj::getY(){
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

int obj::getHeight(){
    return height;
}

int obj::getWidth(){
    return width;
}
