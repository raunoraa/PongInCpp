#include <SDL2/SDL.h>
#include "../include/allheaders.h"
#include <iostream>
#include <fstream>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* args[])
{

    TestOther1();
    TestOther2();

    std::cout << '\n';

    ReadFromTestFile();

    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window* window = SDL_CreateWindow("Pong Game AMONG US SUSUSUSUSUS",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Surface* iconSurface = SDL_LoadBMP("./assets/proov.bmp");

    SDL_SetWindowIcon(window,iconSurface);
    SDL_FreeSurface(iconSurface);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        SDL_RenderClear(renderer);

        // draw game objects

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}