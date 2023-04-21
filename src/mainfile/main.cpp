#include <SDL2/SDL.h>
#include "../include/allheaders.h"
#include <iostream>
#include <fstream>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int PADDLE_SPEED = 1;

void CheckAndMovePaddles(Paddle& paddle1, Paddle& paddle2, const Uint8* keyboardState){
    //player1
    if (keyboardState[SDL_SCANCODE_W]) {
        paddle1.move(-PADDLE_SPEED);
    }
    if (keyboardState[SDL_SCANCODE_S]) {
        paddle1.move(PADDLE_SPEED);
    }

    //player2
    if (keyboardState[SDL_SCANCODE_UP]) {
        paddle2.move(-PADDLE_SPEED);
    }
    if (keyboardState[SDL_SCANCODE_DOWN]) {
        paddle2.move(PADDLE_SPEED);
    }
}

int main(int argc, char* args[])
{
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window* window = SDL_CreateWindow("Pong Game AMONG US SUSUSUSUSUS",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Surface* iconSurface = SDL_LoadBMP("./assets/proov.bmp");

    SDL_SetWindowIcon(window,iconSurface);
    SDL_FreeSurface(iconSurface);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    Paddle paddle1(renderer, 20*3, 200, 20, 100, SCREEN_HEIGHT);

    Paddle paddle2(renderer, SCREEN_WIDTH-20*4, 200, 20, 100, SCREEN_HEIGHT);

    Ball ball;

    bool running = true;

    SDL_Event event;

    unsigned char updatePaddle{};

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            
        }

        updatePaddle += 1;
        if (updatePaddle > 15)
        {
            updatePaddle = 0;
        }

        // Get the state of the keyboard
        const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

        if(updatePaddle%2==0){
            // Update object position based on keyboard input
            // Selleks, et oleks aeglasem, teeme seda igal 16. iteratsioonil
            CheckAndMovePaddles(paddle1,paddle2,keyboardState);
            ball.Move();
            ball.CheckPaddleCollisions();
        }

        //paddle'ite debugimiseks
        //std::cout << "Paddle X: " << paddle1.getPosX() << " ; Paddle Y:" << paddle1.getPosY() << '\n';

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // draw game objects
        paddle1.render();
        paddle2.render();
        ball.Draw(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}