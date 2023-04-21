#include <SDL2/SDL.h>

#ifndef BALL_H
#define BALL_H

class Ball {
    public:
        Ball();
        ~Ball();

        void Move();
        void Draw(SDL_Renderer* renderer);
        void CheckPaddleCollisions();
        void HandleCollision();

    private:
        int x;
        int y;
        int width;
        int height;
        int velocityX;
        int velocityY;
};

#endif 