#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>

class Button
{
public:
    Button(SDL_Renderer* renderer, int x_pos, int y_pos, int width, int height, Uint8 r, Uint8 g, Uint8 b);
    ~Button();

    void render();
    bool checkIfPressed();

private:
    SDL_Renderer* m_renderer;
    SDL_Rect m_rect;
    Uint8 m_r;
    Uint8 m_g;
    Uint8 m_b;

};

#endif