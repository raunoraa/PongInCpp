#include <SDL2/SDL.h>

#ifndef BALL_H
#define BALL_H

class Ball {
    public:
        Ball();

        void Move();
        void Draw(SDL_Renderer* renderer);
        void CheckPaddleCollisions();
        void CheckWallCollisions();

        void setLeftPaddlePosX(int x);
        void setLeftPaddlePosY(int y);
        void setLeftPaddleHeight(int h);

        void setRightPaddlePosX(int x);
        void setRightPaddlePosY(int y);
        void setRightPaddleHeight(int h);


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

        int m_rightPaddlePosX{};
        int m_rightPaddlePosY{}; //see uueneb pidevalt
        int m_rightPaddleHeight{};

};

#endif