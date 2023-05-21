#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
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
void PlaySound(const char* fileName)
        {
            //Load a sound file into memory
            Mix_Chunk* sound = Mix_LoadWAV(fileName);
            if (!sound)
            {
                printf("Error loading sound file!\n");
                return;
            }

            //Play the sound file with a volume of 50
            Mix_Volume(1, 50);
            Mix_PlayChannel(1, sound, 0);

            //Free up the memory associated with the sound file
            Mix_FreeChunk(sound);
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

    Uint8 nupu_r = 211;
    Uint8 nupu_g = 194;
    Uint8 nupu_b = 255;

    //LOOME MENÜÜ NUPUD
    Button pvp(renderer, 457, 265, 372, 75, nupu_r, nupu_g, nupu_b); //PVP NUPP
    Button controls(renderer, 457, 380, 372, 75, nupu_r, nupu_g, nupu_b); //selgitav tekst controlsist (TODO)
    Button exit(renderer, 457, 500, 372, 75, nupu_r, nupu_g, nupu_b);

    Button back(renderer, 62, 567, 400, 87, nupu_r, nupu_g, nupu_b); //controls menüü jaoks tagasi main menu-sse minekuks

    //Laeme pildid mällu
    IMG_Init(IMG_INIT_PNG);

    SDL_Surface * MenuSurface = IMG_Load("./assets/menu.png");
    SDL_Texture * MenuTexture = SDL_CreateTextureFromSurface(renderer, MenuSurface);

    SDL_Surface * ControlsSurface = IMG_Load("./assets/controls.png");
    SDL_Texture * ControlsTexture = SDL_CreateTextureFromSurface(renderer, ControlsSurface);

    SDL_Surface * PlayMenuSurface = IMG_Load("./assets/2ndmenu.png");
    SDL_Texture * PlayMenuTexture = SDL_CreateTextureFromSurface(renderer, PlayMenuSurface);


    TTF_Init();

    //Avab fondi ja määrab fondi suuruse, 200 sest muidu on tekst kandiline
    TTF_Font* Sans = TTF_OpenFont("./assets/OpenSansBold.ttf", 200);
    
    SDL_Color White = {255, 255, 255};

    SDL_Surface* surfaceMessage =
        TTF_RenderText_Solid(Sans, "0 : 0", White);

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    
    SDL_Rect Message_rect; //create a rect

    Message_rect.h = 200;
    Message_rect.w = 200;
    Message_rect.x = 550;
    Message_rect.y = 50;


    SDL_Surface* victorySurface =
    TTF_RenderText_Solid(Sans, "Victory Message", White);

    SDL_Texture* victoryMessage = SDL_CreateTextureFromSurface(renderer, victorySurface);
    
    SDL_Rect victoryMessage_rect; //create a rect

    victoryMessage_rect.h = 180;
    victoryMessage_rect.w = 400;
    victoryMessage_rect.x = 450;
    victoryMessage_rect.y = 170;


    //Initialize the audio system
    Mix_OpenAudio(48000, AUDIO_S16SYS, 1, 1024);


    Mix_Chunk* paddlesound = Mix_LoadWAV("./assets/paddle.flac");
    Mix_Chunk* wallsound = Mix_LoadWAV("./assets/wall.flac");
    Mix_Chunk* score = Mix_LoadWAV("./assets/score.flac");
    

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

    bool SHOW_MENU_FLAG = true;
    bool EXIT_GAME_FLAG = false;
    bool SHOW_CONTROLS_MENU_FLAG = false;


    bool SHOW_PLAY_OPTIONS_MENU_FLAG = false;
    bool BEST_OF_5_FLAG = false;
    bool BEST_OF_15_FLAG = false;

    Button bestOf5(renderer, 0, 93, 450, 75, nupu_r, nupu_g, nupu_b);
    Button bestOf15(renderer, 0, 220, 450, 75, nupu_r, nupu_g, nupu_b);
    Button infinite(renderer, 0, 345, 450, 75, nupu_r, nupu_g, nupu_b);
    Button backToMain(renderer, 0, 475, 450, 75, nupu_r, nupu_g, nupu_b);

    bool GAME_END = false; // mäng läbi (ainult best of 5 ja 15 korral)
    bool CHANGE_TEXT = false;
    
    bool PLAYER1_WON = false; //vasak mängija võitis

    SDL_Event event;

    while (running)
    {
        if (EXIT_GAME_FLAG)
        {
            break;
        }
        

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

            if (EXIT_GAME_FLAG)
            {
                break;
            }
            
            
            if (SHOW_MENU_FLAG)
            {
                //SIIN VAATAME, KAS NUPU PEALE VAJUTATI
                if (pvp.checkIfPressed())
                {
                    SHOW_MENU_FLAG = false;
                    SHOW_PLAY_OPTIONS_MENU_FLAG = true;
                    Mix_PlayChannel(1, wallsound, 0);
                }

                else if (exit.checkIfPressed())
                {
                    EXIT_GAME_FLAG = true;
                    Mix_PlayChannel(1, wallsound, 0);
                }
                
                else if (controls.checkIfPressed())
                {
                    SHOW_CONTROLS_MENU_FLAG = true;
                    SHOW_MENU_FLAG = false;
                    Mix_PlayChannel(1, wallsound, 0);

                    //teeme controls menüü teksti (peab vist tegema mitu objekti, sest ei tuvasta reavahetuse sümbolit)
                    //controls teksti sisu võiks olla sama, mis rida all välja kommenteeritud tekstis
                    //surfaceMessage = TTF_RenderText_Solid(Sans, "Controls\n\n\nLeft Player Paddle Up: W\nLeft Player Paddle Down: S\n\nRight Player Paddle Up: UP\nRight Player Paddle Down: DOWN", White);
                    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

                }
            } 
            else if (SHOW_PLAY_OPTIONS_MENU_FLAG)
            {
                if (bestOf5.checkIfPressed())
                {
                    SHOW_PLAY_OPTIONS_MENU_FLAG = false;
                    BEST_OF_5_FLAG = true;
                    Mix_PlayChannel(1, wallsound, 0);
                }
                else if (bestOf15.checkIfPressed())
                {
                    SHOW_PLAY_OPTIONS_MENU_FLAG = false;
                    BEST_OF_15_FLAG = true;
                    Mix_PlayChannel(1, wallsound, 0);
                }
                else if (infinite.checkIfPressed())
                {
                    SHOW_PLAY_OPTIONS_MENU_FLAG = false;
                    Mix_PlayChannel(1, wallsound, 0);
                }
                else if (backToMain.checkIfPressed())
                {
                    SHOW_PLAY_OPTIONS_MENU_FLAG = false;
                    SHOW_MENU_FLAG = true;
                    Mix_PlayChannel(1, wallsound, 0);
                }
            }
            else if (SHOW_CONTROLS_MENU_FLAG)
            {

                if (back.checkIfPressed())
                {
                    SHOW_CONTROLS_MENU_FLAG = false;
                    Mix_PlayChannel(1, wallsound, 0);
                    SHOW_MENU_FLAG = true;
                }
                
            }
            else{
                //kui vajutati ESC, siis mine tagasi main menüüsse


                if (keyboardState[SDL_SCANCODE_ESCAPE])
                {
                    SHOW_MENU_FLAG = true;
                    BEST_OF_5_FLAG = false;
                    BEST_OF_15_FLAG = false;
                    PLAYER1_WON = false;

                    ball.Center();
                    ball.resetScoreFlags();
                    ball.initializeVelocitiesMoveLeft();
                    paddle1.resetPaddlePos();
                    paddle2.resetPaddlePos();
                    leftScore = 0;
                    rightScore = 0;

                    //vasak mängija saab punkti ning saab alustada
                    //Uuendab akna nime, et skoor oleks uuendatud
                    windowTitle = "Pong Game - Left Player Score: " + std::to_string(leftScore) + "  |  Right Player Score: " + std::to_string(rightScore);
                    SDL_SetWindowTitle(window, windowTitle.c_str());

                    surfaceMessage = TTF_RenderText_Solid(Sans, (std::to_string(leftScore) + " : " + std::to_string(rightScore)).c_str(), White);
                    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

                    if (GAME_END)
                    {
                        GAME_END = false;
                        leftPlayerStarts = true;
                        break;
                    }
                    
                }
                

                if (restartFlag)
                {
                    if (GAME_END)
                    {
                        if (CHANGE_TEXT)
                        {
                        std::string end_tekst;
                        if (PLAYER1_WON)
                        {
                            end_tekst = "Left Player Won!";
                        } else
                        {
                            end_tekst = "Right Player Won!";
                        }
                        victorySurface = TTF_RenderText_Solid(Sans, end_tekst.c_str(), White);
                        victoryMessage = SDL_CreateTextureFromSurface(renderer, victorySurface);
                        CHANGE_TEXT = false;
                        }
                    }
                    else if(leftPlayerStarts && (keyboardState[SDL_SCANCODE_W] || keyboardState[SDL_SCANCODE_S])){
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

                    if (ball.getPaddleHit()) //Paddle puutumise heli jaoks
                    {
                        Mix_Volume(1, 50);
                        Mix_PlayChannel(1, paddlesound, 0);
                    }
                    
                    if (ball.getWallHit()) //Seina puutumise heli jaoks
                    {
                        Mix_Volume(1, 50);
                        Mix_PlayChannel(1, wallsound, 0);
                    }
                    


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
                        //Mängib heli "score"
                        Mix_Volume(1, 50);
                        Mix_PlayChannel(1, score, 0);
                        leftPlayerStarts = true;

                        if (BEST_OF_5_FLAG)
                        {
                            if (leftScore > 2)
                            {
                                GAME_END = true;
                                PLAYER1_WON = true;
                                CHANGE_TEXT = true;
                            }
                        } else if (BEST_OF_15_FLAG)
                        {
                            if (leftScore > 7)
                            {
                                GAME_END = true;
                                PLAYER1_WON = true;
                                CHANGE_TEXT = true;
                            }
                            
                        }                    

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
                        //Mängib heli "score"
                        Mix_Volume(1, 50);
                        Mix_PlayChannel(1, score, 0);
                        leftPlayerStarts = false;

                        if (BEST_OF_5_FLAG)
                        {
                            if (rightScore > 2)
                            {
                                CHANGE_TEXT = true;
                                GAME_END = true;
                            }
                        } else if (BEST_OF_15_FLAG)
                        {
                            if (rightScore > 7)
                            {
                                CHANGE_TEXT = true;
                                GAME_END = true;
                            }
                            
                        } 

                        //Teeme uue Texture objekti vaid siis, kui skoor muutus
                        surfaceMessage = TTF_RenderText_Solid(Sans, (std::to_string(leftScore) + " : " + std::to_string(rightScore)).c_str(), White);
                        Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
                    }
                    //Saab skoori terminali printida
                    //std::cout << "Left Player Score: " << leftScore << "  |  Right Player Score: " << rightScore << std::endl;
                }
            }
    
            accumulatedTime -= TIME_STEP;
        }

        //paddle'ite debugimiseks
        //std::cout << "Paddle X: " << paddle1.getPosX() << " ; Paddle Y:" << paddle1.getPosY() << '\n';

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        if (SHOW_MENU_FLAG)
        {
            //JOONISTAME MENÜÜ
            pvp.render();
            controls.render();
            exit.render();
            SDL_RenderCopy(renderer, MenuTexture, NULL, NULL);
        } 
        else if (SHOW_CONTROLS_MENU_FLAG)
        {
            back.render();
            //SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //RENDERDA TEKST
            SDL_RenderCopy(renderer, ControlsTexture, NULL, NULL);
        }
        else if (SHOW_PLAY_OPTIONS_MENU_FLAG)
        {
            bestOf5.render();
            bestOf15.render();
            infinite.render();
            backToMain.render();
            SDL_RenderCopy(renderer, PlayMenuTexture, NULL, NULL);
        }
        else
        {
            //Joonista mänguobjektid vaid siis, kui oleme menüüdest väljas
            // draw game objects
            paddle1.render();
            paddle2.render();
            ball.Draw(renderer);
            SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //RENDERDA TEKST
            if (GAME_END)
            {
                SDL_RenderCopy(renderer, victoryMessage, NULL, &victoryMessage_rect); //RENDERDA VÕIDU TEKST
            }
            
        }

        SDL_RenderPresent(renderer);


        int remainingTime = TIME_STEP - accumulatedTime;
        if (remainingTime > 0) {
            SDL_Delay(remainingTime);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(Message);
    SDL_DestroyTexture(victoryMessage);
    Mix_FreeChunk(score);
    Mix_FreeChunk(paddlesound);
    Mix_FreeChunk(wallsound);

    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
    

    return 0;
}