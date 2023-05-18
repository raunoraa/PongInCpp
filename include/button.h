#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>

class Button
{
public:
    Button(SDL_Renderer* renderer, int x_pos, int y_pos, int width, int height);
    ~Button();

    void render();
    bool handleEvent(SDL_Event* e);

private:
    SDL_Renderer* m_renderer;
    SDL_Rect m_rect;
};

#endif