class Object{
    public:
        explicit Object(int x, int y, int h, int w);
        int getX();
        int getY();
        int getHeight();
        int getWidth();
        void setX(int x);
        void setY(int y);
        void draw();

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
