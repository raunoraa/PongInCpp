#include "../include/button.h"

Button::Button(SDL_Renderer* renderer, int x_pos, int y_pos, int width, int height) :
    m_renderer(renderer)
{
    m_rect.x = x_pos;
    m_rect.y = y_pos;
    m_rect.w = width;
    m_rect.h = height;
}

Button::~Button()
{

}

void Button::render()
{
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(m_renderer, &m_rect);
}

bool Button::handleEvent(SDL_Event* e)
{
    if (e->type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        // Check if mouse is in button
        bool inside = true;

        // Mouse is left of the button
        if (x < m_rect.x)
        {
            inside = false;
        }
        // Mouse is right of the button
        else if (x > m_rect.x + m_rect.w)
        {
            inside = false;
        }
        // Mouse above the button
        else if (y < m_rect.y)
        {
            inside = false;
        }
        // Mouse below the button
        else if (y > m_rect.y + m_rect.h)
        {
            inside = false;
        }

        // Mouse is inside button
        if (inside)
        {
            return true;
        }
    }

    return false;
}