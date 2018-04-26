##include "Block.h"

class Player : public Block {
    public:
        explicit Object(int x, int y, int h, int w);
        int getX();
        int getY();
        int getNewX();
        int getNewY();
        void setX(int x);
        void setY(int y);
        int getHeight();
        int getWidth();
        int getXSpeed();
        int getYSpeed();
        void setXSpeed(int x);
        void setYSpeed(int y);
        void setColorR(Uint8 color);
        void setColorG(Uint8 color);
        void setColorB(Uint8 color);
        void setColorA(Uint8 color);
        Uint8 getColorR();
        Uint8 getColorG();
        Uint8 getColorB();
        Uint8 getColorA();
        // move the player to a new location based on speeds
        void update();
    private:
        int xLoc;
        int yLoc;
        int newXLoc;
        int newYLoc;
        int height;
        int width;
        int xSpeed;
        int ySpeed;
        Uint8 red;
        Uint8 blue;
        Uint8 green;
        Uint8 alpha;
}