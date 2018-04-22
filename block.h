#include "polygon.h"

class Block : public Object
{
    public:
        explicit Object(int x, int y, int h, int w);
        virtual void getColor() = 0;
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
        //void update();

//        void draw();

    private:
        int xLoc;
        int yLoc;
        //int newXLoc;
        //int newYLoc;
        int height;
        int width;
};