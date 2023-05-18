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

    SDL_Window* window = SDL_CreateWindow("Pong Game",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Surface* iconSurface = SDL_LoadBMP("./assets/ikoon.bmp");
    std::string windowTitle = "Pong Game - Left Player Score: " + std::to_string(leftScore) + "  |  Right Player Score: " + std::to_string(rightScore);
    SDL_SetWindowTitle(window, windowTitle.c_str());

    SDL_SetWindowIcon(window,iconSurface);
    SDL_FreeSurface(iconSurface);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    
    TTF_Init();

    //this opens a font style and sets a size
    TTF_Font* Sans = TTF_OpenFont("./assets/OpenSansBold.ttf", 200);
    
    SDL_Color White = {255, 255, 255};

    SDL_Surface* surfaceMessage =
        TTF_RenderText_Solid(Sans, "0 : 0", White);

    // now you can convert it into a texture
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    
    SDL_Rect Message_rect; //create a rect

    Message_rect.h = 100;
    Message_rect.w = 100;
    Message_rect.x = 600;
    Message_rect.y = 50;
    

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
                    //vasak mängija saab punkti ning saab alustada
                    //Uuendab akna nime, et skoor oleks uuendatud
                    windowTitle = "Pong Game - Left Player Score: " + std::to_string(leftScore) + "  |  Right Player Score: " + std::to_string(rightScore);
                    SDL_SetWindowTitle(window, windowTitle.c_str());
                    leftPlayerStarts = true;

                    //Teeme uue Texture objekti vaid siis, kui skoor muutus
                    surfaceMessage = TTF_RenderText_Solid(Sans, (std::to_string(leftScore) + " : " + std::to_string(rightScore)).c_str(), White);
                    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
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
                    //parem mängija saab punkti ning saab alustada
                    //Uuendab akna nime, et skoor oleks uuendatud
                    windowTitle = "Pong Game - Left Player Score: " + std::to_string(leftScore) + "  |  Right Player Score: " + std::to_string(rightScore);
                    SDL_SetWindowTitle(window, windowTitle.c_str());
                    leftPlayerStarts = false;

                    //Teeme uue Texture objekti vaid siis, kui skoor muutus
                    surfaceMessage = TTF_RenderText_Solid(Sans, (std::to_string(leftScore) + " : " + std::to_string(rightScore)).c_str(), White);
                    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
                }
                           //Saab skoori terminali printida
                           //std::cout << "Left Player Score: " << leftScore << "  |  Right Player Score: " << rightScore << std::endl;
            }
    
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

        SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //DEBUG LINE

        SDL_RenderPresent(renderer);


        int remainingTime = TIME_STEP - accumulatedTime;
        if (remainingTime > 0) {
            SDL_Delay(remainingTime);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(Message);

    TTF_Quit();
    SDL_Quit();
    

    return 0;
}