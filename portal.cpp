#include "portal.h"

// Make sure there are only ever 2 instances of this object
// One will be blue and the other will be orange
// Need to first check if you have the right portal.
// Then toggle if it is active, then draw it


Portal::Portal(bool portalclr, bool vertOrHoriz, SDL_Renderer* ref) {
    isActive = false;
    setX(0);
    setY(0);
    setColorA(255);
    renderer = ref;
    if (vertOrHoriz) { // Vertical = 0 | Horizontal = 1
      setHeight(100);
      setWidth(10);
    } else {
      setHeight(10);
      setWidth(100);
    }
    if (!portalclr) {  // Colors correspond to blue portal
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
	//renderer = ref;
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

SDL_Rect* Portal::getRectangle() {
    return &rectangle;
}

bool Portal::getPortalColor() {
	return portalColor;
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

void Portal::draw(int mouse_X, int mouse_Y, bool direction) {
    if (isActive) {
        // erase old player
        // draw new player
        //std::cout << "New X Location = " << newXLoc << " X Speed = " << xSpeed << std::endl;
        //std::cout << "New Y Location = " << newYLoc << " Y Speed = " << ySpeed << std::endl;
    	  if (direction) { // Vertical = 0 | Horizontal = 1
            setHeight(100);
            setWidth(10);
        } else {
            setHeight(10);
            setWidth(100);
        }
    	  oldDirection = direction;
        xLoc = mouse_X;
        yLoc = mouse_Y;	  
        //rectangle.x = xLoc;
        //rectangle.y = yLoc;
        SDL_Rect rectangle = {xLoc, yLoc, width, height};
        SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
        SDL_RenderFillRect(renderer, &rectangle);
    } else {
        xLoc = mouse_X;
        yLoc = mouse_Y;
    	  if (oldDirection) { // Vertical = 0 | Horizontal = 1
            setHeight(100);
            setWidth(10);
        } else {
            setHeight(10);
            setWidth(100);
        }
        //rectangle.x = xLoc;
        //rectangle.y = yLoc;
        SDL_Rect rectangle = {xLoc, yLoc, width, height};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rectangle);
  }
}
