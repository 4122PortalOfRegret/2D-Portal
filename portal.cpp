#pragma once
#include "portal.h"
// Make sure there are only ever 2 instances of this object
// One will be blue and the other will be orange
// Need to first check if you have the right portal.
// Then toggle if it is active, then draw it


Portal::Portal(bool portalclr, SDL_Renderer* ref) {
    isActive = false;
    setX(0);
    setY(0);
    setColorA(255);
    renderer = ref;
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

bool Portal::getActive() {
  return isActive;
}


void Portal::PortalHit(vector<Block>& vec, SDL_Rect &player,int mouse_X, int mouse_Y, Portal otherp){
    double x = mouse_X - (player.x + CHAR_WIDTH/2);
    double y = mouse_Y - (player.y + CHAR_HEIGHT/2);
    double length = sqrt( x*x + y*y );

    double addx = x / length;
    double addy = y / length;

    x = (player.x + CHAR_WIDTH/2);
    y = (player.y + CHAR_HEIGHT/2);

    while(x>0 && x<WINDOW_WIDTH && y>0 && y<WINDOW_HEIGHT)
    {
        //cout << "what" << endl;
      x += addx;
      y += addy;
    }
    int playerheadx = player.x + CHAR_WIDTH/2;
    int playerheady = player.y + CHAR_HEIGHT/2;

    int pheadx = playerheadx;
    int pheady = playerheady;

    int minx;
    int miny;
    SDL_Rect* collisionRect;
    Block collideBlock;

    double mindist = 9999;
    double distance;

    bool collide = false;

    int x2 = (int)x;
    int y2 = (int)y;

    SDL_bool hit;

    bool oldState = isActive;
    int oldXLoc = xLoc;
    int oldYLoc = yLoc;
    int oldHeight = height;
    int oldWidth = width;

    vector<Block>::iterator it;
    for (it = vec.begin(); it != vec.end(); it++) {
        SDL_Rect* rect2 = (*it).getRectangle();
        hit = SDL_IntersectRectAndLine(rect2, &playerheadx , &playerheady,&x2,&y2);
        if (hit){
            collide = true;
            distance = sqrt(pow((playerheadx - pheadx), 2) +  pow((playerheady - pheady), 2));
            if (distance < mindist) {
                collisionRect = rect2;
                collideBlock = *it;
                minx = playerheadx;
                miny = playerheady;
                mindist = distance;
            }
            distance = sqrt(pow((x2 - pheadx), 2) +  pow((y2 - pheady), 2));
            if (distance < mindist) {
                collisionRect = rect2;
                minx = x2;
                miny = y2;
                mindist = distance;
            }
            x2 = (int)x;
            y2 = (int)y;
            playerheadx = pheadx;
            playerheady = pheady;
        }
    }

    bool valid = false;
    if(collideBlock.getType()) {
      return;
    }
    if(collide) {
        if (minx > collisionRect->x && minx < collisionRect->x + collisionRect->w && miny == collisionRect->y)                      // top
        {
            cout << "top" << endl;
            if (minx - 40 >= collisionRect->x && minx + 40 <= collisionRect->x + collisionRect->w){
                xLoc = minx - 40;
                width = 80;
                yLoc = miny - 5;
                height = 10;
                valid = true;                
            }
        }

        if (minx > collisionRect->x && minx < collisionRect->x + collisionRect->w && miny == collisionRect->y + collisionRect->h - 1)    // bottom
        {
                        cout << "bot" << endl;
            if (minx - 40 >= collisionRect->x && minx + 40 <= collisionRect->x + collisionRect->w){
                xLoc = minx - 40;
                width = 80;
                yLoc = miny - 5;
                height = 10;
                valid = true;               
            }
        }

        if (miny > collisionRect->y && miny < collisionRect->y + collisionRect->h && minx == collisionRect->x)                      // left
        {
                        cout << "lef" << endl;
            if ((miny - 40) >= collisionRect->y && miny + 40 <= collisionRect->y + collisionRect->h){
                xLoc = minx - 5;
                width = 10;
                yLoc = miny - 40;
                height = 80;
                valid = true;               
            }
        }

        if (miny > collisionRect->y && miny < collisionRect->y + collisionRect->h && minx == collisionRect->x + collisionRect->w - 1)                      // right
        {
                        cout << "right" << endl;
            if (miny - 40 >= collisionRect->y && miny + 40 <= collisionRect->y + collisionRect->h){
                xLoc = minx - 5;
                width = 10;
                yLoc = miny - 40;
                height = 80;
                valid = true;              
            }
        }
    }

    if(valid){
      vector<Block>::iterator it;
      SDL_Rect newPortal = {xLoc, yLoc, width, height};
      for (it = vec.begin(); it != vec.end(); it++) {
          SDL_Rect* rect3 = (*it).getRectangle();
          if (collisionRect != rect3)
          {
              if(SDL_HasIntersection(&newPortal,rect3)){
                isActive = oldState;
                xLoc = oldXLoc;
                yLoc = oldYLoc;
                height = oldHeight;
                width = oldWidth;
                return;
              }
          }
      }
      if(otherp.getActive()) {
        SDL_Rect portalOne = {otherp.getX(), otherp.getY(), otherp.getWidth(), otherp.getHeight()};
          if(SDL_HasIntersection(&portalOne,&newPortal)){
                isActive = oldState;
                xLoc = oldXLoc;
                yLoc = oldYLoc;
                height = oldHeight;
                width = oldWidth;
                return;
          }
        }
    }
    isActive = true;
}

void Portal::draw() {
    if (isActive) {
        // erase old player
        // draw new player
        //std::cout << "New X Location = " << newXLoc << " X Speed = " << xSpeed << std::endl;
        //std::cout << "New Y Location = " << newYLoc << " Y Speed = " << ySpeed << std::endl; 
        //rectangle.x = xLoc;
        //rectangle.y = yLoc;
        SDL_Rect rectangle = {xLoc, yLoc, width, height};
        SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
        SDL_RenderFillRect(renderer, &rectangle);
    } 
}
