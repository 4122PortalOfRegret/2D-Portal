class Object{
    public:
        explicit Object(int x, int y, int h, int w);
        int getX();
        int getY();
        int getNewX();
        int getNewY();
        int getHeight();
        int getWidth();
        void setXSpeed(int x);
        void setYSpeed(int y);
        void setX(int x);
        void setY(int y);
        void update();
//        void draw();

    private:
        int xLoc;
        int yLoc;
        int newXLoc;
        int newYLoc;
        int height;
        int width;
        void setHeight(int h);
        void setWidth(int w);
        int xSpeed;
        int ySpeed;
        void hitDetection();
};
