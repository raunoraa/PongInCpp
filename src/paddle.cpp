#include "../include/paddle.h"

Paddle::Paddle(SDL_Renderer* renderer, int x_pos, int y_pos, int width, int height, int screenHeight) :
    m_renderer(renderer),
    m_rendererHeight{y_pos},
    m_screenHeight{screenHeight}
    {
        m_rect.x = x_pos;
        m_rect.y = y_pos;
        m_rect.w = width;
        m_rect.h = height;
    }

void Paddle::move(int verticalDistance){
    m_rect.y += verticalDistance;

    if (m_rect.y < 0) {
        m_rect.y = 0;
    }

    if (m_rect.y + m_rect.h > m_screenHeight)
    {
        m_rect.y = m_screenHeight - m_rect.h;
    }
}

void Paddle::render(){
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(m_renderer, &m_rect);
}

void Paddle::resetPaddlePos()
{
    m_rect.y = m_screenHeight/3;
}

int Paddle::getPosX(){
    return m_rect.x;
}

int Paddle::getPosY(){
    return m_rect.y;
}

int Paddle::getPaddleHeight()
{
    return m_rect.h;
}

int Paddle::getPaddleWidth()
{
    return m_rect.w;
}


