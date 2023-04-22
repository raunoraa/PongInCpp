#include <SDL2/SDL.h>

#ifndef BALL_H
#define BALL_H

class Ball {
    public:
        Ball();

        void Move();
        void Center();
        void Draw(SDL_Renderer* renderer);
        void CheckPaddleCollisions();
        void CheckWallCollisions();

        void setLeftPaddlePosX(int x);
        void setLeftPaddlePosY(int y);
        void setLeftPaddleHeight(int h);
        void setLeftPaddleWidth(int w);

        void setRightPaddlePosX(int x);
        void setRightPaddlePosY(int y);
        void setRightPaddleHeight(int h);

        void setScreenWidth(int w);
        void setScreenHeight(int h);

        bool getLeftScoresFlag();
        bool getRightScoresFlag();
        void resetScoreFlags(); //paneb vasaku ja parema skoorimise lipud false'iks

        void initializeVelocitiesMoveLeft(); //y kiiruseks saab -1 ning x kiiruseks saab -1
        void initializeVelocitiesMoveRight(); //y kiiruseks saab -1 ning x kiiruseks saab 1


    private:
        int m_x;
        int m_y;
        int m_width;
        int m_height;
        int m_velocityX;
        int m_velocityY;

        int m_leftPaddlePosX{};
        int m_leftPaddlePosY{}; //see uueneb pidevalt
        int m_leftPaddleHeight{};
        int m_leftPaddleWidth{};

        int m_rightPaddlePosX{};
        int m_rightPaddlePosY{}; //see uueneb pidevalt
        int m_rightPaddleHeight{};

        int m_SCREEN_HEIGHT{};
        int m_SCREEN_WIDTH{};

        bool m_leftScores{false};
        bool m_rightScores{false};

};

#endif