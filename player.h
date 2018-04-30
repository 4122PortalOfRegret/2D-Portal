#ifndef PLAYER_H
#define PLAYER_H

#include "block.h"
#include "utils.h"

class Player : public Block {
    public:
        explicit Player();
        explicit Player(int x, int y, int w, int h, SDL_Renderer* r, SDL_Rect& rect, SDL_Texture* i);
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
        void setHeight(int h);
        void setWidth(int w);
        SDL_Rect* getRectangle();
        void changeXSpeed(int x);
        void changeYSpeed(int y);
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
        void draw(SDL_Rect *anim);
        // move the player to a new location based on speeds
        void update(vector<Block>& vec, bool* ground, STATE& jump);
        void updateX(vector<Block>& vec);
        void updateY(vector<Block>& vec, bool* ground, STATE& lols);

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
        SDL_Renderer* renderer;
        SDL_Rect rectangle;
        SDL_Rect animation;
        SDL_Texture* image;
};

#endif