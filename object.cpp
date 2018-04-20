#include "object.h"

Object::Object(int x, int y, int h, int w){
    setX(x);
    setY(y);
    setHeight(h);
    setWidth(w);
    setXSpeed(0);
    setYSpeed(0);
}

void Object::setX(int x){
    xLoc = x;
}

void Object::setY(int y){
    yLoc = y;
}

void Object::setHeight(int h){
    height = h;
}

void Object::setWidth(int w){
    width = w;
}

int Object::getX(){
    return xLoc;
}

int Object::getY(){
    return yLoc;
}

int Object::getNewX(){
    return newXLoc;
}

int Object::getNewY(){
    return newYLoc;
}

void Object::setXSpeed(int x){
    xSpeed = x;
}

void Object::setYSpeed(int y){
    ySpeed = y;
}

void Object::update(){

}

int Object::getHeight(){
    return height;
}

int Object::getWidth(){
    return width;
}

/*
void Object::draw(){

    //draw gray at xLoc, yLoc
    //draw sprite at newXLoc, newYLoc
    xLoc = newXLoc;
    yLoc = newYLoc;

}
*/
/*
void Object::hitDetection(){
    int mapColor;

    //X detection
    int done = 0;
    int finalX = xLoc;
    if(xSpeed > 0){ //moving to right
        for(int i = xLoc + width; i < xLoc + width + xSpeed; i++){
            for(int j = yLoc; j < yLoc + height; j++) {
                mapColor = map(i, j);
                if(mapColor != 0){
                    xSpeed = 0;
                    done = 1;
                    break;
                }
            }
            if(done){
                break;
            }
            finalX = i - width;
        }
    } else if(xSpeed < 0) { //moving to left
        for(int i = xLoc; i > xLoc + xSpeed - 1; i--){
            for(int j = yLoc; j < yLoc + height; j++) {
                mapColor = map(i, j);
                if(mapColor != 0){
                    xSpeed = 0;
                    done = 1;
                    break;
                }
            }
            if(done){
                break;
            }
            finalX = i;
        }
    }

    //Speed Y
    done = 0;
    int finalY = yLoc;
    if(ySpeed > 0){ //going down
        for(int i = yLoc + height; i < yLoc + height + ySpeed; i++){
            for(int j = xLoc; j < xLoc + width; j++) {
                mapColor = map(i, j);
                if(mapColor != 0){
                    ySpeed = 0;
                    done = 1;
                    break;
                }
            }
            if(done){
                break;
            }
            finalY = i - height;
        }
    } else if(ySpeed < 0) { //going up
        for(int i = yLoc; i > yLoc + ySpeed - 1; i--){
            for(int j = xLoc; j < xLoc + width; j++) {
                mapColor = map(i, j);
                if(mapColor != 0){
                    ySpeed = 0;
                    done = 1;
                    break;
                }
            }
            if(done){
                break;
            }
            finalY = i;
        }
    }

    //Final X and Final Y are what can be drawn for next
    newXLoc = finalX;
    newYLoc = finalY;
}

void Object::
*/
