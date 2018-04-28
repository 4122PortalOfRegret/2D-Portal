#ifndef PORTAL_H
#define PORTAL_H
#include "block.h"
#include "utils.h"


class Portal : public Block
{
    public:
        explicit Portal(bool portalclr, bool vertOrHoriz, SDL_Renderer* ref);
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
        bool getPortalColor();
        Uint8 getColorR();
        Uint8 getColorG();
        Uint8 getColorB();
        Uint8 getColorA();
        void setColorR(Uint8 color);
        void setColorG(Uint8 color);
        void setColorB(Uint8 color);
        void setColorA(Uint8 color);
        void toggleClick();
        //void update();
        void draw(int mouse_X, int mouse_Y, bool direction);

//        void draw();

    private:
        int xLoc;
        int yLoc;
        SDL_Renderer* renderer;
        //int newXLoc;
        //int newYLoc;
        int height;
        int width;
        Uint8 red;
        Uint8 blue;
        Uint8 green;
        Uint8 alpha;
        bool isActive;
        bool oldDirection;
        bool portalColor; // blue == 0 | orange == 1
        
};

#endif
