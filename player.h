#include "block.h"

class Player : public Block
{
    public:
        explicit Player(int x, int y, int h, int w);
        int getX();
        int getY();
        int getNewX();
        int getNewY();
        int getHeight();
        int getWidth();
        void setX(int x);
        void setY(int y);
        void setNewX(int x);
        void setNewY(int y);
        void setXSpeed(int x);
        void setYSpeed(int y);
        void getXSpeed();
        void getYSpeed();
        void setHeight(int h);
        void setWidth(int w);
        void setColorR(Uint8 color);
        void setColorG(Uint8 color);
        void setColorB(Uint8 color);
        void setColorA(Uint8 color);
        Uint8 getColorR();
        Uint8 getColorG();
        Uint8 getColorB();
        Uint8 getColorA();
        void update();

//        void draw();

    private:
        int xLoc;
        int yLoc;
        int newXLoc;
        int newYLoc;
        int xSpeed;
        int ySpeed;
        int height;
        int width;
        Uint8 red;
        Uint8 blue;
        Uint8 green;
        Uint8 alpha;
};