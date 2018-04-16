#include <iostream>
#include "SDL.h"

using namespace std;

int main(int argc, char** argv) {
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        cout << "Something went wrong! " << SDL_GetError() << endl;
    }


    SDL_Window* window = SDL_CreateWindow("SDL_Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
    if(window == NULL){
        cout << "Something also went wrong here" << endl;
    }

    bool quit = false;
    SDL_Event event;
    int x = 288;
    int y = 208;

    SDL_Renderer* renderer;
    SDL_Renderer* wRender;
    SDL_Event events;

    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderClear(renderer);


    SDL_Rect myRect = {50, 50, 64, 64};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &myRect);
    SDL_RenderPresent(renderer);
    while(!quit){
        SDL_PollEvent(&events);
        if(events.type == SDL_QUIT) {
            quit = true;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &myRect);
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_A]) {
            myRect.x -= 1;
        }
        if(state[SDL_SCANCODE_S]) {
            myRect.y += 1;
        }
        if(state[SDL_SCANCODE_D]) {
            myRect.x += 1;
        }
        if(state[SDL_SCANCODE_W]) {
            myRect.y -= 1;
        }
        if(state[SDL_SCANCODE_ESCAPE]) {
            quit = true;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &myRect);
        SDL_RenderPresent(renderer);
        SDL_PumpEvents();
        //SDL_Delay(15);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

