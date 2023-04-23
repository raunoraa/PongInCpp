#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../include/allheaders.h"
#include <iostream>
#include <string>
#include <fstream>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int PADDLE_SPEED = 1;

const int TARGET_FPS = 360;
const int TIME_STEP = 1000 / TARGET_FPS;

Uint32 lastUpdateTime = SDL_GetTicks();
int accumulatedTime = 0;
int leftScore = 0;
int rightScore = 0;

// Define font variable
TTF_Font* font = TTF_OpenFont("assets/FreeSansBold.ttf", 24);

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

    Paddle paddle1(renderer, 20*3, SCREEN_HEIGHT/3, 20, 100, SCREEN_HEIGHT);

    Paddle paddle2(renderer, SCREEN_WIDTH-20*4, SCREEN_HEIGHT/3, 20, 100, SCREEN_HEIGHT);

    Ball ball;


    
    ball.setLeftPaddlePosX(paddle1.getPosX());
    ball.setLeftPaddlePosY(paddle1.getPosY());
    ball.setLeftPaddleHeight(paddle1.getPaddleHeight());
    ball.setLeftPaddleWidth(paddle1.getPaddleWidth());

    ball.setRightPaddlePosX(paddle2.getPosX());
    ball.setLeftPaddlePosY(paddle2.getPosY());
    ball.setRightPaddleHeight(paddle2.getPaddleHeight());

    ball.setScreenWidth(SCREEN_WIDTH);
    ball.setScreenHeight(SCREEN_HEIGHT);
    

    bool running = true;

    bool restartFlag = true;

    bool leftPlayerStarts = true; //esimesel korral alustab vasak mängija
    ball.initializeVelocitiesMoveLeft();

    SDL_Event event;

    //unsigned char updatePaddle{};

    while (running)
    {

        Uint32 currentTime = SDL_GetTicks();
        Uint32 deltaTime = currentTime - lastUpdateTime;
        lastUpdateTime = currentTime;

        accumulatedTime += deltaTime;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            
        }

        // Get the state of the keyboard
        const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

        while (accumulatedTime >= TIME_STEP) {

            if (restartFlag)
            {
                if(leftPlayerStarts && (keyboardState[SDL_SCANCODE_W] || keyboardState[SDL_SCANCODE_S])){
                    restartFlag = false;
                }
                else if (!leftPlayerStarts && (keyboardState[SDL_SCANCODE_UP] || keyboardState[SDL_SCANCODE_DOWN]))
                {
                    restartFlag = false;
                }

            } else
            {
                CheckAndMovePaddles(paddle1,paddle2,keyboardState);

                ball.setLeftPaddlePosY(paddle1.getPosY());
                ball.setRightPaddlePosY(paddle2.getPosY());

                ball.Move();

                if (ball.getLeftScoresFlag())
                {
                    ball.Center();
                    ball.resetScoreFlags();
                    ball.initializeVelocitiesMoveLeft();
                    paddle1.resetPaddlePos();
                    paddle2.resetPaddlePos();
                    restartFlag = true;
                    leftScore++;
                    //vasak mängija saab punkti (TODO) ning saab alustada
                    leftPlayerStarts = true;

                }
                else if (ball.getRightScoresFlag())
                {
                    ball.Center();
                    ball.resetScoreFlags();
                    ball.initializeVelocitiesMoveRight();
                    paddle1.resetPaddlePos();
                    paddle2.resetPaddlePos();
                    restartFlag = true;
                    rightScore++;
                    //parem mängija saab punkti (TODO) ning saab alustada
                    leftPlayerStarts = false;
                }
                           std::cout << "Left Player Score: " << leftScore << "  |  Right Player Score: " << rightScore << std::endl;
            }
            
            // Draw the score
            SDL_Color whiteColor = { 255, 255, 255, 255 };
            SDL_Surface* scoreSurfaceLeft = TTF_RenderText_Solid(font, std::to_string(leftScore).c_str(), whiteColor);
            SDL_Surface* scoreSurfaceRight = TTF_RenderText_Solid(font, std::to_string(rightScore).c_str(), whiteColor);
            SDL_Texture* scoreTextureLeft = SDL_CreateTextureFromSurface(renderer, scoreSurfaceLeft);
            SDL_Texture* scoreTextureRight = SDL_CreateTextureFromSurface(renderer, scoreSurfaceRight);
            SDL_Rect scoreDestRectRight = { SCREEN_WIDTH * 3 / 4, 10, 20, 20 };
            SDL_Rect srcRectLeft = { 0, 0, 40, 40 }; // specify the area of the score texture to draw
            SDL_Rect destRectLeft = { SCREEN_WIDTH / 2 - 20, 10, 40, 40 }; // specify the coordinates of the window where the texture will be drawn

            SDL_RenderCopy(renderer, scoreTextureLeft, &srcRectLeft, &destRectLeft);
            SDL_RenderCopy(renderer, scoreTextureRight, NULL, &scoreDestRectRight);

            accumulatedTime -= TIME_STEP;
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

        int remainingTime = TIME_STEP - accumulatedTime;
        if (remainingTime > 0) {
            SDL_Delay(remainingTime);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}