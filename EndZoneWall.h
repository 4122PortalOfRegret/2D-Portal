#ifndef ENDZONEWALL_H
#define ENDZONEWALL_H
//#include "block.h"
#include "utils.h"

class EndZoneWall 
{
    public:
        explicit EndZoneWall(int x, int y, int h, int w, SDL_Renderer* ref, SDL_Rect& rect);
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

//        void draw();

    private:
        SDL_Renderer* renderer;
        SDL_Rect rectangle;
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
};
#endif
