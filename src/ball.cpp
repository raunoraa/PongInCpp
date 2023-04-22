#include "../include/ball.h"
#include <iostream>

Ball::Ball() {
    m_x = 640;
    m_y = 360;
    m_width = 20;
    m_height = 20;
    m_velocityX = 1;
    m_velocityY = 1;
}

void Ball::Move() {
    m_x += m_velocityX;
    m_y += m_velocityY;
    CheckWallCollisions();
    CheckPaddleCollisions();
}

void Ball::Draw(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = m_x;
    rect.y = m_y;
    rect.w = m_width;
    rect.h = m_height;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Ball::CheckPaddleCollisions() {

    //std::cout << "LeftPaddlePosX+20: " << m_leftPaddlePosX +20 << " ; LeftPaddlePosY: " << m_leftPaddlePosY << " ; Y+PaddleHeight: " << m_leftPaddlePosY + m_leftPaddleHeight << " ; BallX: " << m_x << " ; BallY+20: " << m_y + m_height << '\n';

    // Check collision with left paddle
    //20 on paddle'i laius (selliste asjade hardcode'imine pole hea tava, seega tuleb tõenäoliselt veel ühe private isendiväljana kaasa anda)
    //m_height/2 on seetõttu, et muuta hitboxe leebemaks (kui pool palli puutub veel paddle'iga, siis loe seda veel kokkupõrkeks)
    if (m_x <= m_leftPaddlePosX + 20 && (m_y >= m_leftPaddlePosY && m_y + m_height/2 <= m_leftPaddlePosY + m_leftPaddleHeight))
    {
        //std::cout << "LeftPaddlePosY: " << m_leftPaddlePosY << " ; Y+PaddleHeight: " << m_leftPaddlePosY + m_leftPaddleHeight << " ; BallY+BallHeight: " << m_y + m_height << '\n';
        //std::cout << "LEFTPADDLE_COLLISION\n"

        /* Siia tuleb mingi targem loogika, et paddle abil saaks kontrollida palli liikumist */
        m_x = m_leftPaddlePosX + 20 + 1;
        m_velocityX = -m_velocityX;
    }
    

    // Check collision with right paddle
    if (m_x + m_width >= m_rightPaddlePosX && (m_y >= m_rightPaddlePosY && m_y + m_height/2 <= m_rightPaddlePosY + m_rightPaddleHeight))
    {
        //std::cout << "RIGHTPADDLE_COLLISION\n";
                
        /* Siia tuleb mingi targem loogika, et paddle abil saaks kontrollida palli liikumist */
        m_x = m_rightPaddlePosX - m_width - 1;
        m_velocityX = -m_velocityX;        
    }
    
}

void Ball::CheckWallCollisions() {
    // Check collision with top wall
    if (m_y <= 0) {
        m_velocityY = -m_velocityY;
    }
    // Check collision with bottom wall
    if (m_y + m_height >= 720) {
        m_velocityY = -m_velocityY;
    }
     if (m_x + m_width >= 1280) {
        m_velocityX = -m_velocityX;
    }
     if (m_x + m_width <= 0) {
        m_velocityX = -m_velocityX;
    }
}

void Ball::setLeftPaddlePosX(int x)
{
    m_leftPaddlePosX = x;
}

void Ball::setLeftPaddlePosY(int y)
{
    m_leftPaddlePosY = y;
}

void Ball::setLeftPaddleHeight(int h)
{
    m_leftPaddleHeight = h;
}

void Ball::setRightPaddlePosX(int x)
{
    m_rightPaddlePosX = x;
}

void Ball::setRightPaddlePosY(int y)
{
    m_rightPaddlePosY = y;
}

void Ball::setRightPaddleHeight(int h)
{
    m_rightPaddleHeight = h;
}
