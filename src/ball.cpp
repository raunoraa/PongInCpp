#include "../include/ball.h"

Ball::Ball() {
    x = 640;
    y = 360;
    width = 20;
    height = 20;
    velocityX = 1;
    velocityY = 1;
}

Ball::~Ball() {

}

void Ball::Move() {
    x += velocityX;
    y += velocityY;
}

void Ball::Draw(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Ball::CheckPaddleCollisions() {
    // Check collision with left paddle
    if (x <= 50 && y >= 0 && y <= 600) {
        HandleCollision();
    }
    // Check collision with right paddle
    if (x >= 650 && y >= 0 && y <= 600) {
        HandleCollision();
    }
}

void Ball::HandleCollision() {
    velocityX = -velocityX;
}