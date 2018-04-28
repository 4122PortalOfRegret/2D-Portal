#ifndef BLOCK_H
#define BLOCK_H

#include "utils.h"

class Block
{
    public:
        explicit Block();
        explicit Block(int x, int y, int w, int h, SDL_Renderer* r, SDL_Rect& rect);
        int getX();
        int getY();
        //int getNewX();
        //int getNewY();
        int getHeight();
        int getWidth();
        void setX(int x);
        void setY(int y);
        void setHeight(int h);
        void setWidth(int w);
        SDL_Rect* getRectangle(); 
        void setColorR(Uint8 color);
        void setColorG(Uint8 color);
        void setColorB(Uint8 color);
        void setColorA(Uint8 color);
        Uint8 getColorR();
        Uint8 getColorG();
        Uint8 getColorB();
        Uint8 getColorA();

        void draw();
        //void update();
       
    private:
        int xLoc;
        int yLoc;
        //int newXLoc;
        //int newYLoc;
        int height;
        int width;
        Uint8 red;
        Uint8 blue;
        Uint8 green;
        Uint8 alpha;
        SDL_Renderer* renderer;
        SDL_Rect rectangle;
};

#endif
